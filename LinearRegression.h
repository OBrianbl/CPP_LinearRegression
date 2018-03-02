#ifndef LINEARREGRESSION_H_INCLUDED
#define LINEARREGRESSION_H_INCLUDED
/*
- Least Square minimizes the square of the distance from the line to the data point
- The error function we are aiming to minimize is defined as :

Error(a, b) = (1 / N) SUM_ { i = 1 }{N} (y_i - (ax_i + b)) ^ 2

-------- - The minimum is obtained when the gradient is equal to zero---------- -

-- - Differentiate with respect to a :

GRADIENT_a E = (2 / N) SUM_ { i = 1 }{N} -x(y_i - (ax_i + b))

-- - Differentiate with respect to b :

GRADIENT_b E = (2 / N) SUM_ { i = 1 }{N} -(y_i - (ax_i + b))

--------------------------------------------------------------------------------

----------------Calculating  the Step Size--------------------------------------
- Why: Keeping it fixed is not the best idea, if it is too large solution can
will not converge.
- Use backtracking line serach, where we decrease the step size by a certain amount
each iterationsation
- We can compute an approximate of the step size from a formula
- Or we can compute the next optimum step size

--We want the step size to decrease monotonically as the algorithm converges
--We can achieve this from the folllowing two equations :
1. alpha = 2 / (n + 2) --half the step size each time
2. alpha_{ n + 1 } = beta * alpha{ n }, where beta\in(0, 1)


*/


#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

//Linear Regression Class
class LinearRegression {

	//public member functions and data variables
public:
	//default constructor
	LinearRegression() {}

	// default deconstructor
	~LinearRegression() {}

	//non-default contstructor
	//initialize vector passes for x, y values of private data members
	LinearRegression(vector<double> & x_values_, vector<double> & y_values_) : x_values(x_values_),
		y_values(y_values_), number_of_elements(y_values_.size()), previous_error(std::numeric_limits<double>::max()) {}

	//interface calculates coefficients for line of best fit
	//number_of_iterationsations_ is the number of iterationsations of gradient descent we want to perform
	//a_init_ is initial coefficient for a
	//b_init_ is the initial coefficients for b
	void trainAlgorithm(double number_of_iterations_, double a_init_, double b_init_) {
		//keep track of number of iterationsations we are taking
		//initialized to 0
		int iterations = 0;

		//initialize coefficient value for a
		a = a_init_;

		//initialize coefficient value for b
		b = b_init_;

		//calculate the gradient descent
		//while iterationss is less than the number of iterationsations we want, peform gradient descent
		//while loop prefered so can introduce check to see if convergence has occured
		//
		while (!isConverged() && iterations < number_of_iterations_) {
			//update the gradient
			//step, type double, is the multiplier of the gradient when we subtract it
			//step size is halved at iterationsation
			double step = 2 / double(iterations + 2);//

													 //variable for gradient, initialized to 0
			double gradient_a = 0;

			//variable for gradient, initialized to 0
			double gradient_b = 0;

			//compute gradient with respect to a
			//summing up over all the data points, then multiplying by -x, value of input, times the difference
			//this is the differientiation with respect to a
			//continue, as long as i is less than the number of elements
			for (int i = 0; i < number_of_elements; i++) {
				//accumulating the values
				// -1 was taken out, but will be used in the update
				//gradient_a is the SUM{i=1}{N} x_i *((ax_i + b)-y_i))
				gradient_a += x_values[i] * ((a * x_values[i] + b) - y_values[i]);

			}
			// multiplying gradient_a, a gradient, by (2/N)
			gradient_a = (2 * gradient_a) / number_of_elements;

			//compute gradient with respect to b
			//summing up over all the data points, then multiplying by x, value of input, times the difference
			//this is differenitaion with respect to b formula
			//continue as long as i is less than the number of elements
			for (int i = 0; i < number_of_elements; i++) {
				//accumulating the values
				//gradient_b is the SUM_{i=1}{N}  (y_i-(ax_i + b))
				gradient_b += ((a * x_values[i] + b) - y_values[i]);
			}
			//multiply gradient_b, b gradient, by (2/N)
			gradient_b = (2 * gradient_b) / number_of_elements;

			/*--------------take a step--------------------*/
			//update the value of a
			a -= (step * gradient_a);

			//update the value of b
			b -= (step * gradient_b);

			//output, values of a and b coeficients for sanity check
			cout << "a:\t" << a << " , b:\t" << b << endl;

			//output gradient
			cout << "gradient_a:\t" << gradient_a << " , gradient_b:\t" << gradient_b << endl;

			//increment iterations
			iterations++;

		}
	}

	//regress function on certain value on x, use after line of best fit
	double regression(double x_) {
		//standard regression formula
		//result, type doulbe, result (y) = a*x + b
		double result = a * x_ + b;
		return result;
	}

	//private member functions and data variables
private:
	vector<double> x_values;//vectors hold x vals to train against
	vector<double> y_values;//vectors hold y vals to train against
	double number_of_elements;//number of elements (N)
	double previous_error;//stores the previous error
	double a;//coefficient a
	double b;//coefficient b

			 //compare the previous error to the current error
			 //error is the sum of the differences squared, over N
			 // (1/N) SUM_{i=1}{N} (y_i - (ax_i + b))^2
	bool isConverged() {
		double error = 0;

		//thress, type double, to see the previous error and current error in a range of each other 
		double threshold = 0.001;

		//loop over all the values
		for (int i = 0; i < number_of_elements; i++) {
			error += ((a * x_values[i] + b) - y_values[i]) * ((a * x_values[i] + b) - y_values[i]);
		}
		error /= number_of_elements;
		cout << "Error " << error << endl;
		//check if converged: 1 converged, 0 not converged
		//if error is above the lower threshold and error is below the upper threshold true, else false
		bool result = (abs(error) >(previous_error - threshold) && abs(error) < (previous_error + threshold)) ? true : false;
		//update old error
		previous_error = abs(error);
		return result;
	}

};

#endif // LINEARREGRESSION_H_INCLUDED