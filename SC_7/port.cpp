#include <systemc>
using namespace sc_core;
SC_MODULE(MODULE1){
	sc_signal<int>s;
	sc_port<sc_signal_out_if<int>>p;
	SC_CTOR(MODULE1){
		SC_THREAD(selfwrite);
		SC_THREAD(selfread);
		sensitive<< s ;
		dont_initialize();
		SC_THREAD(outsidewrite);
	}
	void selfwrite(){
		int val = 1;
		while(true){
			s.write(val++);
			wait(1,SC_SEC);
		}
	}
	void selfread(){
		while(true){
			std::cout<<sc_time_stamp()<<": reads from own channel, val=" << s.read() << std::endl;
			wait();
		}
	}
	void outsidewrite(){
		int val = 1;
		while(true){
			p->write(val++);
			wait(1,SC_SEC);
		}
	}

};
SC_MODULE(MODULE2){
	sc_port<sc_signal_in_if<int>>p;
	SC_CTOR(MODULE2){
		SC_THREAD(outsideread);
		sensitive<<p;
		dont_initialize();
	}
	void outsideread(){
		while(true){
			std::cout<<sc_time_stamp()<<": reads from outsided channel, val= " << p->read() << std::endl;
			wait();
		}
	}
};

int sc_main(int, char*[]){
	MODULE1 mod1("mod1");
	MODULE2 mod2("mod2");
	sc_signal<int>s;
	mod1.p(s);
	mod2.p(s);
	sc_start(10,SC_SEC);
	return 0;
}
