/* simpLinearRegression     */
/* Jan Klingel, 06/2026     */
/* Code version for POWER C */
/* and MOS 6502/6510 CPU    */

#include <stdio.h>
#include <math.h>

#define MAXVAL 100

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
  int pprice = 0;
  int squaref = 0;
  float r,sx,sy,a,b = 0.0;
  int xbar, ybar;

  float price[MAXVAL];
  price[0] = 3160;
  price[1] = 2770;
  price[2] = 1550;
  price[3] = 2530;
  price[4] = 2110;
  price[5] = 3290;
  price[6] = 3170;
  price[7] = 3600;
  price[8] = 2040;
  price[9] = 2500;
  price[10] = '\0';

  float square[MAXVAL];
  square[0] = 1852;
  square[1] = 1975;
  square[2] = 1176;
  square[3] = 1550;
  square[4] = 1458;
  square[5] = 2689;
  square[6] = 2259;
  square[7] = 2763;
  square[8] = 1325;
  square[9] = 1992;
  square[10] = '\0';

  while(price[n] != '\0')
    n++;
  printf("Number of Elements n: %d\n", n);

  xbar = 0;
  for(i=0;i<n;i++)
    xbar += square[i];
  xbar /= n;
  printf("xbar: %d\n", xbar);

  ybar = 0;
  for(i=0;i<n;i++)
    ybar += price[i];
  ybar /= n;
  printf("ybar: %d\n", ybar);

  r = calculate_correlation(square,price,n);
  printf("r: %f\n", r);

  sx = getSigma(square,n);
  printf("Standard deviation sx: %f\n", sx);

  sy = getSigma(price,n);
  printf("Standard deviation sy: %f\n", sy);

  b = r*sy/sx;
  a = ybar-b*xbar;
  printf("Coefficient a and b: %f, %f\n", a, b);

  printf("Enter the square footage of the house: ");
  scanf("%d", &squaref);
  pprice = b*squaref+a;
  printf("The estimated house price is: %d\n", pprice);
  return(0);
}