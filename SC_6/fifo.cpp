#include <systemc>
using namespace sc_core;

SC_MODULE(FIFO){
	sc_fifo<int> f1, f2, f3;
	SC_HAS_PROCESS(FIFO);
	FIFO(sc_module_name nm) : sc_module(nm), f1(2), f2(3), f3(4) {
		//SC_THREAD(gen1);
		//SC_THREAD(con1);
		//SC_THREAD(gen2);
		//SC_THREAD(con2);
		SC_THREAD(gen3);
		SC_THREAD(con3);
	}
	void gen1(){
		int v = 0;
		while(true){
			f1.write(v);
			std::cout<<sc_time_stamp() << " : gen 1 writes " << v++ << std::endl;
			wait(1,SC_SEC);
		}
	}
	void con1(){
		int v = -1;
		while(true){
			f1.read(v);
			std::cout<< sc_time_stamp() << ": cons 1 reads " << v << std::endl;
			wait(3,SC_SEC);
		}
	}
	void gen2(){
		int v = 0;
		while(true){
			while(f2.nb_write(v)== false ){
				wait(f2.data_read_event());
			}
			std::cout << sc_time_stamp() << ": gen2 writes " << v++ << std::endl;
			wait(1,SC_SEC);
		}	
	}
	void con2(){
		int v = -1;
		while(true){
			while(f2.nb_read(v)==false){
				wait(f2.data_written_event());
			}
			std::cout<<sc_time_stamp() << ": cons2 reads " << v << std::endl;
			wait(3,SC_SEC);
		}
	}
	void gen3(){
		int v = 0;
		while(true){
			std::cout << sc_time_stamp() << ": gen3, before write, #free/#available= " << f3.num_free() << "/" << f3.num_available() << std::endl;
			f3.write(v++);
			std::cout<< sc_time_stamp() << ": gen3, after write, #free/#available= " << f3.num_free() << "/" << f3.num_available() << std::endl;
			wait(1,SC_SEC);
		}
	}
	void con3(){
		int v = -1 ;
		while(true){
			std::cout << sc_time_stamp() << ": cons3, before read, #free/#available= " << f3.num_free() << "/" << f3.num_available() << std::endl;
			f3.read(v);
			std::cout << sc_time_stamp() << ": cons3, after read, #free/#available= " << f3.num_free() << "/" << f3.num_available() << std::endl;
			wait(3, SC_SEC);
		}
	}
};
int sc_main(int,char*[]){
	FIFO fifo("fifo");
	sc_start(10,SC_SEC);
	return 0;
}
