#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <math.h>
#include <string.h>

#define MAXNUM	10001

using namespace std;

class Number { // includes Integer range

public:

	int arr[MAXNUM];
	int how_many_digit;

	int start_idx; // idx which starts number

	bool is_minus;

	Number(int num) {

		int idx = MAXNUM - 1;
		int temp_num = num < 0 ? -num : num;
		how_many_digit = 0;

		while (temp_num) {

			arr[idx--] = temp_num % 10;
			temp_num /= 10;

			how_many_digit++;
		}

		start_idx = idx + 1;

		for (; idx >= 0; idx--)
			arr[idx] = 0;

		if (num == 0) {
			how_many_digit = 1;
			start_idx = MAXNUM - 1;
		}

		is_minus = num < 0 ? true : false;
	}

	Number(char * num) {

		int num_len = strlen(num);
		int idx = num_len - 1;

		start_idx = MAXNUM - 1;
		int saved_start_idx = start_idx;

		for (; idx >= 0; idx--) {
			arr[start_idx--] = num[idx] - '0';
			how_many_digit++;
		}

		saved_start_idx = start_idx + 1;

		for (; start_idx >= 0; start_idx--)
			arr[start_idx] = 0;

		start_idx = saved_start_idx;

		is_minus = (num[0] == '-' ? true : false);

	}

	void set_number(int num) {

		int idx = MAXNUM - 1;
		int temp_num = num < 0 ? -num : num;
		how_many_digit = 0;

		while (temp_num) {

			arr[idx--] = temp_num % 10;
			temp_num /= 10;

			how_many_digit++;
		}

		start_idx = idx + 1;

		for (; idx >= 0; idx--)
			arr[idx] = 0;

		if (num == 0) {
			how_many_digit = 1;
			start_idx = MAXNUM - 1;
		}

		is_minus = num < 0 ? true : false;
	}

	Number(const Number& Num, bool minus_flag) {

		how_many_digit = Num.how_many_digit;
		start_idx = Num.start_idx;

		if (Num.is_minus == true)
			is_minus = (minus_flag == true ? false : true);
		else
			is_minus = (minus_flag == true ? true : false);

		for (int i = 0; i < MAXNUM; i++) {
			arr[i] = 0;

			if (i == Num.start_idx) {
				for (int j = i; j < MAXNUM; j++)
					arr[j] = Num.arr[j];
				break;
			}
		}

	}


	void set_number(const Number& Num) {

		how_many_digit = Num.how_many_digit;
		start_idx = Num.start_idx;
		is_minus = Num.is_minus;

		for (int i = 0; i < MAXNUM; i++) {
			arr[i] = 0;

			if (i == Num.start_idx) {
				for (int j = i; j < MAXNUM; j++)
					arr[j] = Num.arr[j];
				break;
			}
		}

	}

	void print_number() {

		if (is_minus == true)
			printf("-");

		for (int i = start_idx; i<MAXNUM; i++)
			printf("%d", arr[i]);
		printf("\n");
	}

	int get_number() const { // if number is not out of range in int

		int value = 0, cnt = 0;

		for (int j = MAXNUM - 1; j > MAXNUM - 11; j--) {

			value += (pow(10, cnt) * arr[j]);
			cnt++;
		}

		return (is_minus == true ? -value : value);
	}

	bool operator>(const Number& Num) {

		if (is_minus == true && Num.is_minus == false)
			return false;
		else if (is_minus == false && Num.is_minus == true)
			return true;
		else {

			if (how_many_digit > Num.how_many_digit)
				return (is_minus == false ? true : false);
			else if (how_many_digit < Num.how_many_digit)
				return (is_minus == false ? false : true);
			else {

				for (int i = start_idx; i < MAXNUM ; i++)
					if (arr[i] > Num.arr[i])
						return (is_minus == false ? true : false);
					else if (arr[i] < Num.arr[i])
						return (is_minus == false ? false : true);
					else
						continue;

				// if they are same
			}

		}

	}

	bool compare_abs(const Number& Num) {

		if (how_many_digit > Num.how_many_digit)
			return true;
		else if (how_many_digit < Num.how_many_digit)
			return false;
		else {

			for (int i = start_idx; i < MAXNUM; i++)
				if (arr[i] > Num.arr[i])
					return true;
				else if (arr[i] < Num.arr[i])
					return false;
				else
					continue;
	
		}


	}

