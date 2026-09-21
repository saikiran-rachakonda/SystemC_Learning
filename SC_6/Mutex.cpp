#include <systemc>
using namespace sc_core;
SC_MODULE(Mutex){
	sc_mutex m;
	SC_CTOR(Mutex){
		SC_THREAD(t1);
		SC_THREAD(t2);
	}
	void t1(){
		while(true){
			if(m.trylock() == -1){
				m.lock();
				std::cout<<sc_time_stamp()<<"t1 by lock()"<<std::endl;
			}
			else{	
				std::cout<<sc_time_stamp()<<"t1 by unlock()"<<std::endl;
			}
			wait(1,SC_SEC);
			m.unlock();
			std::cout<<sc_time_stamp()<<"unlocked by t1"<<std::endl;
			wait(SC_ZERO_TIME);
		}
	}
	void t2(){
		while(true){
			if(m.trylock() == -1){
				m.lock();
				std::cout<<sc_time_stamp()<<"t2 by lock()"<<std::endl;
			}
			else{	
				std::cout<<sc_time_stamp()<<"t2 by unlock()"<<std::endl;
			}
			wait(1,SC_SEC);
			m.unlock();
			std::cout<<sc_time_stamp()<<"unlocked by t2"<<std::endl;
			wait(SC_ZERO_TIME);
		}
	}
};

int sc_main(int,char*[]){
	Mutex mutex("mutex");
	sc_start(4,SC_SEC);
	return 0;
}
