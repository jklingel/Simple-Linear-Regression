/* simpLinearRegression     */
/* Jan Klingel, 06/2026     */
/* Code version for POWER C */
/* and MOS 6502/6510 CPU    */

#include <stdio.h>
#include <math.h>

#define MAXVAL 50

float getSigma(val,n)
float val[MAXVAL];
int n;
{
  int i;
  float mu;

  i=0;
  mu=0.0;
  while(i < n) {
    mu += val[i];
    i += 1;
  }
  mu /= n;
  printf("Mean mu: %.2f\n", mu);

  i=0;
  while(i < n) {
    val[i]=(val[i]-mu)*(val[i]-mu);
    i++;
  }

  i=0;
  float variance = 0.0;
  while(i<n) {
    variance += val[i];
    i++;
  }
  variance /= n;

  return(sqrt(variance));
}

float calculate_correlation(x,y,n)
float x[];
float y[];
int n; 
{
  float sum_X = 0, sum_Y = 0, sum_XY = 0;
  float sum_X2 = 0, sum_Y2 = 0;
  int i;

  for (i = 0; i < n; i++) {
    sum_X += x[i];
    sum_Y += y[i];
    sum_XY += x[i] * y[i];
    sum_X2 += x[i] * x[i];
    sum_Y2 += y[i] * y[i];
  }

  float numerator = (n * sum_XY) - (sum_X * sum_Y);

  float denominator = sqrt((n * sum_X2 - (sum_X * sum_X)) * (n * sum_Y2 - (sum_Y * sum_Y)));

  if (denominator == 0)
    return(0.0);

  return(numerator / denominator);
}

int main(void)
{
  int i, n = 0;
  float pprice = 0.0;
  int squaref = 0;
  float r,sx,sy,a,b = 0.0;
  float xbar, ybar;

  float price[MAXVAL];
  price[0] = 316000.0;
  price[1] = 277000.0;
  price[2] = 155000.0;
  price[3] = 253000.0;
  price[4] = 211000.0;
  price[5] = 329000.0;
  price[6] = 317000.0;
  price[7] = 360000.0;
  price[8] = 204000.0;
  price[9] = 250000.0;
  price[10] = '\0';

  float square[MAXVAL];
  square[0] = 1852.0;
  square[1] = 1975.0;
  square[2] = 1176.0;
  square[3] = 1550.0;
  square[4] = 1458.0;
  square[5] = 2689.0;
  square[6] = 2259.0;
  square[7] = 2763.0;
  square[8] = 1325.0;
  square[9] = 1992.0;
  square[10] = '\0';

  while(price[n] != '\0')
    n++;
  printf("Number of Elements n: %d\n", n);

  xbar = 0.0;
  for(i=0;i<n;i++)
    xbar += square[i];
  xbar /= n;
  printf("xbar: %f\n", xbar);

  ybar = 0.0;
  for(i=0;i<n;i++)
    ybar += price[i];
  ybar /= n;
  printf("ybar: %f\n", ybar);

  r = calculate_correlation(square,price,n);
  printf("r: %f\n", r);

  sx = getSigma(square,n);
  printf("Standard deviation sx: %.2f\n", sx);

  sy = getSigma(price,n);
  printf("Standard deviation sy: %.2f\n", sy);

  b = r*sy/sx;
  a = ybar-b*xbar;
  printf("Coefficient a and b: %.2f, %.2f\n", a, b);

  printf("Enter the square footage of the house: ");
  scanf("%d", &squaref);
  pprice = b*squaref+a;
  printf("The estimated house price is: %.0f\n", pprice);
  return(0);
}
