#include <systemc>
using namespace sc_core;

SC_MODULE(Talker){
	SC_CTOR(Talker){
		SC_THREAD(runtw);
		SC_THREAD(run);
	}
	void run() {
		wait(10, SC_NS);
		std::cout<<"run hello at "<< sc_time_stamp() << "\n";
	}
	void runtw(){
		while(true){
			std::cout<<"runtw hello at "<< sc_time_stamp() << "\n";
			wait(10, SC_NS);
			if(sc_time_stamp()==sc_time(100,SC_NS)){
				sc_stop();
			}
		}
	}
};

int sc_main(int argc, char* argv[]){
	Talker talker("talker");
	sc_start();
	
	return 0;
}
