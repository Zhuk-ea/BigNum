#include "BigNum.h"
#include "Func.h"

using namespace std;

BigNum::BigNum(string& str, unsigned a_d) {
	string s1 = "";
	unsigned i = 0;
	sign = 1;
	if (str[0] == '-') {
		sign = -1;
		++i;
	}
	for (i; str[i] != '.' && str[i] != ',' && str[i] != '\0'; ++i) {
		s1 += str[i];
	}
	deque<uint32_t> ar;
	unsigned b_d = get_int_part(ar, s1);
	if (str[i] == '\0') {
		for (int i = 0; i < (a_d / 32 + (a_d % 32 != 0)); ++i) {
			ar.push_back(0);
		}
		after_dot = a_d;
		arr = ar;
		befor_dot = b_d;
		return;
	}
	string s2 = "";
	++i;
	for (i; str[i] != '\0'; ++i) {
		s2 += str[i];
	}
	get_frac_part(ar, s2, a_d);
	arr = ar;
	befor_dot = b_d;
	after_dot = a_d;
}



void BigNum::print_in_bin() const {
	if (sign == -1) {
		cout << '-';
	}
	rint_bits_arr_int(arr, befor_dot);
	if (after_dot != 0) {
		cout << '.';
		rint_bits_arr_frac(arr, befor_dot, after_dot);
	}
	cout << endl;
}

int compare(const BigNum& a, const BigNum& b, unsigned accuracy) {
	Info infa = a.get_info();
	Info infb = b.get_info();

	if (infa.sign != infb.sign) {
		if (infa.sign == 1) {
			return 1;
		}
		return -1;
	}
	int rev = 1;
	if (infa.sign == -1) {
		rev = -1;
	}
	if (infa.befor_dot > infb.befor_dot) {
		return rev;
	}
	if (infa.befor_dot < infb.befor_dot) {
		return -rev;
	}
	for (int i = 0; i < (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0); ++i) {
		if (infa.arr[i] > infb.arr[i]) {
			return rev;
		}
		if (infa.arr[i] < infb.arr[i]) {
			return -rev;
		}
	}
	deque<uint32_t> mn;
	unsigned mn_len = min(infa.after_dot, infb.after_dot);
	unsigned mn_bd;
	unsigned mx_bd;
	unsigned mx_len = max(infa.after_dot, infb.after_dot);
	deque<uint32_t> mx;
	if (infa.after_dot > infb.after_dot) {
		mx = infa.arr;
		mx_bd = (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0);
		mn = infb.arr;
		mn_bd = (infb.befor_dot / 32) + (infb.befor_dot % 32 != 0);
	}
	else {
		mn = infa.arr;
		mn_bd = (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0);
		mx = infb.arr;
		mx_bd = (infb.befor_dot / 32) + (infb.befor_dot % 32 != 0);
		rev *= -1;
	}
	if (accuracy < mn_len) {
		mn_len = accuracy;
		mx_len = accuracy;
	}
	else if (accuracy < mx_len) {
		mx_len = accuracy;
	}

	int add = 0;
	if (infa.befor_dot == 0) {
		add ++;
	}
	for (int i = add; i < mn_len / 32 + (mn_len % 32 != 0) + add; ++i) {
		if (mx[mx_bd + i] > mn[mn_bd + i]) {
			return rev;
		}
		if (mx[mx_bd + i] < mn[mn_bd + i]) {
			return -rev;
		}
	}
	for (int i = mn_len / 32 + (mn_len % 32 != 0); i < mx_len / 32 + (mx_len % 32 != 0); ++i) {
		if (mx[i] != 0) {
			return rev;
		}
	}
	return 0;
}

int compare(Info& infa, Info& infb, unsigned accuracy) {

	if (infa.sign != infb.sign) {
		if (infa.sign == 1) {
			return 1;
		}
		return -1;
	}
	int rev = 1;
	if (infa.sign == -1) {
		rev = -1;
	}
	if (infa.befor_dot > infb.befor_dot) {
		return rev;
	}
	if (infa.befor_dot < infb.befor_dot) {
		return -rev;
	}
	for (int i = 0; i < (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0); ++i) {
		if (infa.arr[i] > infb.arr[i]) {
			return rev;
		}
		if (infa.arr[i] < infb.arr[i]) {
			return -rev;
		}
	}
	deque<uint32_t> mn;
	unsigned mn_len = min(infa.after_dot, infb.after_dot);
	unsigned mn_bd;
	unsigned mx_bd;
	unsigned mx_len = max(infa.after_dot, infb.after_dot);
	deque<uint32_t> mx;
	if (infa.after_dot > infb.after_dot) {
		mx = infa.arr;
		mx_bd = (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0);
		mn = infb.arr;
		mn_bd = (infb.befor_dot / 32) + (infb.befor_dot % 32 != 0);
	}
	else {
		mn = infa.arr;
		mn_bd = (infa.befor_dot / 32) + (infa.befor_dot % 32 != 0);
		mx = infb.arr;
		mx_bd = (infb.befor_dot / 32) + (infb.befor_dot % 32 != 0);
		rev *= -1;
	}
	if (accuracy < mn_len) {
		mn_len = accuracy;
		mx_len = accuracy;
	}
	else if (accuracy < mx_len) {
		mx_len = accuracy;
	}
	for (int i = 0; i < mn_len / 32 + (mn_len % 32 != 0); ++i) {
		if (mx[mx_bd + i] > mn[mn_bd + i]) {
			return rev;
		}
		if (mx[mx_bd + i] < mn[mn_bd + i]) {
			return -rev;
		}
	}
	for (int i = mn_len / 32 + (mn_len % 32 != 0); i < mx_len / 32 + (mx_len % 32 != 0); ++i) {
		if (mx[i] != 0) {
			return rev;
		}
	}
	return 0;
}

