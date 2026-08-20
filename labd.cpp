#include<systemc>
using namespace sc_core;
using namespace std;
SC_MODULE(Adder){
	sc_in<int>a, b;
	sc_out<int> sum;
	SC_CTOR(Adder){
		SC_METHOD(add);
		sensitive<<a<<b;
	}
	void add(){
		sum.write(a.read()+b.read());
	}
};
class Scalar : public sc_module {
	private :
		int m_factor;
		void scale(){
			out.write(in.read()*m_factor);
		}
	public :
		sc_in<int>in;
		sc_out<int>out;
		SC_HAS_PROCESS(Scalar);
		Scalar(sc_module_name nm, int factor):sc_module(nm),m_factor(factor){
			SC_METHOD(scale);
			sensitive << in ;
		}

};
SC_MODULE(Top){
	sc_signal<int>sa,sb,ssum;
	sc_signal<int>sout;
	Adder adder;
	Scalar scalar;
	SC_CTOR(Top):adder("adder"),scalar("scalar",10){
		adder.a(sa),adder.b(sb),adder.sum(ssum);
		scalar.in(ssum),scalar.out(sout);
		SC_THREAD(stimulus);
	}
	void stimulus(){
		sa.write(3);
		sb.write(4);
		wait(1,SC_NS);
		cout<<sc_time_stamp()<<sa.read()<<" "<<sb.read()<<" "<<ssum.read()<<" "<<sout.read()<<" "<<"first"<<endl;
		sa.write(5);
		sb.write(6);
		wait(1,SC_NS);
		cout<<sc_time_stamp()<<sa.read()<<" "<<sb.read()<<" "<<ssum.read()<<" "<<sout.read()<<" "<<"second"<<endl;
		sa.write(7);
		sb.write(8);
		wait(1,SC_NS);
		cout<<sc_time_stamp()<<sa.read()<<" "<<sb.read()<<" "<<ssum.read()<<" "<<sout.read()<<" "<<"third"<<endl;
	}
};

int sc_main(int argc, char* argv[]){
	Top top("top");
	sc_start(10,SC_NS);
	return 0;
}
