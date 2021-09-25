/// @file doc.h

#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1e-4;

enum nRoots {
	NO_ROOTS = 0,
	ONLY_ONE_ROOT = 1,
	TWO_ROOTS = 2,
	INF_ROOTS = 3,
	ERROR = 4
};

//! @brief Cmp 2 number
//! @param[in] a - 1st param
//! @param[in] b - 2nd param
//! @return 1 - if numbers are compared
//!         2 - if numbers are not compared
int isEqual(double a, double b);

//! @brief cheking on correctness entered symbols by scnaf
//! @note  there are limit on the number of input attempts
//! @param[in] numbers of limits on the
//! @param[out] the first coefficient in the quadratic equation
//! @param[out] the second coefficient in the quadratic equation
//! @param[out] the third coefficient in the quadratic equation
//! @return     0 - if everything right
//!                ERROR - overrun limit of input attempts
int fn_safe_scanf(int n_Try_enter, double* a, double* b, double* c);

//! @brief if the first coefficient = 0, this function will help you
//! @param[in] the first coefficient of line equation
//! @param[in] the second coefficient of line equation
//! @return    root of line equation
double fn_line_solver(double a, double b);

//! @brief function, which solve quadratic equation
//! @param[in] the first coefficient in the quadratic equation
//! @param[in] the second coefficient in the quadratic equation
//! @param[in] the third coefficient in the quadratic equation
//! @param[out] first root of quadratic equation, if there is't any solutition\
or there are infinity roots x1 will be NAN
//! @param[out] second root of quadratic equation, if there is't any solutition\
or there are infinity roots or only one root x2 will be NAN
//! @return this function return count of roots:
//!          NO_ROOTS - if there isn't solution of quadratic equation
//!          ONLY_ONE_ROOT -  if there is only one root of quadratic equation
//!          TWO_ROOTS - if there are two roots of quadratic equation
//!          INF_ROOTS - if there are infinity roots of quadratic equation
//!          ERROR - if something wrong
int fn_sq_solver(double a, double b, double c, double* x1, double* x2);


//! @brief this function print result of function fn_sq_solver - count of roots
//! @param[in] count of roots, received of fn_sq_solver
//! @return     0 - if everything right
int PrintfResult(int nRoots);


//! @brief this function substitutes the coefficients into the function and compares the obtained values\
 of the roots and their number with the reference
//! @return  0 - if everything right
int Uni_Test_sqrt_solver();
