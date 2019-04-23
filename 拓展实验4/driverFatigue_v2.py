# importing the necessary packages
from scipy.spatial import distance as dist
from imutils import face_utils
import numpy as np
import imutils
import dlib
import cv2
import os
'''
dlib的人脸检测算法采用 基于梯度增强
(radient boosting) 的框架,通过优化损失函数和误差的
总和来学习回归树集合 (Ensemble of Regression Trees,
ERT), 检测出脸部图像中的 68 个关键点, 最后对齐人
脸, 并根据关键点序号定位出所需要的眼部、嘴部图
像。

首先在训练集中对人脸图像特征点进行标注。然后利用回归树模型进行训练。
首先需要计算的是平均脸，作为模型在测试时初始化的形状，认为是shape。训练时，将像素点强度作为特征，
已标定的训练集附近的像素点和点对之间的距离作为特征池，将距离除以两眼之间的距离以进行归一化，这里引入指数距离先验，
套用集成回归树模型，模型为级联的10个回归树，每个回归树中有500个弱回归器，每个树的深度为5，
使用梯度提升算法(集成)使用残差不断回归，拟合误差，得到最终的回归树模型。在测试时，将人脸检测结果输入模型，
先使用平均脸贴在一个新的测试脸中，得到初始shape，用脸部形状来预测特征点，同时反过来也用特征点预测脸部的形状，
并利用与训练时同样的误差函数去回归，不断回归并减小与groundtruth的误差，通过10次级联回归树，得到最终的人脸特征点定位结果。


# HOG特征提取算法的实现过程 方向梯度直方图
HOG特征提取方法就是将一个image（你要检测的目标或者扫描窗口）：
1）灰度化（将图像看做一个x,y,z（灰度）的三维图像）；

2）采用Gamma校正法对输入图像进行颜色空间的标准化（归一化）；
目的是调节图像的对比度，降低图像局部的阴影和光照变化所造成的影响，同时可以抑制噪音的干扰；

3）计算图像每个像素的梯度（包括大小和方向）；主要是为了捕获轮廓信息，同时进一步弱化光照的干扰。

4）将图像划分成小cells（例如6*6像素/cell）；

5）统计每个cell的梯度直方图（不同梯度的个数），即可形成每个cell的descriptor；

6）将每几个cell组成一个block（例如3*3个cell/block），
一个block内所有cell的特征descriptor串联起来便得到该block的HOG特征descriptor。

7）将图像image内的所有block的HOG特征descriptor串联起来就可以得到该image
（你要检测的目标）的HOG特征descriptor了。这个就是最终的可供分类使用的特征向量了。
'''



#计算眼宽比
def eye_aspect_ratio(eye):
	# 计算垂直方向之间的欧氏距离
	A = dist.euclidean(eye[1], eye[5])
	B = dist.euclidean(eye[2], eye[4])

	# 计算水平方向之间的欧氏距离
	C = dist.euclidean(eye[0], eye[3])
	# compute the eye aspect ratio
	ear = (A + B) / (2.0 * C)
	return ear

#calculating mouth aspect ratio
def mouth_aspect_ratio(mou):
	# 计算水平方向之间的欧氏距离
	X   = dist.euclidean(mou[0], mou[6])
	# 计算垂直方向之间的欧氏距离
	Y1  = dist.euclidean(mou[2], mou[10])
	Y2  = dist.euclidean(mou[4], mou[8])
	# taking average
	Y   = (Y1+Y2)/2.0
	# compute mouth aspect ratio
	mar = Y/X
	return mar

# define constants for aspect ratios
EYE_AR_THRESH = 0.25
EYE_AR_CONSEC_FRAMES = 5
MOU_AR_THRESH = 0.75

COUNTER = 0
yawnStatus = False
yawns = 0
# 初始化dlib的人脸检测器(基于霍格)，然后创建面部地标预测器
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor('./shape_predictor_68_face_landmarks.dat')

# 抓取左右眼的面部地标的索引还有嘴巴
(lStart, lEnd) = face_utils.FACIAL_LANDMARKS_IDXS["left_eye"]
(rStart, rEnd) = face_utils.FACIAL_LANDMARKS_IDXS["right_eye"]
(mStart, mEnd) = face_utils.FACIAL_LANDMARKS_IDXS["mouth"]

# 循环捕获视频

path_all = ["../test_picture/eye/","../test_picture/mouth/"]


