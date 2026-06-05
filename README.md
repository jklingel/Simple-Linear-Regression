# Simple-Linear-Regression
Calculate an estimated house price using simple linear regression (machine learning).

Calculate the correlation between two variables x and y. Here: The correlation between the square footages of real houses and their selling price. Then, estimate the selling price of a house with a given square footage. This represents a simple machine learning algorithm.

The term simple linear regression means that we deal with only two value xn and yn correlating with each other. Dealing with more correlated values is called multiple linear correlation. An example would be calculating an estimated house price from given square feet, location, and builder.

This is basically how it works: All points xn (square feet) and yn (prices) are plotted on a graph. The program then calculates a straight (linear) line through all points in such a way that all points have the smallest possible distance e-bar from the line. The formula for a straight line is y = b*x + a. The coefficient b is the slope, and the coefficient a describes the point where the line crosses the y-axis. A new y-value (here: predicted price) is obtained by inserting the floor area (square feet) of a new house as the x-value into the formula.

Formulas used:                               

y=b*x+a

 	b is the coefficient value, the slope of the line through
	all {xn|yn} points.

b=r*(sy/sx)

	r is the Pearson correlation coefficient in the range of -1
	to 1. A number close to -1 or 1 is a sign for a significant
	correlation. 0 means no correlation between x and y.
	sx and sy are the standard deviation for xn and yn.

a=y-bar - b*x-bar

	x-bar is the mean of xn, y-bar the mean of yn.

Using GCC, compile source code with

$ gcc -o simpLinearRegression simpLinearRegression.c -lm
