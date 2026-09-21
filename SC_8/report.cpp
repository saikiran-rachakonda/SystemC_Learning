#include <systemc>
#include <string>
using namespace sc_core;

SC_MODULE(MODULE){
	sc_port<sc_signal<int>> p;
	SC_CTOR(MODULE){
		SC_REPORT_WARNING("ctor", "register function");
		SC_THREAD(writer);
		SC_THREAD(reader);
		sensitive << p ;
		dont_initialize();
	}
	void writer(){
		int v = 1;
		while(true){
			SC_REPORT_INFO("writer", ("write" + std::to_string(v)).c_str());
			p->write(v++);
			wait(1,SC_SEC);
		}
	}
	void reader(){
		while(true){
			SC_REPORT_INFO("reader", ("read" + std::to_string(p->read())).c_str());
			wait();
		}
	}
};
int sc_main(int,char*[]){
	sc_report_handler::set_log_file_name("report.log");
	sc_report_handler::set_actions("writer", SC_INFO, SC_LOG);
	MODULE mod("mod");
	sc_signal<int> s;
	mod.p(s);
	SC_REPORT_INFO("main", "simulation starts");
	sc_start(2,SC_SEC);
	SC_REPORT_INFO("main", "simulation ends");
	return 0;
}