for path in path_all:
    path_list = os.listdir(path)
    path_list.sort()
    for picturename in path_list:
        filepicture = path + picturename
        cap = cv2.VideoCapture(filepicture)

        while True:
            # grab the frame from the camera, resize
            # it, and convert it to grayscale
            # channels)
            ret, frame = cap.read()
            if not ret:
                break
            frame = imutils.resize(frame, width=640)
            gray1 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            #采用双边滤波降噪
            #般的高斯模糊在进行采样时主要考虑了像素间的空间距离关系，但是却并没有考虑像素值之间的相似程度，
            # 因此这样我们得到的模糊结果通常是整张图片一团模糊。Bilateral blur的改进就在于在采样时不仅考虑像素在空间距离上的关系，
            # 同时加入了像素间的相似程度考虑，因而可以保持原始图像的大体分块进而保持边缘。
            #普通的高斯滤波会将图像的边缘模糊掉，而双边滤波器具有保边特性。
            gray2 = cv2.bilateralFilter(gray1,9,75,75)
            prev_yawn_status = yawnStatus
            # 检测灰度帧中的人脸
            rects = detector(gray, 0)

            # 环面检测
            for rect in rects:
                # 然后确定脸部区域的面部地标将面部地标(x, y)坐标转换为NumPy数组
                shape = predictor(gray, rect)
                shape = face_utils.shape_to_np(shape)

                # 提取左眼和右眼坐标，然后使用坐标用于计算双眼的眼宽比
                leftEye = shape[lStart:lEnd]
                rightEye = shape[rStart:rEnd]
                mouth = shape[mStart:mEnd]
                leftEAR = eye_aspect_ratio(leftEye)
                rightEAR = eye_aspect_ratio(rightEye)
                mouEAR = mouth_aspect_ratio(mouth)
                # 将两只眼睛的眼宽比平均起来
                ear = (leftEAR + rightEAR) / 2.0

                # 然后计算左眼和右眼的凸包
                leftEyeHull = cv2.convexHull(leftEye)
                rightEyeHull = cv2.convexHull(rightEye)
                mouthHull = cv2.convexHull(mouth)
                cv2.drawContours(frame, [leftEyeHull], -1, (0, 255, 255), 1)
                cv2.drawContours(frame, [rightEyeHull], -1, (0, 255, 255), 1)
                cv2.drawContours(frame, [mouthHull], -1, (0, 255, 0), 1)

                #检查眼睛的长宽比是否低于眨眼阈值，如果是，则递增blink帧计数器
                if ear < EYE_AR_THRESH:
                    COUNTER += 1
                    cv2.putText(frame, "Eyes Closed ", (10, 30),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

                    # if the eyes were closed for a sufficient number of
                    if COUNTER >= EYE_AR_CONSEC_FRAMES:
                        # draw an alarm on the frame
                        cv2.putText(frame, "****************Fatigue--Driver!!!****************", (10, 325),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
        

                #否则，眼宽比不低于眨眼阈值，因此重置计数器和警报
                else:
                    COUNTER = 0
                    cv2.putText(frame, "Eyes Open ", (10, 30),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

                cv2.putText(frame, "EAR: {:.2f}".format(ear), (480, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

                # 打呵欠的检测

                if mouEAR > MOU_AR_THRESH:
                    cv2.putText(frame, "Yawning ", (10, 70),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                    yawnStatus = True
                    output_text = "Yawn Count: " + str(yawns + 1)
                    cv2.putText(frame, output_text, (10,100),cv2.FONT_HERSHEY_SIMPLEX, 0.7,(255,0,0),2)
                else:
                    yawnStatus = False
                    cv2.putText(frame, "Yawn Count: " + str(yawns), (10,100),cv2.FONT_HERSHEY_SIMPLEX, 0.7,(255,0,0),2)

                if prev_yawn_status == True and yawnStatus == False:
                    yawns+=1

                cv2.putText(frame, "MAR: {:.2f}".format(mouEAR), (480, 60),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

                cv2.putText(frame, "{}".format(picturename), (480, 90),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                
                cv2.putText(frame, "Author:WU Fan",(480, 120),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            # show the frame
            cv2.imshow("Wu Fan", frame)
            key = cv2.waitKey(1) & 0xFF

            # if the `q` key was pressed, break from the loop
            if key == ord("q"):
                break
        cap.release()
        print("图片：",picturename)
# do a bit of cleanup
cv2.destroyAllWindows()

