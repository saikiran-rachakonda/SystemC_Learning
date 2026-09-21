#include <systemc>
using namespace sc_core;
SC_MODULE(events){
	sc_event t2_event;
	SC_CTOR(events){
		SC_THREAD(thread_one);
		SC_THREAD(thread_two);
	}
	void thread_one(){
		while(true){
			t2_event.notify(1,SC_NS);
			if(sc_time_stamp()==sc_time(4,SC_NS)){
				t2_event.cancel();
				std::cout<<sc_time_stamp() << " t1 : event cancelled."<<std::endl;
			}
			wait(2,SC_NS);
			std::cout<<sc_time_stamp()<< " t1 "<<std::endl;
		}
	}
	void thread_two(){
		while(true){
			wait(t2_event);
			std::cout<<sc_time_stamp()<<" t2 "<<std::endl;
		}
	}
};
int sc_main(int argc, char* argv[]){
	events event("event");
	sc_start(10,SC_NS);	
	return 0;

}
