#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPSILON = 1e-7;

enum nRoots {
	NO_ROOTS = 0,
	ONLY_ONE_ROOT = 1,
	TWO_ROOTS = 2,
	INF_ROOTS = 3,
	ERROR = 4
};


/*Исправления:
* функции написаны для юнитестов
* изменена функция equal
* assert добален к каждой функции, где есть указатели
*/


int is_equal(double a, double b)
{
	if ((a / EPSILON <= 10) || (b / EPSILON) <= 10)
	{
		if ((a - b) == 0)
			return 1;
		else
			return 0;
	}
	else
	{
		if (fabs(a - b) <= EPSILON)
			return 1;
		else
			return 0;
	}
}



int fn_safe_scanf(int n_Try_enter, double* a, double* b, double* c)			//функция безопастного ввода символов с клавиатуры
{
	assert(a != b != NULL);
	assert(a != c != NULL);
	assert(b != c != NULL);
	
	int nCharacters = scanf_s("%lf %lf %lf", a, b, c);
	int nTry = 0;

	while (nTry < n_Try_enter && nCharacters != 3)
	{
		while (getchar() != '\n') { ; }										//отчистка буфера
		printf("error, please, try again, you have %d tryes to enter\n", n_Try_enter - nTry);
		nCharacters = scanf_s("%lf %lf %lf", a, b, c);
		nTry++;
	}

	if (nCharacters == 3)
		return 0;
	else
	{
		printf("there are too many incorrect inputs\n");
		return ERROR;
	}
}


double fn_line_solver(double a, double b)
{
	return (-b / a);
}

int fn_sq_solver(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (is_equal(a, 0) == 1)
	{

		if (is_equal(b, 0) == 1)
		{
			if (is_equal(c, 0) == 1)
				return (INF_ROOTS);

			else
				return(NO_ROOTS);
		}
		else							//b != 0
		{
			*x1 = fn_line_solver(b, c);
			return (ONLY_ONE_ROOT);
		}
	}
	else								// a, b, c != 0
	{
		double D = b * b - 4 * a * c;
		if (D - EPSILON > 0)
		{
			double z = sqrt(D);
			double line = 2 * a;

			*x1 = (-b - z) / line;
			*x2 = (-b + z) / line;

			return (TWO_ROOTS);
		}
		else if (is_equal(D, 0) == 1)
		{
			*x1 = -b / 2 / a;

			return (ONLY_ONE_ROOT);
		}
		else		//D < 0
		{
			return (NO_ROOTS);
		}
	}
	return ERROR;

}

int print_result(int nRoots)											// для вывода количества корней
{
	switch (nRoots) {		
	case NO_ROOTS:
		printf("no roots\n");
		break;
	case ONLY_ONE_ROOT:
		printf(" only one root\n");
		break;
	case TWO_ROOTS:
		printf("two roots\n");
		break;
	case INF_ROOTS:
		printf("infinite roots\n");
		break;
	default:		//ERROR
		printf("something wrong %d\n", nRoots);
	}
	return 0;
}


void uni_test_sqrt_solver_NO_ROOTS_or_INF_ROOTS(int count_roots_from_function, int n_roots_must_be, int test_number,\
	double a, double b, double c)
{
	if (count_roots_from_function != n_roots_must_be)
	{
		printf("error test №%d: a = %lf, b = %lf, c = %lf;\n "
			"count of roots must be %d\n"
			"int the result of program work %d \n", test_number, a, b, c,\
			n_roots_must_be, count_roots_from_function);
	}
}


void uni_test_sqrt_solver_ONLY_ONE_ROOT(int count_roots_from_function, int n_roots_must_be, int test_number, \
	double a, double b, double c, double x1, double res1)
{
	if (count_roots_from_function != n_roots_must_be || x1 != res1)
	{
		printf("error test №%d: a = %lf, b = %lf, c = %lf;\n "
			"count of roots must be %d\n"
			"int the result of program works %d \n"
			"roots : \n program work result x1 = %lf\n"
			"x1 should be = %lf", test_number, a, b, c, n_roots_must_be, \
			count_roots_from_function, x1, res1);
	}
}


