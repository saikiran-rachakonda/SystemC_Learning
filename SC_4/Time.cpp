#include <systemc>
using namespace sc_core;
using namespace sc_dt;
SC_MODULE(Clock){
	SC_HAS_PROCESS(Clock);
	sc_out<sc_bit>ou;
	Clock(sc_module_name nm,sc_time period)
		:sc_module(nm),CLK_PERIOD(period){
		SC_THREAD(generate_clock);
	}
	void generate_clock(){
		while(true){
			ou.write(~((ou.read())));
			wait(CLK_PERIOD/2);
			std::cout<<ou.read()<<" "<<sc_time_stamp()<<std::endl;
		}
	}
	private :
		sc_time CLK_PERIOD;
};
int sc_main(int argc, char* argv[]){
	
	sc_set_time_resolution(1,SC_NS);
	
	sc_time t1(10,SC_NS);
	
	Clock clk("clk",t1);
	sc_signal<sc_bit>ou;
	clk.ou(ou);	

	sc_start(1,SC_NS);
	std::cout<<t1<<std::endl;
	
	sc_time zero(SC_ZERO_TIME);
	std::cout<<zero<<std::endl;
	
	sc_time zerotwo(0,SC_NS);
	std::cout<<zerotwo<<std::endl;
	sc_start(100,SC_NS);
	//std::cout<<sc_get_time_resolution();	

	return 0;
}
