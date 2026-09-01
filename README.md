# SystemC_Learning
# we have designed an up down synchronous 8 bit counter with 3 modes
# saturated, wrap, zero
# with overload functionality
# use the below command to compile the counter
g++ -std=c++17 -Wall -I"$SYSTEMC_HOME/include" couter_top.cpp -L"$SYSTEMC_HOME/lib-linux64" -lsystemc -Wl,-rpath,"$SYSTEMC_HOME/lib-linux64" -o couter_top

