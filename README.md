# SystemC_Learning

g++ -std=c++17 -Wall -I"$SYSTEMC_HOME/include" file.cpp -L"$SYSTEMC_HOME/lib-linux64" -lsystemc -Wl,-rpath,"$SYSTEMC_HOME/lib-linux64" -o file

