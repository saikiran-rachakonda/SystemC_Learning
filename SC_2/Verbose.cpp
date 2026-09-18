#include <systemc>
using namespace sc_core;
int sc_main(int argc, char* argv[]){
	bool m_verbose = false;

	if(sc_argc() > 1 && std::string(sc_argv()[1]) == "-verbose"){
		m_verbose = true;
	}

	if(m_verbose){
		std::cout<<"verbosity enabled."<< std::endl;
	}

	return 0;
}
