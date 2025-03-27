#pragma once
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <deque>
#include <cmath>

using namespace std;

void rint_bits_arr_int(const deque<uint32_t>& arr, const unsigned len) {
	int unf = len % 32;
	if (!len) {
		cout << '0';
		return;
	}
	if (!unf) {
		unf = 32;
	}
	for (int i = (32 - unf); i < len + (32 - unf); ++i) {
		cout << ((arr[i / 32] & (1 << (31 - i % 32))) != 0);
	}
}

void rint_bits_arr_frac(const deque<uint32_t>& arr, const unsigned b_d, const unsigned len) {
	int start = b_d + (32 - b_d % 32);
	for (int i = start; i < (start + len); ++i) {
		cout << ((arr[i / 32] & (1 << (31 - i % 32))) != 0);
	}
}


void rint_bits(uint32_t u) {
	for (int i = 31; i > -1; --i) {
		cout << ((u & (1 << (i % 32))) != 0);
	}
	cout << endl;
}

string multiply_by_two(string& str) {
	int str_len = str.length();
	int res_len = str_len;
	int z = 0;
	if (str[0] >= '5') {
		res_len++;
		z = 1;
	}
	string res;
	res.resize(res_len, '_');
	int have_transfer = 0;
	for (int i = (str_len - 1); i > -1; i--) {
		int temp = ((str[i] - '0') * 2 + have_transfer);
		res[i + z] = temp % 10 + '0';
		if (temp / 10 == 0) {
			have_transfer = 0;
		}
		else {
			have_transfer = 1;
		}
	}
	if (have_transfer) {
		res[0] = '1';
	}
	return res;
}


string multiply_by_two_for_frac(string& str) {
	int str_len = str.length();
	int res_len = str_len;
	int z = 0;
	if (str[0] >= '5') {
		res_len++;
		z = 1;
	}
	string res;
	res.resize(res_len, '_');
	int have_transfer = 0;
	for (int i = (str_len - 1); i > -1; i--) {
		int temp = ((str[i] - '0') * 2 + have_transfer);
		res[i + z] = temp % 10 + '0';
		if (temp / 10 == 0) {
			have_transfer = 0;
		}
		else {
			have_transfer = 1;
		}
	}
	if (have_transfer) {
		res[0] = '!';
	}
	return res;
}


int string_divide_by_two(string& str) {
	int len = str.length();
	int transfer = 0;
	for (int i = 0; i < len; ++i) {
		char c = str[i];
		str[i] = (str[i] - '0' + transfer) / 2 + '0';
		if ((c - '0') % 2 == 1) {
			transfer = 10;
		}
		else {
			transfer = 0;
		}
	}
	while (str[0] == '0') {
		str.erase(0, 1);
	}

	return (transfer != 0);
}

int string_divide_by_two_frac(string& str) {
	int len = str.length();
	int transfer = 0;
	for (int i = 0; i < len; ++i) {
		char c = str[i];
		str[i] = (str[i] - '0' + transfer) / 2 + '0';
		if ((c - '0') % 2 == 1) {
			transfer = 10;
		}
		else {
			transfer = 0;
		}
	}
	if (transfer) {
		str += "5";
	}
	return (transfer != 0);
}


int string_compare(string& str1, string& str2) {
	if (str1.length() > str2.length()) {
		return 1;
	}
	if (str1.length() < str2.length()) {
		return -1;
	}
	if (str1 < str2) {
		return -1;
	}
	if (str1 > str2) {
		return 1;
	}
	return 0;
}


unsigned get_int_part(deque<uint32_t>& arr, string& str) {
	vector<string> powers_of_two;
	powers_of_two.push_back("1");
	string s = str;
	if (s[0] == '0') {
		arr.resize(1, 0);
		return 0;
	}
	int i = 0;
	while (s != "") {
		int bit = string_divide_by_two(s);
		if (i % 32 == 0) {
			arr.push_front(uint32_t(0));
		}
		if (bit) {
			uint32_t pat = (1 << (i % 32));
			arr[0] |= pat;
		}
		++i;
	}


	return i;
}


