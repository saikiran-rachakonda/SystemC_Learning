#include <systemc>
using namespace sc_core;
SC_MODULE(SIGNAL){
	sc_signal<int>s;
	sc_signal<int> s1, s2;

	SC_CTOR(SIGNAL){
		//SC_THREAD(readwrite);
		SC_THREAD(prod1);
		SC_THREAD(prod2);
		SC_THREAD(cons);
		sensitive << s1 << s2 ;
		dont_initialize();
	}
	void readwrite(){
		s.write(3);
		std::cout<< "s= " << s << ";" << s.read() << std::endl;
		wait(SC_ZERO_TIME);
		std::cout << " after delta_cycle, s = " << s << std:: endl;

		s = 4 ;
		s = 5 ;

		int tmp = s;
		std::cout << "s= " << tmp << std::endl;
		wait(SC_ZERO_TIME);
		std::cout << "after delta_cycle, s = " << s.read() << std::endl;
	}
	void prod1(){
		int v = 1;
		while(true){
			s1.write(v++);
			wait(2,SC_SEC);
		}
	}
	void prod2(){
		int v = 1 ;
		while(true){
			s2 = v++;
			wait(3,SC_SEC);
		}
	}
	void cons(){
		while(true){
			if(s1.event() == true && s2.event() == true){
				std::cout << sc_time_stamp() << ": s1 and s2 triggerd " << std::endl;
			} else if (s1.event() == true){
				std::cout << sc_time_stamp() << ": s1 triggerd " << std::endl;
			}else{
				std::cout << sc_time_stamp() << ": s2 triggered " << std::endl;
			}
			wait();
		}
	}
};
int sc_main(int,char*[]){
	SIGNAL sign("sign");
	sign.s = -1;
	sc_start(7,SC_SEC);
	return 0;
}
