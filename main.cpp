/// @file main.cpp

#include "doc.h"

int isEqual(double a, double b)									// сравнение чисел разных типов
{
	if (fabs(a - b) < EPSILON)
		return 1;
	else
		return 0;
}


int fn_safe_scanf(int n_Try_enter, double* a, double* b, double* c)			//функция безопастного ввода символов с клавиатуры
{
	int nCharacters = scanf("%lf %lf %lf", a, b, c);
	int nTry = 0;

	while (nTry < n_Try_enter && nCharacters != 3)
	{
		while (getchar() != '\n') { ; }										//отчистка буфера
		printf("error, please, try again, you have %d tryes to enter\n", n_Try_enter - nTry);
		nCharacters = scanf("%lf %lf %lf", a, b, c);
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

	if (isEqual(a, 0) == 1)
	{

		if (isEqual(b, 0) == 1)
		{
			if (isEqual(c, 0) == 1)
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
		else if (isEqual(D, 0) == 1)
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

int PrintfResult(int nRoots)											// для вывода количества корней
{
	switch (nRoots) {		// z переделать
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

int Uni_Test_sqrt_solver()
{
	double a = NAN, b = NAN, c = NAN;
	double x1 = NAN, x2 = NAN;
	double res1 = NAN, res2 = NAN;

// uni test 1

	a = 1;
	b = -2;
	c = 1;
	res1 = 1;

	int root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(isEqual(x1, res1) && root_count == 1))
	{
		printf("error test 1: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, count of roots = %d\n"
			"should be x1 = %lf, count of roots = 1\n", a, b, c, x1, root_count, res1);
	}
	//uni test 2
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 1;
	b = -5;
	c = 6;
	res1 = 2;
	res2 = 3;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(((isEqual(x1, res1) == 1 && isEqual(res2, x2) == 1) || (isEqual(res1, x2) && isEqual(res2, x1)))\
		&& root_count == TWO_ROOTS))
	{
		printf("error test 2: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 2\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 3

	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 0;
	b = 0;
	c = 0;
	res1 = NAN;
	res2 = NAN;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!( root_count == INFINITY) && x1 == NAN && x2 == NAN)
	{
		printf("error test : a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 3\n", a, b, c, x1, x2, root_count, res1, res2);
	}
	return 0;

	//uni test 4
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 24;
	b = -527;
	c = 17;
	res1 = 21.926027740102793;
	res2 = 0.03230559323054175;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(((isEqual(x1, res1) == 1 && isEqual(res2, x2) == 1) || (isEqual(res1, x2) && isEqual(res2, x1)))\
		&& root_count == TWO_ROOTS))
	{
		printf("error test 4: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 2\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 5
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 448;
	b = 0;
	c = -87808;
	res1 = 14;
	res2 = -14;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(((isEqual(x1, res1) == 1 && isEqual(res2, x2) == 1) || (isEqual(res1, x2) && isEqual(res2, x1)))\
		&& root_count == TWO_ROOTS))
	{
		printf("error test 5: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 2\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 6
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 448;
	b = 0;
	c = 87808;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(x1 == NAN && x2 == NAN && root_count == TWO_ROOTS))
	{
		printf("error test 6: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 3\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 7
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 126;
	b = 23;
	c = 878;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(x1 == NAN && x2 == NAN && root_count == NO_ROOTS))

	{
		printf("error test 7: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 0\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 7
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 1;
	b = -10;
	c = 24;
	res1 = 6;
	res2 = 4;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(((isEqual(x1, res1) == 1 && isEqual(res2, x2) == 1) || (isEqual(res1, x2) && isEqual(res2, x1)))\
		&& root_count == TWO_ROOTS))
	{
		printf("error test 7: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 2\n", a, b, c, x1, x2, root_count, res1, res2);
	}

	//uni test 8
	x1 = NAN, x2 = NAN;
	res1 = NAN, res2 = NAN;
	a = 0;
	b = 448;
	c = -87808;
	res1 = 196;

	root_count = fn_sq_solver(a, b, c, &x1, &x2);
	if (!(((isEqual(x1, res1) == 1 && isEqual(res2, x2) == 1) || (isEqual(res1, x2) && isEqual(res2, x1)))\
		&& root_count == TWO_ROOTS))
	{
		printf("error test 5: a = %lf, b = %lf, c = %lf;\n "
			"x1 = %lf, x2 = %lf, count of roots = %d\n"
			"should be x1 = %lf, x2 = %lf, count of roots = 2\n", a, b, c, x1, x2, root_count, res1, res2);
	}
}

int main()
{
	double a = NAN;
	double b = NAN;
	double c = NAN;
	double x1 = NAN;
	double x2 = NAN;

	Uni_Test_sqrt_solver();
	printf("print numbers a b c\n");
	int nTry_to_enter = 3;
	fn_safe_scanf(nTry_to_enter, &a, &b, &c);
	int nRoot = fn_sq_solver(a, b, c, &x1, &x2);
	PrintfResult(nRoot);
	return 0;
}
