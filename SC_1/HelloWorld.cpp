#include <systemc>
using namespace sc_core;
SC_MODULE(Hello){
	SC_CTOR(Hello){
		SC_THREAD(say_hello);
	}
	void say_hello() {
		std::cout<<"Hello, SystemC world!" << std::endl;
		std::cout<<"time is " << sc_time_stamp() << std::endl;
	}
};

int sc_main(int argc, char* argv[]){
	Hello h("h");
	sc_start();
	return 0;
}