void get_frac_part(deque<uint32_t>& arr, string& str, unsigned a_d) {
	string s = str;
	int i = 0;
	int siz = arr.size() - 1;
	for (int i = 0; i < a_d; ++i) {
		str = multiply_by_two_for_frac(str);
		if (i % 32 == 0) {
			arr.push_back(uint32_t(0));
			++siz;
		}
		if (str[0] == '!') {
			str.erase(0, 1);
			uint32_t pat = 1 << (31 - i % 32);
			arr[siz] = arr[siz] | pat;
		}
	}
}


Info arr_plus(Info& a, Info& b) {

	Info Res;
	Res.sign = 1;
	unsigned transf = 0;
	unsigned trait = 0;
	unsigned dif1, dif2;
	unsigned ak1, bk1, ak2, bk2;
	unsigned b_d, a_d;

	if (a.befor_dot > b.befor_dot) {
		ak1 = 0;
		bk1 = 1;
		dif1 = a.befor_dot / 32 + (a.befor_dot % 32 != 0) - (b.befor_dot / 32 + (b.befor_dot % 32 != 0));
		trait = a.befor_dot / 32 + (a.befor_dot % 32 != 0);
		b_d = a.befor_dot;
	}
	else {
		ak1 = 1;
		bk1 = 0;
		dif1 = b.befor_dot / 32 + (b.befor_dot % 32 != 0) - (a.befor_dot / 32 + (a.befor_dot % 32 != 0));
		trait = b.befor_dot / 32 + (b.befor_dot % 32 != 0);
		b_d = b.befor_dot;
	}
	if (a.after_dot > b.after_dot) {
		ak2 = 0;
		bk2 = 1;
		dif2 = a.after_dot / 32 + (a.after_dot % 32 != 0) - (b.after_dot / 32 + (b.after_dot % 32 != 0));
		trait += (b.after_dot / 32 + (b.after_dot % 32 != 0));
		a_d = a.after_dot;
	}
	else {
		ak2 = 1;
		bk2 = 0;
		dif2 = b.after_dot / 32 + (b.after_dot % 32 != 0) - (a.after_dot / 32 + (a.after_dot % 32 != 0));
		trait += (a.after_dot / 32 + (a.after_dot % 32 != 0));
		a_d = b.after_dot;
	}
	if (ak2) {
		for (int i = trait; i < trait + dif2; ++i) {
			Res.arr.push_back(b.arr[i]);
		}
	}
	else {
		for (int i = trait; i < trait + dif2; ++i) {
			Res.arr.push_back(a.arr[i]);
		}
	}

	int add_a = 0;
	int add_b = 0;
	if (a.befor_dot == 0) {
		add_a ++;
	}
	if (b.befor_dot == 0) {
		add_b ++;
	}
	for (int i = trait - 1; i >= dif1; --i) {
		uint64_t temp = (uint64_t)a.arr[i - dif1 * ak1 + add_a] + (uint64_t)b.arr[i - dif1 * bk1  + add_b] + transf;
		if (temp > 0xFFFFFFFF) {
			transf = 1;
		}
		else {
			transf = 0;
		}
		Res.arr.push_front(temp & 0xFFFFFFFF);
		if (i == 0) {
			break;
		}
	}
	if (ak1 && dif1) {
		for (int i = dif1 - 1; i > -1; --i) {
			uint64_t temp = (uint64_t)b.arr[i] + transf;
			if (temp > 0xFFFFFFFF) {
				transf = 1;
			}
			else {
				transf = 0;
			}
			Res.arr.push_front(temp & 0xFFFFFFFF);
		}
	}
	else if (dif1) {
		for (int i = dif1 - 1; i > -1; --i) {
			uint64_t temp = (uint64_t)a.arr[i] + transf;
			if (temp > 0xFFFFFFFF) {
				transf = 1;
			}
			else {
				transf = 0;
			}
			Res.arr.push_front(temp & 0xFFFFFFFF);
		}
	}
	if (transf) {
		Res.arr.push_front(1);
		++b_d;
	}
	else {
		if (b_d == 0 && !transf) {
			Res.arr.push_front(0);
			return(Res);
		}
		b_d = b_d - b_d % 32 + 32;
		for (int i = 31; i > -1; --i) {
			uint32_t pat = 1 << i;
			if ((Res.arr[0] & pat) == 0) {
				b_d -= 1;
			}
			else {
				break;
			}
		}	
	}
	Res.befor_dot = b_d;
	Res.after_dot = a_d;
	return Res;
}


