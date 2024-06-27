#ifndef __DIGITAL_CLOCK__
#define __DIGITAL_CLOCK__

#include <systemc.h>
using namespace sc_core;

class Digital_clock : public sc_module {
public:
	sc_in<bool> nrst, clk;
	// initialize
	sc_in<sc_uint<13>> init_year;
	sc_in<sc_uint<4>> init_month;
	sc_in<sc_uint<5>> init_day;
	sc_in<sc_uint<6>> init_hour, init_min, init_sec;
	sc_in<sc_uint<10>> init_msec;
	// alarm
	sc_in<sc_uint<6>> alarm_hour, alarm_min, alarm_sec;
	// output
	sc_out<sc_uint<13>> year;
	sc_out<sc_uint<4>> month;
	sc_out<sc_uint<5>> day;
	sc_out<sc_uint<6>> hour, min, sec;
	sc_out<sc_uint<10>> msec;
	sc_out<bool> alarm;

	Digital_clock(sc_module_name name) : sc_module(name) {
		SC_THREAD(main);
		sensitive << clk.pos() << nrst;
	}

private:
	bool leap = false;
	int lastDay[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	void main() {
		while (true) {
			// time update
			if (nrst.read() == 0)  initalize();
			else  update();
			// alarm
			if (alarm_hour.read() == hour.read() && alarm_min.read() == min.read() && alarm_sec.read() == sec.read()) {
				alarm = true;
			}
			else alarm = false;
			// leap year
			leap = year.read() % 4 == 0;

			wait();
		}
	}
	void initalize() {
		year = init_year.read();
		month = init_month.read();
		day = init_day.read();
		hour = init_hour.read();
		min = init_min.read();
		sec = init_min.read();
		msec = init_msec.read();
	}
	void update() {
		if (addInRange<10>(0, 1000,&msec)) return;
		if (addInRange<6>(0, 60, &sec)) return;
		if (addInRange<6>(0, 60, &min)) return;
		if (addInRange<6>(0, 24, &hour)) return;
		if (leap && month.read() == 2) {
			if (addInRange<5>(1, 28+1, &day)) return;
		}
		else if (addInRange<5>(1, lastDay[month.read()]+1, &day)) return;
		if (addInRange<4>(1, 12+1, &month)) return;
		if (addInRange<13>(1, 4000+1, &year)) return;
	}

	template<int T>
	bool addInRange(int s, int e, sc_out<sc_uint<T>> *value) {
		bool res = false;

		if (value->read() != e-1) {
			*value = value->read() + 1;
			res = true;
		}
		else {
			*value = s;
		}

		return res;
	}
};
#endif