#include<systemc>
using namespace sc_core;
SC_MODULE(Thread){
	SC_CTOR(Thread){
		SC_THREAD(A);
		SC_THREAD(B);
		SC_THREAD(C);
		//SC_METHOD(display);
		//sensitive<<a<<b;
		//dont_initialize();
	}
	//sc_inout<int>a;
	//sc_inout<int>b;	
	void A(){
		while(true){
		std::cout<<"hello!";
	//	a.write(b.read());
		wait(1,SC_NS);
		}
	}
	void B(){
		while(true){
		//b.write(a.read());
		std::cout<<"world!";
		wait(1,SC_NS);
		}
	}
	void C(){
		while(true){
			std::cout<<std::endl;
			wait(1,SC_NS);
		}
	}
	//void display(){
	//	std::cout<<sc_time_stamp()<<" a: "<<a<<" b: "<<b<<std::endl;
	//}
};
int sc_main(int argc, char* argv[]){
	Thread thread("thread");
	//sc_signal<int>a;
	//sc_signal<int>b;
	//thread.a(a);
	//thread.b(b);
	//a.write(1);
	//b.write(2);
	//sc_start(1,SC_NS);
	//a.write(1);
	//b.write(2);
	sc_start(10,SC_NS);
	sc_stop();
	return 0;
}
