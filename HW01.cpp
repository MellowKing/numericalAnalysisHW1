#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

void iteration(int a, int b, int c, double x, int i, int iterations) {
  cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
  if (i > iterations) return;
  i++;
  double nextX = 10 / (double) a * (b / (double) 40 + pow(-1, c) * sin(x));
  if ((int) (x * 1000000) == (int) (nextX * 1000000)) {
    cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
    return;
  }
  iteration(a, b, c, nextX, i, iterations);
}

void newton(int a, int b, int c, double x, int i, int iterations) {
  cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
  if (i > iterations) return;
  i++;
  double numerator = a / (double) 10 * x - b / (double) 40 - pow(-1, c) * sin(x);
  double denominator = a / (double) 10 - pow(-1, c) * cos(x);
  double nextX = x - numerator / denominator;
  if ((int) (x * 1000000) == (int) (nextX * 1000000)) {
    cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
    return;
  }
  newton(a, b, c, nextX, i, iterations);
}

void newtonModified(int a, int b, int c, double x, double x_0, int i, int iterations) {
  cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
  if (i > iterations) return;
  i++;
  double numerator = a / (double) 10 * x - b / (double) 40 - pow(-1, c) * sin(x);
  double denominator = a / (double) 10 - pow(-1, c) * cos(x_0);
  double nextX = x - numerator / denominator;
  if ((int) (x * 1000000) == (int) (nextX * 1000000)) {
    cout << "\tx_" << i << " = " << setprecision(6) << x << endl;
    return;
  }
  newtonModified(a, b, c, nextX, x_0, i, iterations);
}

double foo(int a, int b, int c, double x) {
  return a / (double) 10 * x - b / (double) 40 - pow(-1, c) * sin(x);
}

void secant(int a, int b, int c, double x_0, double x_1, int i, int iterations) {
  cout << "\tx_" << i << " = " << setprecision(6) << x_0 << endl;
  if (i > iterations) return;
  i++;
  double newX_0 = x_1;
  x_1 = x_1 - (x_1 - x_0) / (foo(a, b, c, x_1) - foo(a, b, c, x_0)) * foo(a, b, c, x_1);
  if ((int) (x_1 * 1000000) == (int) (x_0 * 1000000)) {
    cout << "\tx_" << i << " = " << setprecision(6) << x_1 << endl;
    return;
  }
  x_0 = newX_0;
  secant(a, b, c, newX_0, x_1, i, iterations);
}

// for finding the value that couldn't be found
// with the iteration method otherwise. Not for general
// equation solving. Solves only the equation I needed.
void myIteration2(double x, int i, int iterations) {
  cout << "\tx_" << i << " = " << setprecision(5) << x << endl;
  if (i > iterations) return;
  i++;
  double nextX = (3 / 5.0) * x - (1 / 10.0) - sin(x) + x;
  if ((int) (x * 10000000) == (int) (nextX * 10000000)) {
    cout << "\tx_" << i << " = " << setprecision(5) << x << endl;
    return;
  }
  myIteration2(nextX, i, iterations);
}

int main() {
  int a = 6;
  int b = 4;
  int c = 2;
  double x_0 = -2;
  double secant_x_1 = -1;
  int iterations = 100;

  cout << "ITERATION METHOD" << endl;
  iteration(a, b, c, x_0, 0, iterations);
  cout << endl << "NEWTON'S METHOD" << endl;
  newton(a, b, c, x_0, 0, iterations);
  cout << endl << "MODIFIED NEWTON'S METHOD" << endl;
  newtonModified(a, b, c, x_0, x_0, 0, iterations);
  cout << endl << "SECANT METHOD" << endl;
  secant(a, b, c, x_0, secant_x_1, 0, iterations);

  // cout << "ITERATION METHOD 2" << endl;
  // myIteration2(-0.5, 0, 100);
  return 0;
}
