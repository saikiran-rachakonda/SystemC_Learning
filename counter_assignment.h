#include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
SC_MODULE(updowncounter){

	// input
	sc_in<bool>clock;
	sc_in<bool>reset;
	sc_in<sc_uint<2>>md; // 0 - saturated, 1-wrap, 2-zero
	sc_in<bool> up_down; // 1 : up , 0 : down.
	sc_in<bool> overload;
	sc_in<sc_uint<8>> load_value;

	// output
	sc_out<sc_uint<8>> count;

	SC_CTOR(updowncounter){
		SC_THREAD(counting_thread);
		sensitive << clock.pos();
	}

	void counting_thread(){
		sc_uint<8> nxt_count = 0 ;
		cout<<"INITIAL COUNTER VALUES :"<< sc_time_stamp()<<endl;
	       	cout<<"reset:"<<reset.read()<<endl;
		cout<<"mode :"<<md.read()<<endl;
		cout<<"up_down_value :"<<up_down.read()<<endl;
		cout<<"overload :"<<overload.read()<<endl;
		cout<<"load value :"<<load_value.read()<<endl;	
		while(true){
			wait();
			if(reset.read()){
				nxt_count = 0 ;
				count.write(nxt_count);
				cout<<endl<<"COUNTER RESET at : "<<sc_time_stamp()<<endl;
				continue;
			}
			if(overload.read()){
				nxt_count = load_value.read();
				count.write(nxt_count);
				cout<<endl<<"COUNTER OVERLOADED at : "<<sc_time_stamp()<<endl;
				continue;
			}
			if(up_down.read()) {
				if(nxt_count == 255){
					switch(md.read()){
						case 0 :
							nxt_count = 255;
							break;
						case 1 :
						       	nxt_count = 0;
					       		break;
					 	case 2 :
							nxt_count = 0;
							break;
						default : 
							nxt_count = 0;
							break;	
					}
				}
				else nxt_count++;
			}
			else{
				if(nxt_count == 0){
					switch(md.read()){
						case 0 :
							nxt_count = 0;
							break;
						case 1 :
						       	nxt_count = 255;
					       		break;
					 	case 2 :
							nxt_count = 0;
							break;
						default : 
							nxt_count = 0;
							break;	
					}
				}
				else nxt_count--;
			}
			count.write(nxt_count);
			cout<<endl<<"COUNT operation done at: "<< sc_time_stamp()<< " current count is :"<< nxt_count << " mode is :" << md.read() << endl;
		}
	}

};