Info arr_minus(Info& a, Info& b) {

	Info Res;
	Res.sign = 1;
	unsigned transf = 0;
	unsigned trait = 0;
	unsigned dif1, dif2;
	unsigned ak1, bk1, ak2, bk2;
	unsigned b_d, a_d;


	ak1 = 0;
	bk1 = 1;
	dif1 = a.befor_dot / 32 + (a.befor_dot % 32 != 0) - (b.befor_dot / 32 + (b.befor_dot % 32 != 0));
	trait = a.befor_dot / 32 + (a.befor_dot % 32 != 0);
	b_d = a.befor_dot;

	if (a.after_dot >= b.after_dot) {
		ak2 = 0;
		bk2 = 1;
		dif2 = a.after_dot / 32 + (a.after_dot % 32 != 0) - (b.after_dot / 32 + (b.after_dot % 32 != 0));
		trait += (b.after_dot / 32 + (b.after_dot % 32 != 0));
		a_d = a.after_dot;
	}
	else {
		ak2 = 1;
		bk2 = 0;
		dif2 = b.after_dot / 32 + (b.after_dot % 32 != 0) - (a.after_dot / 32 + (a.after_dot % 32 != 0));
		trait += (a.after_dot / 32 + (a.after_dot % 32 != 0));
		a_d = b.after_dot;
	}
	if (ak2) {
		transf = 1;
		for (int i = trait; i < trait + dif2; ++i) {
			Res.arr.push_back(0xFFFFFFFF - b.arr[i]);
		}
	}
	else {
		for (int i = trait; i < trait + dif2; ++i) {
			Res.arr.push_back(a.arr[i]);
		}
	}

	int add_a = 0;
	int add_b = 0;
	if (a.befor_dot == 0) {
		add_a ++;
	}
	if (b.befor_dot == 0) {
		add_b ++;
	}

	for (int i = trait - 1; i >= dif1; --i) {
		uint64_t temp;
		if ((uint64_t)a.arr[i - dif1 * ak1 + add_a] < (uint64_t)b.arr[i - dif1 * bk1 + add_b] + transf) {
			transf = 1;
			temp = (uint64_t)a.arr[i - dif1 * ak1 + add_a] + (uint64_t)b.arr[i - dif1 * bk1+ add_b] + 0x80000000 - transf;
		}
		else {
			temp = (uint64_t)a.arr[i - dif1 * ak1 + add_a] - (uint64_t)b.arr[i - dif1 * bk1 + add_b] - transf;
		}
		Res.arr.push_front(temp);

		if (i == 0) {
			break;
		}
	}

	if (dif1) {
		for (int i = dif1 - 1; i > -1; --i) {
			uint64_t temp;
			if (a.arr[i] < transf) {
				temp = 0x80000000 - 1;
				transf = 1;
			}
			else {
				temp = a.arr[i];
				transf = 0;
			}
			Res.arr.push_front(temp);
		}
	}

	Res.after_dot = a_d;
	for (int i = 0; i < b_d / 32 + (b_d % 32 != 0); ++i) {
		if (Res.arr[0] == 0) {
			Res.arr.pop_front();
		}
	}
	b_d = Res.arr.size() - Res.after_dot / 32 - (Res.after_dot % 32 != 0);
	b_d *= 32;
	if (b_d) {
	for (int i = 31; i > -1; --i) {
		uint32_t pat = 1 << i;
		if ((Res.arr[0] & pat) == 0) {
			b_d -= 1;
		}
		else {
			break;
		}
	}
	}
	if (b_d == 0) {
		Res.arr.push_front(0);
	}
	Res.befor_dot = b_d;

	return Res;
}
