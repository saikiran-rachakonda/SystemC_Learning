#define SC_INCLUDE_FX
#include <systemc>
#include <cstdint>
using namespace sc_core;
using namespace sc_dt;
int sc_main(int argc, char* argv[]){
	
	bool bool_datatype;
	std::cout<<"bool : " << bool_datatype<<" size :"<<sizeof(bool_datatype)<<std::endl;
	char char_datatype;
	std::cout<<"char : "<<char_datatype<<" size : "<<sizeof(char_datatype)<<std::endl;
	short short_datatype;
	std::cout<<"short : "<<short_datatype<<" size : "<<sizeof(short_datatype)<<std::endl;
	int int_datatype;
	std::cout<<"int : "<<int_datatype<<" size : "<<sizeof(int_datatype)<<std::endl;
	long long_datatype;
	std::cout<<"long : "<<long_datatype<<" size : "<<sizeof(long_datatype)<<std::endl;
	float float_datatype;
	std::cout<<"float : "<<float_datatype<<" size : "<<sizeof(float_datatype)<<std::endl;
	double double_datatype;
	std::cout<<"double : "<<double_datatype<<" size : "<<sizeof(double_datatype)<<std::endl;
	
       	sc_bit scBitDatatype;
	std::cout<<"sc_bit_datatype : "<< scBitDatatype << " size :  "<< sizeof(scBitDatatype)<<std::endl;
	
       	sc_logic scLogicDatatype;
	std::cout<<"sc_Logic_datatype : "<< scLogicDatatype << " size :  "<< sizeof(scLogicDatatype)<<std::endl;
	
       	sc_bv<3> scBvDatatype;
	std::cout<<"sc_Bv_datatype : "<< scBvDatatype << " size :  "<< sizeof(scBvDatatype)<<std::endl;
	
       	sc_lv<5> scLvDatatype;
	std::cout<<"sc_Lv_datatype : "<< scLvDatatype << " size : "<< sizeof(scLvDatatype)<<std::endl;

       	sc_int<10> scIntDatatype;
	std::cout<<"sc_Int_datatype : "<< scIntDatatype << " size : "<< sizeof(scIntDatatype)<<std::endl;

       	sc_bigint<65> scBigIntDatatype;
	std::cout<<"sc_bigint_datatype : "<< scBigIntDatatype << " size : "<< sizeof(scBigIntDatatype)<<std::endl;
       
	sc_fixed<10,1> scFixedDatatype;
	std::cout<<"sc_fixed_datatype : "<< scFixedDatatype << " size : "<< sizeof(scFixedDatatype)<<std::endl;
	
	return 0;
}
