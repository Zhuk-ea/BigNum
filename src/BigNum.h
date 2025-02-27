#ifndef BIGNUM_H_
#define BIGNUM_H

#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <deque>
#include "Info.h"


using namespace std;

class BigNum {
private:
	unsigned befor_dot;
	unsigned after_dot;
	int sign;
	deque<uint32_t> arr;
	void revers_sign() {
		sign = -sign;
	}

public:
	Info get_info() const {
		return Info(befor_dot, after_dot, sign, arr);
	};
	size_t get_size() const {
		return arr.size();
	};
	uint32_t get_first() const {
		return arr[0];
	};
	void push_back_null(unsigned count) {
		for (unsigned i = 0; i < count; ++i) {
			arr.push_back(0);
		}
		if (after_dot == 0) {
			befor_dot += count * 32;
		}
		else {
			after_dot += count * 32;
		}
	}
	~BigNum() = default;
	BigNum(uint32_t u) {
		arr.resize(1);
		arr[0] = u;
		befor_dot = 32;
		after_dot = 0;
		sign = 1;
	}
	BigNum(uint64_t u, unsigned a_d = 0) {
		arr.resize(2);
		arr[1] = u & 0x00000000FFFFFFFF;
		arr[0] = u >> 32;
		befor_dot = 64;
		if (arr[0] == 0) {
			arr.pop_front();
			befor_dot = 32;
		}
		for (int i = 31; i > -1; --i) {
			uint32_t pat = 1 << i;
			if ((arr[0] & pat) == 0) {
				befor_dot -= 1;
			}
			else {
				break;
			}
		}
		if (a_d) {
			befor_dot = a_d;
		}
		after_dot = 0;
		sign = 1;
	}
	BigNum(deque<uint32_t> ar, unsigned b_d, unsigned a_d, int s = 1) {
		befor_dot = b_d;
		after_dot = a_d;
		sign = s;
		arr = ar;
	};
	BigNum() {
		arr.resize(1, 0);
		befor_dot = 1;
		after_dot = 0;
		sign = 1;
	};
	BigNum(Info inf) {
		befor_dot = inf.befor_dot;
		after_dot = inf.after_dot;
		sign = inf.sign;
		arr = inf.arr;
	}
	BigNum(string& str, unsigned a_d = 32);
	BigNum(const char* str, unsigned a_d = 32) {
		string s = str;
		*this = BigNum(s, a_d);
	}
	void print_in_bin() const;
	void print_in_dec() const;
	const BigNum operator+(const BigNum& b) const;
	const BigNum operator-(const BigNum& b) const;
	const BigNum operator*(const BigNum& b) const;
	const BigNum operator/(const BigNum& b) const;
	void operator=(const BigNum& b);
	void operator+=(const BigNum& b);
	void operator-=(const BigNum& b);
	void operator*=(const BigNum& b);
	void operator/=(const BigNum& b);
	bool operator<(const BigNum& b) const;
	bool operator>(const BigNum& b) const;
	bool operator==(const BigNum& b) const;
	bool operator<=(const BigNum& b) const;
	bool operator>=(const BigNum& b) const;
	bool operator!=(const BigNum& b) const;

};
/*
BigNum operator""__longnum(long double number)
{
	string s = to_string(number);
	return BigNum(s);
}
*/

int compare(const BigNum& a, const BigNum& b, unsigned accuracy);


#endif