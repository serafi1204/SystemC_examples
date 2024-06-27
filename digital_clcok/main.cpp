#include <systemc.h>
#include <string>
#include "digital_clock.hpp"
using namespace std;

#define CLK_PERIOD 1
#define CLK_TIME_UNIT 0.5
#define	CLK_DUTY_CYCLE 10
#define VSD_NAME "top"

sc_clock clk("clk", CLK_PERIOD, CLK_DUTY_CYCLE, CLK_TIME_UNIT, 0);
sc_trace_file* fp;

// Digital clock
Digital_clock dc("clock");


sc_signal<bool> nrst;
// initialize
sc_signal<sc_uint<13>> init_year;
sc_signal<sc_uint<4>> init_month;
sc_signal<sc_uint<5>> init_day;
sc_signal<sc_uint<6>> init_hour, init_min, init_sec;
sc_signal<sc_uint<10>> init_msec;
// alarm
sc_signal<sc_uint<6>> alarm_hour, alarm_min, alarm_sec;
// output
sc_signal<sc_uint<13>> year;
sc_signal<sc_uint<4>> month;
sc_signal<sc_uint<5>> day;
sc_signal<sc_uint<6>> hour, mn, sec;
sc_signal<sc_uint<10>> msec;
sc_signal<bool> alarm;

void openGTKwave() {
	string run_commend;

	run_commend = "gtkwave ";
	run_commend += VSD_NAME;
	run_commend += ".vcd";

	system(run_commend.c_str());
}

void testbench() {
	nrst = 0;
	init_year = 4;
	init_month = 2;
	init_day = 28;
	init_hour = 23;
	init_min = 59;
	init_sec = 55;
	init_msec = 990;
	alarm_hour = 23;
	alarm_min = 59;
	alarm_sec = 59;

	sc_start(1, SC_US);
	nrst = 1;

	sc_start(10, SC_US);
	nrst = 0;

	sc_start(1, SC_US);
}

int sc_main(int argc, char* argv[]) {
	fp = sc_create_vcd_trace_file(VSD_NAME);
	fp->set_time_unit(10, SC_PS);

	// wireing 
	dc.nrst(nrst);
	dc.clk(clk);
	dc.init_year(init_year);
	dc.init_month(init_month);
	dc.init_day(init_day);
	dc.init_hour(init_hour);
	dc.init_min(init_min);
	dc.init_sec(init_sec);
	dc.init_msec(init_msec);
	dc.alarm_hour(alarm_hour);
	dc.alarm_min(alarm_min);
	dc.alarm_sec(alarm_sec);

	dc.year(year);
	dc.month(month);
	dc.day(day);
	dc.hour(hour);
	dc.min(mn);
	dc.sec(sec);
	dc.msec(msec);
	dc.alarm(alarm);

	//tracing
	sc_trace(fp, clk, "CLK");
	sc_trace(fp, nrst, "nrst");
	sc_trace(fp, year, "year");
	sc_trace(fp, month, "month");
	sc_trace(fp, day, "day");
	sc_trace(fp, hour, "hour");
	sc_trace(fp, mn, "min");
	sc_trace(fp, sec, "sec");
	sc_trace(fp, msec, "msec");

	// tb
	testbench();
	sc_close_vcd_trace_file(fp);

	openGTKwave();
	return 0;
}