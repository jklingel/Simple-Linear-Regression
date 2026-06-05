/* Simple Linear Regression - Calculate the correlation between two */
/* variables x and y. Here: The correlation between the square      */
/* footages of houses and their selling price. Then, estimate the   */
/* selling price of a house with a given square footage. This       */
/* represents a simple machine learning algorithm.                  */
/* Jan Klingel, 06/2025                                             */

// y=b*x+a
// 	b is the coefficient value, the slope of the line through
//	all {xn|yn} points
// b=r*(sy/sx)
//	r is the Pearson correlation coefficient in the range of -1
//	to 1. A number close to -1 or 1 is a sign for a big
//	correlation. 0 means no correlation between x and y.
//	sx and sy are the standard deviation for xn and yn.
// a=y-bar - b*x-bar
//	x-bar is the mean of xn, y-bar the mean of yn

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXVAL 100 // Maxium of 100 x and 100 y values

/* getSigma() - calculate the standard deviation of n values        */
/* in array val[]                                                   */
/* Jan Klingel, 06/2026                                             */

float getSigma(val,n)
double val[MAXVAL];
int n;
{
  int i;
  float mu;

  // Calculate mean of mu
  i=0;
  mu=0.0;
  while(val[i] != '\0') {
    mu += val[i];
    i++;
  }
  mu /= n;
  printf("Mean mu: %.2f\n", mu);

  // Calculate (deviation from mean)²
  i=0;
  while(i<n) {
    val[i]=(val[i]-mu)*(val[i]-mu);
    i++;
  }

  // Calculate variance
  i=0;
  float variance = 0.0;
  while(i<n) {
    variance += val[i];
    i++;
  }
  variance = variance/n;

  // Calculate sigma = square root of variance
  return(sqrtf(variance));
}

// calculate_correlation()
// Function to calculate Pearson's correlation coefficient
float calculate_correlation(double x[], double y[], int n) {
    double sum_X = 0, sum_Y = 0, sum_XY = 0;
    double sum_X2 = 0, sum_Y2 = 0;

    for (int i = 0; i < n; i++) {
        sum_X += x[i];
        sum_Y += y[i];
        sum_XY += x[i] * y[i];
        sum_X2 += x[i] * x[i];
        sum_Y2 += y[i] * y[i];
    }

    // Numerator calculation (above the fraction bar)
    double numerator = (n * sum_XY) - (sum_X * sum_Y);

    // Denominator calculation (below the fraction bar)
    double denominator = sqrt((n * sum_X2 - (sum_X * sum_X)) * (n * sum_Y2 - (sum_Y * sum_Y)));

    // Handle edge case where denominator is zero (to avoid division by zero error)
    if (denominator == 0)
        return 0.0;

    return numerator / denominator; // equals r
}

int main(void) {
  unsigned int n, i;
  int pprice = 0; // predicted price
  int squaref = 0; // square footage of given house
  double r,sx,sy,a,b = 0.0; // correlation, standard deviation, coefficient a,b
  int xbar, ybar; // means of all x and y values

  double price[MAXVAL] = {316000,277000,155000,253000,211000,329000,317000,360000,204000,250000};
  double square[MAXVAL] = {1852,1975,1176,1550,1458,2689,2259,2763,1325,1992};

  // Calculate number of elements in price[];
  n = 0;
  while(price[n] != '\0')
    n++;
  printf("Number of elements n: %zu\n", n);

  // Calculate xbar (the mean of all x values)
  xbar = 0;
  for(i=0;i<n;i++)
    xbar += square[i];
  xbar /= n;
  printf("xbar: %u\n", xbar);

  // Calculate ybar (the mean of all y values)
  ybar = 0;
  for(i=0;i<n;i++)
    ybar += price[i];
  ybar /= n;
  printf("ybar: %u\n", ybar);

  // Calculate correlation r between x and y
  r = calculate_correlation(square,price,n);
  printf("r: %f\n", r);

  // Calculate standard deviation sx
  sx = getSigma(square,n);
  printf("Standard deviation sx: %f\n", sx);

  // Calculate standard deviation sy
  sy = getSigma(price,n);
  printf("Standard deviation sy: %f\n", sy);

  // Calculate coefficient a and b
  b = r*sy/sx;
  a = ybar-b*xbar;
  printf("Coefficient a and b: %f, %f\n", a, b);

  printf("Enter the square footage of the house: ");
  scanf("%d", &squaref);
  pprice = b*squaref+a;
  printf("The estimated house price is: %d\n", pprice);
  return(0);
}
