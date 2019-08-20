# Chapter4 频率域滤波
## 4.1 背景
用傅里叶级数或变换表示的函数特征完全可以通过 **傅里叶反变换**来重建，而不会丢失任何信息。它可以使我们工作于 “傅里叶域”，而且在返回函数的原始域时不会丢失任何信息。

**复数**：
$$
C=R+\mathrm{j} I
$$

**共轭复数**：
$$
C^{*}=R-\mathrm{j} I
$$

**极坐标下复数**：
$$
C=|C|(\cos \theta+j \sin \theta)
$$
$
|C|=\sqrt{R^{2}+I^{2}}
$

使用 **欧拉公式**：
$$
\mathrm{e}^{\mathrm{j} \theta}=\cos \theta+\mathrm{j} \sin \theta
$$

复数表示为：
$$
C=|C| \mathrm{e}^{\mathrm{j} \theta}
$$

## 4.2 傅里叶级数
具有T周期的连续变量t的周期函数$f(t)$可以被描述为乘以适当系数的正弦和余弦和。
$$
f(t)=\sum_{n=-\infty}^{\infty} c_{n} \mathrm{e}^{\mathrm{j} \frac{2 \pi n}{T} t}
$$
$$
c_{n}=\frac{1}{T} \int_{-T / 2}^{T / 2} f(t) \mathrm{e}^{-\mathrm{j} \frac{2 \pi n}{T} \mathrm{d} t,} \quad n=0, \pm 1, \pm 2, \cdots
$$



