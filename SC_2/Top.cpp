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

SC_MODULE(Top){
	sc_signal<int>a, b, s;
	Adder adder;
	SC_CTOR(Top) : adder("adder"){
		adder.a(a);
		adder.b(b);
		adder.sum(s);
		SC_THREAD(apply_stimulus);
		SC_METHOD(print_sum);
		sensitive<<s;
	}
	void apply_stimulus(){
		wait(1,SC_NS);
		a.write(3);
		b.write(4);
		wait(1,SC_NS);
	}
	void print_sum(){
		std::cout<<"the sum of : "<<a.read()<<" and "<<b.read()<<"is: "<<s.read()<<" at :"<<sc_time_stamp()<<std::endl;
	}

};

int sc_main(int argc, char* argv[]){
	Top top("top");
	sc_start();	
	return 0;

}
