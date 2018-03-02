## Linear Regression with Gradient Descent (C++)

Takes in x and y values, performs linear regression using gradient descent. Each
iteration is printed to the console with the final resutl displayed at the end.
Ex:
gradient_a:     0.0544319 , gradient_b: -0.196517
Error 1.39632
6.08252

* Least Square minimizes the square of the distance from the line to the data point

* The error function we are aiming to minimize is defined as :<br>
Error(a, b) = (1 / N) SUM_ { i = 1 }{N} (y_i - (ax_i + b)) ^ 2

#### The minimum is obtained when the gradient is equal to zero

* Differentiate with respect to a :<br><br>
  GRADIENT_a E = (2 / N) SUM_ { i = 1 }{N} -x(y_i - (ax_i + b))
 
* Differentiate with respect to b :<br><br>
  GRADIENT_b E = (2 / N) SUM_ { i = 1 }{N} -(y_i - (ax_i + b))

#### Calculating  the Step Size

* Why: Keeping it fixed is not the best idea, if it is too large solution can
will not converge.
* Use backtracking line serach, where we decrease the step size by a certain amount
each iterationsation
* We can compute an approximate of the step size from a formula
* Or we can compute the next optimum step size
* We want the step size to decrease monotonically as the algorithm converges
* We can achieve this from the folllowing two equations :<br><br>
1. alpha = 2 / (n + 2) --half the step size each time<br>
2. alpha_{ n + 1 } = beta * alpha{ n }, where beta\in(0, 1)

#### Things to add:

* Function to take in data from file. 
* Train,test, split with KFold Crossvalidation
* Evaluation Metrics
* QT data visualization

#### Files

* [main.cpp](main.cpp)
* [LinearRegression.h](LinearRegression.h)<br><br>
<a href="https://obrianbl.github.io/">Return to Main Page</a>
