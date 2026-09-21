#include <systemc>
using namespace sc_core;

SC_MODULE(MODULE){
	sc_port<sc_signal<int>>p;
	SC_CTOR(MODULE){
		SC_THREAD(writer);
	}
	void writer() {
		int v = 1 ;
		while(true){
			p->write(v++);
			wait(1,SC_SEC);
		}
	}
};
int sc_main(int,char*[]){
	MODULE module("module");
	sc_signal<int>s;
	module.p(s);

	sc_trace_file* file = sc_create_vcd_trace_file("trace");
	sc_trace(file, s, "signal");
	sc_start(5, SC_SEC);
	sc_close_vcd_trace_file(file);
	return 0;
}
