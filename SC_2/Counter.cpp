#include <systemc>
using namespace sc_core;
SC_MODULE(Counter){

	sc_in<bool> clk;

	SC_CTOR(Counter) : count(0) {
		SC_METHOD(tick);
		sensitive << clk.pos();
	}

	void tick(){ 
		++count;
		std::cout<<"count at : "<< sc_time_stamp()<<" is : "<< count << std::endl;	
	}
	int count;
};
int sc_main(int argc, char* argv[]){
	
	Counter counter("counter");
	sc_signal<bool>clk;
	counter.clk(clk);
	
	clk.write(false);
	sc_start(0, SC_NS);
	clk.write(true);

	sc_start(1, SC_NS);
	clk.write(false);
	sc_start(1,SC_NS);
	clk.write(true);
	
	sc_start(1,SC_NS);
	clk.write(false);
	sc_start(1,SC_NS);
	clk.write(true);
	
	sc_start(1,SC_NS);
	clk.write(false);
	sc_start(1,SC_NS);
	clk.write(true);
	
	sc_start(1,SC_NS);

	return 0;

}