bool BigNum::operator<(const BigNum& b) const {
	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res == -1) {
		return true;
	}
	return false;
}
bool BigNum::operator>(const BigNum& b) const {
	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res == 1) {
		return true;
	}
	return false;

}
bool BigNum::operator==(const BigNum& b) const {

	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res == 0) {
		return true;
	}
	return false;
}
bool BigNum::operator<=(const BigNum& b) const {
	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res < 1) {
		return true;
	}
	return false;

}
bool BigNum::operator>=(const BigNum& b) const {
	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res > -1) {
		return true;
	}
	return false;

}
bool BigNum::operator!=(const BigNum& b) const {
	unsigned acc = max(after_dot, b.after_dot);
	int res = compare(*this, b, acc);
	if (res != 0) {
		return true;
	}
	return false;

}
void BigNum::operator=(const BigNum& b) {
	sign = b.sign;
	befor_dot = b.befor_dot;
	after_dot = b.after_dot;
	arr = b.arr;
}

void BigNum::operator+=(const BigNum& b) {
	*this = *this + b;
}
void BigNum::operator-=(const BigNum& b) {
	*this = *this - b;
}
void BigNum::operator*=(const BigNum& b) {
	*this = *this * b;
}


const BigNum BigNum::operator+(const BigNum& b) const {
	if (sign == b.sign && sign == 1) { //++
		Info i_a = get_info();
		Info i_b = b.get_info();
		Info Res = arr_plus(i_a, i_b);
		return BigNum(Res);
	}
	if (sign == b.sign && sign == -1) { //--
		BigNum t_a = *this;
		t_a.revers_sign();
		BigNum t_b = b;
		t_b.revers_sign();
		BigNum res = t_a + t_b;
		res.revers_sign();
		return res;
	}
	if (sign == -1) {
		BigNum t_a = *this;
		t_a.revers_sign();
		return b - t_a;
	} // -+
	BigNum t_b = b;
	t_b.revers_sign();
	return *this - t_b; // +-
}

const BigNum BigNum::operator-(const BigNum& b) const {

	if (sign == b.sign == -1) { //--
		BigNum t_a = *this;
		t_a.revers_sign();
		BigNum t_b = b;
		t_b.revers_sign();
		return t_b - t_a;
	}
	if (sign == b.sign == 1) {// ++
		if (*this < b) {
			BigNum t = b - *this;
			t.revers_sign();
			return t;
		}
		if (*this == b) {
			return BigNum("0", after_dot);
		}
		Info i_a = get_info();
		Info i_b = b.get_info();
		Info Res = arr_minus(i_a, i_b);
		return BigNum(Res);

	}
	if (sign == -1) { // - +
		BigNum t_b = b;
		t_b.revers_sign();
		return *this + t_b;
	}
	// + -
	BigNum t_b = b;
	t_b.revers_sign();
	return *this + t_b;

}

BigNum mult(uint32_t a, uint32_t b, unsigned mod_a = 0, unsigned mod_b = 0) {
	uint64_t t_a = a >> (32 - mod_a) * (mod_a != 0);
	uint64_t t_b = b >> (32 - mod_b) * (mod_b != 0);
	uint64_t u = t_a * t_b;
	return BigNum(u);
}

BigNum multiply(const BigNum& a, const BigNum& b) {

	Info ia = a.get_info();
	Info ib = b.get_info();
	ia.shift_right((32 - ia.after_dot) % 32);
	ia.befor_dot += ia.after_dot;
	ia.after_dot = 0;
	BigNum t_a(ia);



	ib.shift_right((32 - ib.after_dot) % 32);
	ib.befor_dot += ib.after_dot;
	ib.after_dot = 0;
	BigNum t_b(ib);

	BigNum res;

	for (int j = ia.arr.size() - 1; j > -1; --j) {
		unsigned mod_a = ia.arr.size() - 1 - j;
		for (int i = ib.arr.size() - 1; i > -1; --i) {
			unsigned mod_b = ib.arr.size() - 1 - i;
			BigNum t = mult(ia.arr[j], ib.arr[i]);
			t.push_back_null(mod_a + mod_b);
			res += t;
		}
	}


	return res;
}