void uni_test_sqrt_solver_TWO_ROOTS(int count_roots_from_function, int n_roots_must_be, \
									   int test_number, double a, double b, double c, double x1,\
									   double x2, double res1, double res2)
{
	if(!((is_equal(x1,res1) && is_equal(x2, res2)) || (is_equal(x1,res2) && is_equal(x2,res1))))
	{
		printf("error test №%d: a = %lf, b = %lf, c = %lf;\n "
			"count of roots must be %d\n"
			"int the result of program work %d \n"
			"roots : \n program work result x1 = %lf; x2 = %lf\n"
			"x1 should be = %lf; x2 should be = %lf\n", test_number, a, b, c, n_roots_must_be, \
			count_roots_from_function, x1, x2, res1, res2);
	}
}


int uni_test_sqrt_solver_main(int test_number, double a, double b, double c, int n_roots_must_be, double res1, \
	double res2, double x1, double x2)
{
	int count_roots_function = fn_sq_solver(a, b, c, &x1, &x2);
	switch (n_roots_must_be)
	{
	case NO_ROOTS:
		uni_test_sqrt_solver_NO_ROOTS_or_INF_ROOTS(count_roots_function, n_roots_must_be, test_number, a, b, c);
		break;
	case ONLY_ONE_ROOT:
		uni_test_sqrt_solver_ONLY_ONE_ROOT(count_roots_function, n_roots_must_be, test_number, a, b, c, x1, res1);
		break;
	case TWO_ROOTS:
		uni_test_sqrt_solver_TWO_ROOTS(count_roots_function, n_roots_must_be, test_number, a, b, c, \
			x1, x2, res1, res2);
		break;
	case INF_ROOTS:
		uni_test_sqrt_solver_NO_ROOTS_or_INF_ROOTS(count_roots_function, n_roots_must_be, test_number, a, b, c);
		break;


	default:
		printf("ERROR");
		break;
	}
	return 0;
}


int ft_uni_tests()
{
	double x1 = NAN, x2 = NAN;
	uni_test_sqrt_solver_main(1, 1, -2, 1, 1, 1, NAN, x1, x2);
	uni_test_sqrt_solver_main(2, 1, -5, 6, 2, 2, 3, x1, x2);
	uni_test_sqrt_solver_main(3, 0, 0, 0, 3, NAN, NAN, x1, x2);
	uni_test_sqrt_solver_main(4, 17, -79, 91, 2, 2.5376502908611918, 2.10940853266822, x1, x2);
	uni_test_sqrt_solver_main(5, 94, 399, -123, 2, 0.28864267688603085, -4.533323527949861, x1, x2);
	uni_test_sqrt_solver_main(6, 70, 140, 70, 1, -1, NAN, x1, x2);
	uni_test_sqrt_solver_main(7, 84, -3, 12, 0, NAN, NAN, x1, x2);
	uni_test_sqrt_solver_main(8, 36, - 1245, 4119, 2, 30.87787546251713, 3.705457870816206, x1, x2);
	uni_test_sqrt_solver_main(9, 3124, -12389741, 1234, 2, 3965.9861359968572, 0.00009959853324614627, x1, x2);
	uni_test_sqrt_solver_main(10, 0.123, -0.9812, 0.00013456, 2, 7.977098631801949, 0.00013714055577466108, x1, x2);
	return 0;
}

int main()
{
	double a = NAN;
	double b = NAN;
	double c = NAN;
	double x1 = NAN;
	double x2 = NAN;

	printf("print numbers a b c\n");
	int nTry_to_enter = 3;
	fn_safe_scanf(nTry_to_enter, &a, &b, &c);
	int nRoot = fn_sq_solver(a, b, c, &x1, &x2);
	printf("x1 = %lf x2 = %lf", x1, x2);
	printf("\n\n");
	ft_uni_tests();

	print_result(nRoot);
	return 0;
}
