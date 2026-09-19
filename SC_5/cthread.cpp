#include <systemc>
using namespace sc_core;
SC_MODULE(Sender){
	sc_in<bool> clk;
	SC_CTOR(Sender){
		SC_CTHREAD(run,clk.neg());
	}
	void run(){
		while(true){
			std::cout<<"write 1 : "<<sc_time_stamp()<<std::endl;
			wait();
			std::cout<<"write 2 : "<<sc_time_stamp()<<std::endl;
			wait();
		}
	}
};

int sc_main(int argc, char* argv[]){
	Sender sender("sender");
	sc_signal<bool>clk;
	sender.clk(clk);
	clk.write(0);
	sc_start(1,SC_NS);
	clk.write(1);
	sc_start(1,SC_NS);
	clk.write(0);
	sc_start(1,SC_NS);
	clk.write(1);
	sc_start(1,SC_NS);
	return 0;
}
