#include <systemc>
using namespace std;
using namespace sc_core ;

// ---------------------------- 1 --------------------------

SC_MODULE(leaf){
	SC_CTOR(leaf){
		SC_THREAD(fromleaf);
		cout<<"I am from leaf : constructor : "<<name()<<endl;
	}
	void fromleaf(){
		cout<<"I am from leaf : from function : "<<name()<<endl;
	}
};

SC_MODULE(submodule){
	leaf aa;
	SC_CTOR(submodule) : aa("aa") {
		SC_THREAD(fromsubmodule);
		cout<<"I am from submodule : constructor :  "<<name()<<endl;
	}
	void fromsubmodule(){
		cout<<"I am from submodule : from function : "<<name()<<endl;
	}
};

SC_MODULE(top){
	submodule one, two;
	SC_CTOR(top) : one("one"), two("two"){
		SC_THREAD(fromtop);
		cout<<"I am from top : constructor : "<<name()<<endl;
	}
	void fromtop(){
		cout<<"I am from top : function : "<<name()<<endl;
	}
};

// -------------------------- 2 -----------------------------
//---------------------- interface --------------------------
class labm_if : virtual public sc_interface{
	public : 
		virtual void write(int data) = 0 ;
		virtual int read()=0 ;	
	//	virtual const sc_event& default_event() const = 0 ;
};

// -------------------------- 3 -------------------------------
// ----------------------- channel ---------------------------

class labm_channel : public sc_prim_channel, public labm_if {
	
	private : 
		int data ;
		bool data_available ;
		sc_event data_event; 
	public : 
	labm_channel(sc_module_name name) : sc_prim_channel(name) {
		//cout<<"I am from top."<<name()<<endl;
		data = 0 ;
		data_available = false;

	}
	void write(int value){
		data = value ;
		data_available = true;
		data_event.notify(SC_ZERO_TIME);
	}
	int read(){
		data_available = false;
		return data;
	}
	const sc_event& default_event() const /*override*/ {
		return data_event;
	}
};

// ----------------------------------- 4 --------------------------
// ------------------ connection between the modules --------------

class producer : public sc_module{
	public : 
		sc_port<labm_if> out;
		SC_CTOR(producer){
			SC_THREAD(process);
		}
		void process(){
			cout<<"port name:"<<out.name()<<endl;
			cout<<"port kind:"<<out.kind()<<endl;
			wait(SC_ZERO_TIME);
			out->write(100);
		}
};
class consumer : public sc_module{
	public : 
		sc_port<labm_if> in;
		SC_CTOR(consumer){
			SC_THREAD(process);
		}
		void process(){
			cout<<"port name:"<<in.name()<<endl;
			cout<<"port kind:"<<in.kind()<<endl;
			wait(in->default_event());
			int value = in->read();
			cout<<"Received value is: "<<value<<endl;
		}
};
class top_second : public sc_module{

	public : 
		labm_channel channel;
		producer prod;
		consumer cons;
		SC_CTOR(top_second) : channel("channel"), prod("prod"), cons("cons"){
			prod.out(channel);
			cons.in(channel);
		}
};
int sc_main(int argc, char* argv[]){
	// top a("top");
	top_second b("top_second");	
	sc_start();
	return 0;
}
