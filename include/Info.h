#pragma once
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <deque>



using namespace std;


class Info {
public:
	unsigned befor_dot;
	unsigned after_dot;
	int sign;
	deque<uint32_t> arr;
	Info() {
		sign = 1;
		befor_dot = 0;
		after_dot = 0;
	};
	Info(unsigned null) {
		sign = 1;
		befor_dot = 1;
		after_dot = 0;
		arr.push_back(null);
	};
	Info(unsigned b_d, unsigned a_d, int sgn, deque<uint32_t>& ar) {
		befor_dot = b_d;
		after_dot = a_d;
		sign = sgn;
		arr = ar;
	};
	Info(const unsigned b_d, const unsigned a_d, const int sgn, const deque<uint32_t>& ar) {
		befor_dot = b_d;
		after_dot = a_d;
		sign = sgn;
		arr = ar;
	};
	void shift_right(unsigned sh, unsigned nou = 0) { //������ ��� ���������
		if (!sh) {
			return;
		}
		uint32_t mem = 0;
		uint32_t pat = (1 << sh) - 1;
		if (nou) {
			arr.push_back(0);
		}
		for (int i = 0; i < arr.size(); ++i) {
			uint32_t t = arr[i] & pat;
			arr[i] = arr[i] >> sh;
			arr[i] |= (mem << (32 - sh));
			mem = t;
		}
		if (!nou || arr[0] == 0) {
			arr.pop_front();
		}
	}
	void shift_right2(unsigned sh, unsigned nou = 0) {
		if (!sh) {
			return;
		}
		uint32_t mem = 0;
		uint32_t pat = (1 << sh) - 1;
		for (int i = 0; i < arr.size(); ++i) {
			uint32_t t = arr[i] & pat;
			arr[i] = arr[i] >> sh;
			arr[i] |= (mem << (32 - sh));
			mem = t;
		}
		if (arr[0] == 0 && !nou) {
			arr.pop_front();
		}
		befor_dot--;
	}
	Info get_part(unsigned b_d) {

		Info res;
		unsigned unfull = befor_dot % 32;
		for (int i = 0; i < ((unfull + b_d) / 32) + ((unfull + b_d) != 0); ++i) {
			res.arr.push_back(arr[i]);
		}

		res.shift_right2((befor_dot - b_d) % 32);
		if (res.arr[0] == 0) {
			res.arr.pop_front();
		}
		res.befor_dot = b_d;
		return res;
	}


	void shift_left(unsigned sh, unsigned nou = 0) {
		if (!sh) {
			return;
		}
		uint32_t mem = 0;
		uint32_t pat = ((1 << sh) - 1) << (32 - sh);
		arr.push_front(0);
		for (int i = arr.size() - 1; i > -1; --i) {
			uint32_t t = arr[i] & pat;
			arr[i] = arr[i] << sh % 32;
			arr[i] |= (mem >> (32 - sh % 32));
			mem = t;
		}
		for (int i = 0; i < sh / 32; ++i) {
			arr.push_back(0);
		}
		if (arr[0] == 0 && !nou) {
			arr.pop_front();
		}
		befor_dot += sh;
	}

	void operator=(const Info& b) {
		befor_dot = b.befor_dot;
		after_dot = b.after_dot;
		sign = b.sign;
		arr = b.arr;
	}

};
