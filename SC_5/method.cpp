#include<systemc>
using namespace sc_core;
SC_MODULE(Method){
	SC_CTOR(Method){
		SC_METHOD(A);
		SC_METHOD(B);
		//SC_METHOD(C);
	}
	void A(){
		std::cout<<"hello!"<<sc_time_stamp()<<std::endl;
		next_trigger(1,SC_NS);
	}
	void B(){
		std::cout<<"world!"<<sc_time_stamp()<<std::endl;
		next_trigger(1,SC_NS);
	}
	void C(){
		std::cout<<sc_time_stamp()<<std::endl;
	}
};
int sc_main(int argc, char* argv[]){
	Method method("method");
	sc_start(10,SC_NS);
	std::cout<<"simulation time before sc stop."<< sc_time_stamp()<<std::endl;
	sc_stop();
	std::cout<<"simulation time after sc stop."<< sc_time_stamp()<<std::endl;
	return 0;
}
