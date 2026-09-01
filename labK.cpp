#include<systemc>
using namespace sc_core;
using namespace std;
// ----------------------- 1. Mutex --------------------------
SC_MODULE(dummy_mutex){
	sc_mutex mtx;
	SC_CTOR(dummy_mutex){
		SC_THREAD(one);
		SC_THREAD(two);
	}

	void one(){	
		if(mtx.trylock()) cout<<"one got the mtx"<<endl;
		mtx.lock();
		//cout<<"one : "<<sc_time_stamp()<<endl;
	//	wait(20, SC_NS);
		cout<<"one : "<< sc_time_stamp()<<endl;
		mtx.unlock();
	}

	void two(){
		//cout<<"two : "<< sc_time_stamp()<<endl;
		//wait(1, SC_NS);
		if(mtx.trylock()) cout<<"two got the mtx"<<endl;
		cout<<"two : " << sc_time_stamp()<<endl;
		mtx.lock();
		wait(30,SC_NS);
		cout<<"two : "<< sc_time_stamp()<<endl;
		mtx.unlock();
	}
};
int sc_main(int argc, char* argv[]){
	//dummy_mutex("dum");
	sc_start(100, SC_NS);
	return 0;
}
