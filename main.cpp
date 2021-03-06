﻿// main.cpp : Defines the entry point for the console application.
//
/*
Author: Brandon O'Briant
Date: 03/01/2018
Program: Linear Regression 

Takes in x and y values, performs linear regression using gradient descent. Each
iteration is printed to the console with the final resutl displayed at the end.
Ex:
gradient_a:     0.0544319 , gradient_b: -0.196517
Error 1.39632
6.08252

--Things to add:

-Function to take in data from file. 
-Train,test, split with KFold Crossvalidation
-Evaluation Metrics
-QT data visualization

*/

#include "stdafx.h"
#include "LinearRegression.h"
#include <iostream>

using namespace std;




// run program
int main(int argc, char ** argv)
{   

	//y input values
	vector<double> y({ 55.6, 23.1, 47.6, 31.7, 40.0 });

	//x input values
	vector<double> x({ 1, 2, 3, 4, 5});

	//instantiate LinearRegression Clas
	LinearRegression linear_regression(x, y);

	//train the regression algorithm
	//iterations is 1000
	//initial value 
	linear_regression.trainAlgorithm(1000, 5, -10);

	//output value of regression
	cout << "Regression result : " << linear_regression.regression(5) << endl;


    return 0;
}

