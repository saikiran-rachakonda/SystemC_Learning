#include <systemc>
using namespace sc_core;

SC_MODULE(delta){
	int x = 1, y = 1;
	SC_CTOR(delta){
		SC_THREAD(multiply_x);
		SC_THREAD(add_x);
		//SC_THREAD(add_y);
		//SC_THREAD(multiply_y);
	}
	void add_x(){
		std::cout<<sc_time_stamp()<<"add_x: "<< x << " + 2 = " ;
		x += 2;
		std::cout<<x<<std::endl;
	}
	void multiply_x(){
		wait(SC_ZERO_TIME);
		std::cout<<sc_time_stamp()<<"multiply_x: "<<x<<" * 3 = ";
		x *= 3;
		std::cout<<x<<std::endl;
	}
};

int sc_main(int argc, char* argv[]){
	delta deltaa("deltaa");
	sc_start(10,SC_NS);
	return 0;
}
