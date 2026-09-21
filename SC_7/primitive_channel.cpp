#include<systemc>
#include<string>
using namespace sc_core;

class GENERATOR_IF : public sc_interface {
	public : 
		virtual void notify() = 0;
};

class RECEIVER_IF : public sc_interface {
	public : 
		virtual const sc_event& default_event() const = 0;
};

class INTERRUPT : public sc_prim_channel, public GENERATOR_IF, public RECEIVER_IF{
	public : 
		INTERRUPT(sc_module_name name) : sc_prim_channel(name){}
		void notify(){
			e.notify();
		}
		const sc_event& default_event() const {
			return e;
		}
	private : 
		sc_event e;
};
SC_MODULE(GENERATOR){
	sc_port<GENERATOR_IF> p;
	SC_CTOR(GENERATOR){
		SC_THREAD(gen_interrupt);
	}
	void gen_interrupt(){
		while(true){
			p->notify();
			wait(1,SC_SEC);
		}
	}
};
SC_MODULE(RECEIVER){
	sc_port<RECEIVER_IF>p;
	SC_CTOR(RECEIVER){
		SC_THREAD(rcv_interrupt);
		sensitive << p;
		dont_initialize();
	}
	void rcv_interrupt(){
		while(true){
			std::cout << sc_time_stamp() << ": interrupt received."<< std::endl;
			wait();
		}
	}
};
int sc_main(int,char*[]){
	GENERATOR generator("generator");
	RECEIVER receiver("receiver");
	INTERRUPT interrupt("interrupt");
	generator.p(interrupt);
	receiver.p(interrupt);
	sc_start(10,SC_SEC);
	return 0;
}