	Number operator+(const Number& Num) {

		if (is_minus != Num.is_minus)
			return this->operator-(Num);
		else {

			int carry = 0, value, rem;
			Number result(0);

			result.is_minus = is_minus;

			for (int i = MAXNUM - 1; i >= 0; i--) {

				rem = (arr[i] + Num.arr[i] + carry) % 10;
				value = arr[i] + Num.arr[i] + carry;

				result.arr[i] = rem;

				carry = (value >= 10 ? 1 : 0);
			
			}

			for(int j=0;j<MAXNUM;j++)
				if (result.arr[j] != 0) {
					result.start_idx = j;
					result.how_many_digit = MAXNUM - j;
					break;
				}



			return result;
		}

	}

	Number operator*(const Number& Num) {

		int times = Num.get_number();
		times = (Num.is_minus == true ? -times : times);

		Number result(0);
		Number temp_Num = Number(*this, is_minus == true ? true : false);

		for (int i = 0; i < times; i++)
			result = result.operator+(temp_Num);

		result.is_minus = (this->is_minus != Num.is_minus ? true : false);

		return result;
	}

	Number operator-(const Number& Num) {

		if (is_minus == false && Num.is_minus == true)
			return this->operator+(Number(Num, true));
		else if (is_minus == true && Num.is_minus == false)
			return this->operator+(Number(Num,true));
		else {

			bool which_is_bigger = compare_abs(Num);

			Number temp_Num1 = Number(which_is_bigger == true ? *this : Num,false);
			if (which_is_bigger == false && Num.is_minus == true)
				temp_Num1.is_minus = false;
			else if(which_is_bigger == false && Num.is_minus == false)
				temp_Num1.is_minus = true;

			Number temp_Num2= Number(which_is_bigger == true ? Num : *this, false);

			int borrow = 0;

			for (int i = MAXNUM - 1; i >= temp_Num1.start_idx; i--) {

				if (temp_Num1.arr[i] - borrow - temp_Num2.arr[i] < 0) {
					temp_Num1.arr[i] = 10 + temp_Num1.arr[i] - borrow - temp_Num2.arr[i];
					borrow = 1;
				}
				else {
					temp_Num1.arr[i] = temp_Num1.arr[i] - borrow - temp_Num2.arr[i];
					borrow = 0;
				}
			}

			for (int j = 0; j<MAXNUM; j++)
				if (temp_Num1.arr[j] != 0) {
					temp_Num1.start_idx = j;
					temp_Num1.how_many_digit = MAXNUM - j;
					break;
				}


			return temp_Num1;
		}

	}

	void operator++() {

		int carry = 0;

		for (int i = MAXNUM - 1; i >= start_idx; i--) {

			if (arr[i] + carry + (i==MAXNUM-1 ? 1 : 0) >= 10) {
				arr[i] = 0;
				carry = 1;
			}
			else {
				arr[i] = (arr[i] + carry + (i == MAXNUM - 1 ? 1 : 0));
				carry = 0;
			}
		}

		if (carry == 1) {
			start_idx--;
			arr[start_idx] = 1;
			how_many_digit++;
		}


	}

	void operator--() {

		int borrow = 0;

		for (int i = MAXNUM - 1; i >= start_idx; i--) {

			if (arr[i] - borrow - (i == MAXNUM - 1 ? 1 : 0) < 0) {
				arr[i] = 9;
				borrow = 1;
			}
			else {
				arr[i] = arr[i] - borrow - (i == MAXNUM - 1 ? 1 : 0);
				borrow = 0;
			}
		}

		if (arr[start_idx] == 0) {
			start_idx++;
			how_many_digit--;
		}

	}

	Number operator/(const Number& Num) {

		// deal with positive integers first
		Number result(0);
		Number value(0);

		if (this->operator>(Num) == false)
			return result;
		else {

			Number result2 = Number(*this, false);

			while (1) {

				result2.set_number(result2.operator-(Num));
				value.operator++();

				if (result2.is_minus == true) {
					value.operator--();
					return value;
				}


			}
		}
	}

	Number operator%(Number& Num) {

		if (this->operator>(Num) == false)
			return *this;
		else {

			Number rem = Number(*this - Num.operator*(this->operator/(Num)),false);
			return rem;
		}
		
	}

	bool operator==(int num) {

		if (get_number() == num)
			return true;
		else
			return false;

	}

};

char buf1[MAXNUM], buf2[MAXNUM];

int main(void)
{
	scanf("%s %s", buf1, buf2);

	Number num1(buf1), num2(buf2);

	Number result = Number(num1 + num2, false);
	result.print_number();

	return 0;
}