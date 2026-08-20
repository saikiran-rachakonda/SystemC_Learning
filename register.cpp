#include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
class regi : public sc_module {
	private :
		sc_uint<32>reg_cpu;
	public :
	       	SC_HAS_PROCESS(regi);
       		regi(sc_module_name nm) : sc_module(nm){
			SC_THREAD(test);
		}	
		void set_enable(sc_uint<1> en){
			reg_cpu.range(0,0) = en;
		}
		sc_uint<1> get_enable(){
			return reg_cpu.range(0,0);
		}
		void set_mode(sc_uint<2> md){
			reg_cpu.range(2,1) = md;
		}
		sc_uint<2> get_mode(){
			return reg_cpu.range(2,1);
		}
		void set_address(sc_uint<8> ad){
			reg_cpu.range(17,10) = ad;
		}
		sc_uint<8> get_address(){
			return reg_cpu.range(17,10);
		}
		void test(){
			cout<<reg_cpu<<endl;
			cout<<"enable:"<<get_enable()<<endl;
			cout<<"mode:"<<get_mode()<<endl;
			cout<<"address:"<<get_address()<<endl;
			
			set_enable(1);
			set_mode(3);
			set_address(0xAB);
			cout<<"----------------------------"<<endl;
			cout<<"enable:"<<get_enable()<<endl;
			cout<<"mode:"<<get_mode()<<endl;
			cout<<"address:"<<get_address()<<endl;

			cout<<reg_cpu<<endl;	
		}
};

int sc_main(int argc, char* argv[]){
	regi reg_bit("reg");
	sc_start();	
	return 0;
}
