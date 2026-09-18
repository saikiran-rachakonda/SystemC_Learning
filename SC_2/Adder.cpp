#include <systemc>
using namespace sc_core;

SC_MODULE(Adder) {
	
	sc_in<int> a, b;
	sc_out<int> sum;

	SC_CTOR(Adder){
		SC_METHOD(add);
		sensitive << a << b ;
	}
	void add(){
		sum.write(a.read()+b.read());
	}

};

int sc_main(int argc, char* argv[]){
	
	sc_signal<int> a, b, s;
	Adder adder("adder");

	adder.a(a);
	adder.b(b);
	adder.sum(s);

	sc_start(0,SC_NS);

	a.write(1);
	b.write(2);
	sc_start(1, SC_NS);
	std::cout<<s.read()<<"at"<<sc_time_stamp();
	sc_start(10,SC_NS);

	return 0;

}
