#include <systemc.h>
using namespace sc_core;
using namespace std;
SC_MODULE(Hello){
	SC_CTOR(Hello){
		SC_THREAD(say_welcome);
		SC_THREAD(say_hello);
	}
	void say_welcome(){
		while(true){
			cout<<"welcome to the SystemC world!"<<endl;
			cout<<"time is:"<<sc_time_stamp()<<endl;
			wait(300, SC_MS);
		}
	}
	void say_hello(){
		cout<<"hello world!"<<endl;
		cout<<"time is:"<<sc_time_stamp()<<endl;
	}
};
int sc_main(int argv, char* argc[]){
	Hello h("h");
	sc_start();
	return 0;
}
