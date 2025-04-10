#include "Tests.h"

void plus_test_plus_plus() {

	// given
	BigNum f1("0.5");
	BigNum f2("0.75");
	BigNum correct_anw("1.25");


	// when 
	BigNum res = f1 + f2;

	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void plus_test_minus_minus() {

	// given
	BigNum f1("-12.5", 3);
	BigNum f2("-2.5", 2);
	BigNum correct_anw("-15", 3);

	// when 
	BigNum res = f1 + f2;

	// then

	if (res == correct_anw)	{
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void plus_test_plus_minus() {

	// given
	const BigNum f1("-10.15");
	const BigNum f2("10.75");
	const BigNum correct_anw("0.6015625");
	// when 
	const BigNum res = f1 + f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void plus_test_longnums() {

	// given
	BigNum f1("12345678910.5", 3);
	BigNum f2("12345678910.5", 2);
	BigNum correct_anw("24691357821", 3);

	// when 
	BigNum res = f1 + f2;

	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void all_plus_tests() {
	cout << "a + b: ";
	plus_test_plus_plus();
	cout << "-a + (-b): ";
	plus_test_minus_minus();
	cout << "a + (-b): ";
	plus_test_plus_minus();
	cout << "longnum1 + longnum2: ";
	plus_test_longnums();
}

void minus_test_plus_plus() {

	// given
	BigNum f1("12.5", 3);
	BigNum f2("2.5", 2);
	BigNum correct_anw("10", 3);

	// when 
	BigNum res = f1 - f2;
	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void minus_test_plus_minus() {

	// given
	BigNum f1("12.5", 3);
	BigNum f2("-2.5", 2);
	BigNum correct_anw("15", 3);

	// when 
	BigNum res = f1 - f2;
	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void minus_test_minus_plus() {

	// given
	BigNum f1("-12.5", 3);
	BigNum f2("2.5", 2);
	BigNum correct_anw("-15", 3);

	// when 
	BigNum res = f1 - f2;
	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void minus_test_longnums() {

	// given
	BigNum f1("12345678910.5", 3);
	BigNum f2("12345678910.5", 2);
	BigNum correct_anw("0", 3);

	// when 
	BigNum res = f1 - f2;

	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void all_minus_tests() {
	cout << "a - b: ";
	minus_test_plus_plus();
	cout << "-a + (-b): ";
	minus_test_minus_plus();
	cout << "-a - b: ";
	minus_test_plus_minus();
	cout << "longnum1 - longnum2: ";
	minus_test_longnums();

}


void multiply_test_plus_plus() {
	// given
	BigNum f1("15.84375");
	BigNum f2("-11.8125");
	BigNum correct_anw("-187.154296875");
	

	// when 
	BigNum res = f1 * f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void multiply_test_plus_minus() {
	// given
	BigNum f1("-20.625", 4);
	BigNum f2("2.5", 2);
	BigNum correct_anw("-51,5625", 4);

	// when 
	BigNum res = f1 * f2;
	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "WA\n";
	}
}

void multiply_test_minus_minus() {
	// given
	BigNum f1("-12.5", 3);
	BigNum f2("-2.5", 2);
	BigNum correct_anw("31,25", 3);

	// when 
	BigNum res = f1 * f2;
	// then

	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}


void multiply_test_longnums_integer() {
	// given
	BigNum f1("94376895077716", 2);
	BigNum f2("89021780", 2);
	BigNum correct_anw("8401599190691516654480", 2);

	// when 
	BigNum res = f1 * f2;
	// then


	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}


void multiply_test_longnums_not_integer() {
	// given
	BigNum f1("698.684898375844568363390863", 40);
	BigNum f2("3771.9106170734157785773277283", 35);
	BigNum correct_anw("2635376.9861727086795461400408408077021723669098207665229", 40);

	// when 
	BigNum res = f1 * f2;
	// then


	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void all_multiply_tests() {

	cout << "a * b: ";
	multiply_test_plus_plus();
	cout << "a * (-b): ";
	multiply_test_plus_minus();
	cout << "(-a) * (-b): ";
	multiply_test_minus_minus();
	cout << "int_longnum1 * int_longnum2: ";
	multiply_test_longnums_integer();
	cout << "frac_longnum1 * frac_longnum2: ";
	multiply_test_longnums_not_integer();

}


void divide_test1() {
	// given
	BigNum f1("-2,5");
	BigNum f2("2,5");
	BigNum correct_anw("-1");

	// when 
	BigNum res = f1 / f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}


void divide_test_integer_integer() {
	// given
	BigNum f1("12", 0);
	BigNum f2("2", 0);
	BigNum correct_anw("6", 0);

	// when 
	BigNum res = f1 / f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void divide_test_frac_frac() {
	// given
	BigNum f1("0.5625");
	BigNum f2("0.8125");
	BigNum correct_anw("0,692307692");
	

	// when 
	BigNum res = f1 / f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void divide_test_frac_frac2() {
	// given
	BigNum f1("0.28125", 6);
	BigNum f2("0.8125", 4);
	BigNum correct_anw("0,346153846", 6);

	// when 
	BigNum res = f1 / f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}


void divide_test_int_int_res_longfrac() {
	// given
	BigNum f1("2", 10);
	BigNum f2("3", 4);
	BigNum correct_anw("0,6666", 10);

	// when 
	BigNum res = f1 / f2;
	// then
	if (res == correct_anw) {
		cout << "OK\n";
	}
	else {
		cout << "FAIL\n";
	}
}

void all_divide_tests() {
	cout << "frac/frac = int: ";
	divide_test1();
	cout << "frac/frac = frac: ";
	divide_test_frac_frac();
	//cout << "frac/frac 2: ";
	//divide_test_frac_frac2();
	cout << "int/int = int: ";
	divide_test_integer_integer();
	cout << "int/int = frac: ";
	divide_test_int_int_res_longfrac();
}