const BigNum BigNum::operator* (const BigNum& b) const {
	BigNum t_a = *this;
	BigNum t_b = b;

	BigNum res = multiply(t_a, t_b); // получили целую гадость
	unsigned a_d = t_a.after_dot + t_b.after_dot;
	unsigned b_d = res.befor_dot - a_d;
	unsigned actual_a_d = max(t_a.after_dot, t_b.after_dot);
	unsigned bad_ints = (a_d - actual_a_d) / 32;

	// do good

	Info r = res.get_info();
	for (int i = 0; i < bad_ints; ++i) {
		r.arr.pop_back();
		r.befor_dot -= 32;
	}

	r.shift_right(r.befor_dot % 32 + (32 - b_d % 32), 1);
	r.befor_dot = b_d;
	r.after_dot = a_d;

	uint32_t pat = 0xFFFFFFFF << (((32 - actual_a_d) % 32));
	r.arr[r.arr.size() - 1] &= pat;
	r.after_dot = actual_a_d;
	BigNum ress(r);
	ress.sign = sign * b.sign;

	// did good




	return ress;
}

const BigNum BigNum::operator/ (const BigNum& b) const {

	unsigned n = min(befor_dot, b.befor_dot);
	unsigned delta = max(befor_dot, b.befor_dot) - n;
	unsigned res_a_d = max(after_dot, b.after_dot);
	unsigned b_d = 0;

	Info ia = get_info();
	Info ib = b.get_info();
	ia.sign = 1;
	ib.sign = 1;

	// Сдвигаем ia и ib на столько, чтобы ib стало целым
	ia.shift_right((32 - ib.after_dot) % 32, 1);
	ia.befor_dot += ib.after_dot;
	if (ia.after_dot > ib.after_dot) {
		ia.after_dot -= ib.after_dot;
	}
	else {
		ia.after_dot = 0;
	}


	ib.shift_right((32 - ib.after_dot) % 32);
	ib.befor_dot += ib.after_dot;
	ib.after_dot = 0;

	int res_b_d = ia.befor_dot - ib.befor_dot + 1;


	ia.shift_right((32 - ia.after_dot) % 32, 1);
	ia.befor_dot += ia.after_dot;
	ia.after_dot = 0;


	Info res(0);
	unsigned front_nulls = 0;
	if (ia.befor_dot < ib.befor_dot) { // Докинули справа нулей, если их не хватает
		front_nulls += ib.befor_dot - ia.befor_dot;
		ia.shift_left(ib.befor_dot - ia.befor_dot);
	}

	Info temp = ia.get_part(ib.befor_dot);
	unsigned add = (31 - (ia.befor_dot % 32)) * (ia.befor_dot % 32 != 0) + ib.befor_dot;
	unsigned need_ops = res_a_d;
	if (compare(temp, ib, ib.befor_dot) < 0) {
		need_ops++;
		res_b_d = 1;
	}
	if (compare(temp, ib, ib.befor_dot) < 0) {
		res_b_d--;
	}
	if (res_b_d > 0) {
		need_ops += res_b_d;
	}
	else {
		need_ops -= res_b_d;
	}


	// Деление в столбик до конца исходного числа
	unsigned i = 0;
	for (i; i < ia.befor_dot - ib.befor_dot; ++i) {
		int x = compare(temp, ib, ib.befor_dot);
		if (x > 0) {
			temp = arr_minus(temp, ib);
			res.arr[res.arr.size() - 1] += 1;
		}
		else if (x == 0) {
			temp = Info(0);
			res.arr[res.arr.size() - 1] += 1;
		}
		temp.shift_left(1);
		if (temp.arr.size() == 0) {
			temp.arr.push_back(0);
			temp.befor_dot = 1;
		}
		uint32_t pat = 1 << (31 - (i + add + 1) % 32);

		uint32_t bit = ia.arr[(i + add) / 32] & pat;
		res.shift_left(1);
		if (bit) {
			Info one(1);
			temp = arr_plus(temp, one);
		}
	}

	// Делим докидывая только 0
	for (i; i < need_ops; ++i) {
		if (temp.arr.size() == 0) {
			temp.arr.push_back(0);
			temp.befor_dot = 1;
		}
		int x = compare(temp, ib, ib.befor_dot);
		if (x >= 0) {
			temp = arr_minus(temp, ib);
			res.arr[res.arr.size() - 1] += 1;
		}
		temp.shift_left(1);
		uint32_t pat = 1 << (31 - (i + add) % 32);
		res.shift_left(1);
	}
	res.shift_right2(1);
	if (res_b_d == 0) {
		res.shift_left((32 - res.befor_dot + 1), 1);
	}
	else {
		res.shift_left((32 - res.befor_dot) + res_b_d);
	}
	res.befor_dot = res_b_d;
	res.after_dot = res_a_d;
	res.sign = sign * b.sign;

	return BigNum(res);
}