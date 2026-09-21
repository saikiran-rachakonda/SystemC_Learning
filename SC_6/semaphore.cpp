#include <systemc>
using namespace sc_core;

SC_MODULE(semaphoremod){
	sc_semaphore s;
	SC_HAS_PROCESS(semaphoremod);
	semaphoremod(sc_module_name nm) : sc_module(nm), s(2) {
		SC_THREAD(thread_1);
		SC_THREAD(thread_2);
		SC_THREAD(thread_3);
	}
	void thread_1(){
		while(true){
			std::cout<<sc_time_stamp()<<"--------------- :  thread 1, value is "<< s.get_value() << std::endl;
			if(s.trywait() == -1){
				s.wait();
				std::cout<<"blocked by thread 1 ------------------"<< std::endl;
			}
			std::cout<<sc_time_stamp()<<" :  locked by thread 1, value is "<< s.get_value() << std::endl;
			wait(1,SC_SEC);
			s.post();
			std::cout<<sc_time_stamp() << " : unlocked by thread 1, value is " << s.get_value() << std::endl;
			wait(SC_ZERO_TIME);
		}
	}
	void thread_2(){
		while(true){
			std::cout<<sc_time_stamp()<<"----------------- :  thread 2, value is "<< s.get_value() << std::endl;
			if(s.trywait() == -1){
				s.wait();
				std::cout<<"blocked by thread 2 ------------------"<< std::endl;
			}
			std::cout<<sc_time_stamp()<<" :  locked by thread 2, value is "<< s.get_value() << std::endl;
			wait(1,SC_SEC);
			s.post();
			std::cout<<sc_time_stamp() << " : unlocked by thread 2, value is " << s.get_value() << std::endl;
			wait(SC_ZERO_TIME);
		}
	}
	void thread_3(){
		while(true){
			std::cout<<sc_time_stamp()<<"---------------------------- :  thread 3, value is "<< s.get_value() << std::endl;
			if(s.trywait() == -1){
				s.wait();
				std::cout<<"blocked by thread 3 ------------------"<< std::endl;
			}
			std::cout<<sc_time_stamp()<<" :  locked by thread 3, value is "<< s.get_value() << std::endl;
			wait(1,SC_SEC);
			s.post();
			std::cout<<sc_time_stamp() << " : unlocked by thread 3, value is " << s.get_value() << std::endl;
			wait(SC_ZERO_TIME);
		}
	}
};

int sc_main(int, char*[]){
	semaphoremod semp("semp");
	sc_start(4, SC_SEC);
	return 0;
}
