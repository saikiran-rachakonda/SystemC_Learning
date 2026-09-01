#include<systemc>
using namespace std;
using namespace sc_core;

// --------------- 1 -------------------

SC_MODULE(Producer){
	sc_fifo_out<int>out;
	SC_CTOR(Producer){
		SC_THREAD(produce);
	}
	void produce(){
		for(int i=0;i<5;i++){
			out.write(i);
		}
	}
};

SC_MODULE(Consumer){
	sc_fifo_in<int>in;
	SC_CTOR(Consumer){
		SC_THREAD(consume);
	}
	void consume(){
		for(int i=0;i<10;i++){
			int val = in.read();
			cout << val << endl;
		}
	}
};

// ----------------- 2 -------------------
//---------------------- interface --------------------------
class labm_if : virtual public sc_interface{
	public : 
		virtual void write(int data) = 0 ;
		virtual int read()=0 ;	
	//	virtual const sc_event& default_event() const = 0 ;
};

class labm_channel : public sc_prim_channel, public labm_if {
	
	private : 
		int data ;
		sc_event data_event; 
	public : 
	labm_channel(sc_module_name name) : sc_prim_channel(name) {
		data = 0 ;

	}
	void write(int value){
		data = value ;
		data_event.notify(SC_ZERO_TIME);
	}
	int read(){
		return data;
	}
	const sc_event& default_event() const {
		return data_event;
	}
};

SC_MODULE(test_class){
	sc_port<labm_channel> port;
	void react(){
		cout<<"test module reacting at : " << sc_time_stamp() << endl ;
	}
	SC_CTOR(test_class){
		SC_METHOD(react);
		sensitive << port ;
		dont_initialize() ;
	}
};

int sc_main(int argc, char* argv[])
	
	/*sc_fifo<int>fifo(10);
	Producer prod("prd");
	Consumer cons("cos");
	prod.out(fifo);
	cons.in(fifo);*/
	
	labm_channel chan;
	test_class tm("tm");
	tm.port(chan);

	sc_start(1, SC_NS);
	chan.write(1);
	sc_start(10, SC_NS);
	return 0;
}
