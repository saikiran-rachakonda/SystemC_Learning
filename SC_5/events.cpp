#include <systemc>
using namespace sc_core;
SC_MODULE(events){
	sc_event t1_event;
	sc_event t2_event;
	SC_CTOR(events){
		SC_THREAD(thread_one);
		//sensitive<<t1_event;
		//dont_initialize();
		SC_THREAD(thread_two);
		//sensitive<<t2_event;
		//dont_initialize();
	}
	void thread_one(){
		while(true){
			std::cout<<sc_time_stamp()<< " t1 "<<std::endl;
			t2_event.notify(1,SC_NS);
			wait(t1_event);
		}
	}
	void thread_two(){
		while(true){
			wait(t2_event);
			std::cout<<sc_time_stamp()<<" t2 "<<std::endl;
			t1_event.notify(1,SC_NS);
		}
	}
};
int sc_main(int argc, char* argv[]){
	events event("event");
	sc_start(10,SC_NS);	
	return 0;
}
