#include <systemc>
using namespace sc_core;

class Scaler : public sc_module {
	public :
		sc_in<int> in;
		sc_out<int> out;

		SC_HAS_PROCESS(Scaler);

		Scaler(sc_module_name nm, int factor)
			: sc_module(nm), m_factor(factor){
				SC_METHOD(scale);
				sensitive<<in;
			}
	private :
		void scale(){
			out.write(in.read() * m_factor);
		}
		int m_factor;
};


int sc_main(int argc, char* argv[]){
	Scaler scaler("scaler", 10);
	sc_signal<int>in, out;
	scaler.in(in);
	scaler.out(out);
	sc_start(1,SC_NS);
	in.write(1);		
	std::cout<<out<<std::endl;
	sc_start(1,SC_NS);
	std::cout<<out<<std::endl;
	return 0;
}
