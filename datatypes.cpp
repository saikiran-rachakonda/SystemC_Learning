#define SC_INCLUDE_FX
#include <systemc>

using namespace sc_dt;
using namespace std;
int sc_main(int argc, char* argv[]){
	cout<<"-------------- bit vector ------------"<<endl;
	sc_bv<5> positions = "01101";
	//sc_bit one = '0';
	cout<<"sc bit vector positions:"<<positions<<endl;
	cout<<"positions.and_reduce :"<<positions.and_reduce()<<endl;
	cout<<"positions.or_reduce :"<<positions.or_reduce()<<endl;
	cout<<"-------------- logic vector ------------"<<endl;
	//sc_logic one = 'z';
	//cout<<"sc logic one: "<<one<<endl;
	//sc_lv<6>two = "0x10z1";
	//cout<<"sc lv : "<<two<<endl;
	sc_lv<1> zero = '0';
	sc_lv<1> one = '1';
	sc_lv<1> z = 'z';
	sc_lv<1> x = 'x';
	cout<<"0 & z= "<<(zero&z)<<": 0 | z= "<<(zero|z)<<": 0 & x= "<<(zero&x)<<": 0 | x= "<<(zero|x)<<endl;
       	cout<<"1 & z= "<<(one&z)<<": 1 | z= "<<(one|z)<<": 1 & x= "<<(one&x)<<": 1 | x= "<<(one|x)<<endl;
	cout<<"z & x= "<<(z&x)<<": z | x= "<<( z|x)<<endl;	
	cout<<"-------------- int ---------------------"<<endl;
	sc_int<4> signed_int = 9;
	sc_uint<4> unsigned_int  = 17;
	cout<<"signed int: "<<signed_int/*<<signed_int.size()*/<<endl;
	cout<<"un signed int: "<<unsigned_int<<endl;
	sc_uint<16> labf = 1023;
	cout<<labf<<"labf range 6,0 : "<<labf.range(6,0)<<endl;
	sc_int<2> concat_one = 0;
	sc_int<2> concat_two = 1;
	sc_int<2> concat_three =2;
	sc_int<2> concat_four =3;
	cout<<(concat_two,concat_one/*,concat_three,concat_four*/)<<endl;
	sc_int<8> sum_two = 10 * 200 ;
	cout<<sum_two<<endl;
	sc_int<16> sum_three = 10*200 ;
	cout<< sum_three << endl ;
	cout<<"------------- fixed --------------------"<<endl;
	sc_fixed<4,4,SC_TRN,SC_SAT> fixed_int = 9;
	cout<<"fixed int 6 , 3 " << fixed_int << endl;
	return 0;
}
