#include <systemc.h>
#include "counter_assignment.h"


SC_MODULE(Top)
{
    // Signals
   
    sc_clock clk;

    sc_signal<bool> reset;
    sc_signal<bool> up_down;
    sc_signal<sc_uint<2>> mode;
    sc_signal<bool> overload;
    sc_signal<sc_uint<8>> load_value;
    sc_signal<sc_uint<8>> count;

    // Counter instance
    updowncounter counter;


    SC_CTOR(Top)
        : clk("clk", sc_time(10, SC_NS)),
          counter("counter")
    {
       
        counter.clock(clk);
        counter.reset(reset);
        counter.up_down(up_down);
        counter.md(mode);
        counter.overload(overload);
        counter.load_value(load_value);
        counter.count(count);
	
        SC_THREAD(stimulus_thread);
    }


    // Stimulus
    void stimulus_thread()
    {
       
        // Initial values
       
        reset.write(0);
        up_down.write(1);
        mode.write(0);
        overload.write(0);
        load_value.write(0);
	
        // RESET
       
        cout <<endl<< "RESET TEST"<<endl;

        reset.write(1);

        wait(20, SC_NS);

        reset.write(0);

        // UP COUNT - SATURATED MODE
       
        cout <<endl<< "UP COUNT - SATURATED"<<endl;

        up_down.write(1);
        mode.write(0);

        wait(100, SC_NS);


        // OVERLOAD
        // Load 250
       
       	cout <<endl<< "OVERLOAD TEST"<<endl;

        load_value.write(250);
        overload.write(1);

        wait(10, SC_NS);

        overload.write(0);

        // Continue UP
       
       	wait(100, SC_NS);


        // WRAP MODE
       
       	cout << endl<<"WRAP MODE"<<endl;

        mode.write(1);
        up_down.write(1);

        wait(100, SC_NS);
  
        // DOWN COUNT - WRAP
     
        cout << endl << "DOWN COUNT - WRAP"<<endl;

        up_down.write(0);

        wait(100, SC_NS);

	// ZERO MODE

        cout << endl << "ZERO MODE"<<endl;

        mode.write(2);
        up_down.write(0);

        wait(100, SC_NS);

        // OVERLOAD AGAIN

        cout << endl << "OVERLOAD 5"<<endl;

        load_value.write(5);
        overload.write(1);

        wait(10, SC_NS);

        overload.write(0);

        wait(50, SC_NS);

        cout << endl << "SIMULATION COMPLETE"<<endl;

        sc_stop();
    }
};

int sc_main(int argc, char* argv[])
{
    Top top("top");

    sc_start();

    return 0;
}
