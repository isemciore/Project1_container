#include <cxxtest/TestSuite.h>
#include "boolVector.hpp"
#include <iostream>
#include <sstream>

class vector_cxx_test : public CxxTest::TestSuite {
	Vector<bool> boolVector;
	Vector<bool> bool_vec_tttfft;
	Vector<bool> long_bool_vector;

	const Vector<bool> k_bool_vec = {false,true,false,true,true,true};
	
    void setUp(){
		bool_vec_tttfft = {true,true,true,false,false,true};
		long_bool_vector = Vector<bool>(60,false);
		long_bool_vector[3] = true;
		long_bool_vector[8] = true;
		long_bool_vector[9] = true;
		long_bool_vector[14] = true;
		long_bool_vector[15] = true;
		long_bool_vector[20] = true;
		long_bool_vector[59] = true;
    }


public:
	void test_vector_copy_assign(){
		boolVector = k_bool_vec;
		int start = 0;
		bool bool_values[] = {false,true,false,true,true,true};
		for(auto &bool_value: boolVector){
			TS_ASSERT_EQUALS(bool_value,bool_values[start]);
			start++;
		}
	}
	void test_vector_copy_construct(){
		Vector<bool> boolVector_construct = k_bool_vec;
		int start = 0;
		bool bool_values[] = {false,true,false,true,true,true};
		for(auto &bool_value: boolVector_construct){
			TS_ASSERT_EQUALS(bool_value,bool_values[start]);
			start++;
		}
	}
	void test_vector_move_ass(){
		boolVector = std::move(bool_vec_tttfft);
		int start = 0;
		bool bool_values[] = {true,true,true,false,false,true};
		for(auto &bool_value: boolVector){
			TS_ASSERT_EQUALS(bool_value,bool_values[start]);
			start++;
		}
		TS_ASSERT_EQUALS(bool_vec_tttfft.size(),(std::size_t)0);
	}

	void test_vector_move_construct(){
		Vector<bool> boolVector_construct = std::move(bool_vec_tttfft);
		int start = 0;
		bool bool_values[] = {true,true,true,false,false,true};
		for(auto &bool_value: boolVector_construct){
			TS_ASSERT_EQUALS(bool_value,bool_values[start]);
			start++;
		}
		TS_ASSERT_EQUALS(bool_vec_tttfft.size(),(std::size_t)0);
	}
	



	void test_vector_sort_start(){
		Vector<bool>::iterator f_it = long_bool_vector.begin();
		std::sort(f_it,f_it+12);
		TS_ASSERT_EQUALS(*(f_it+11),true);
		TS_ASSERT_EQUALS(*(f_it+10),true);
		TS_ASSERT_EQUALS(*(f_it+9),true);
		for(int i = 0; i <9;i++){
			TS_ASSERT_EQUALS(*(f_it+i),false);			
		}
		//std::sort(long_bool_vector.begin(),mid_iterator);
		//std::cout << *long_bool_vector.begin();
	}
	
	void test_vector_sort_whole(){
		std::sort(long_bool_vector.begin(),long_bool_vector.end());
		for(int i =53;i<60;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],true);
		}
		for(int i =0;i<53;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],false);
		}
	}
	
	void test_vector_sort_end(){
		std::sort(long_bool_vector.end()-42,long_bool_vector.end());
		for(int i =58;i<60;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],true);
		}
		for(int i =18;i<58;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],false);
		}	
	}
	
	void test_vector_sort_mid(){
		std::sort(long_bool_vector.begin()+14,long_bool_vector.begin()+35);
		TS_ASSERT_EQUALS(long_bool_vector[3],true);
		TS_ASSERT_EQUALS(long_bool_vector[8],true);
		TS_ASSERT_EQUALS(long_bool_vector[9],true);
		TS_ASSERT_EQUALS(long_bool_vector[59],true);
		
		TS_ASSERT_EQUALS(long_bool_vector[34],true);
		TS_ASSERT_EQUALS(long_bool_vector[33],true);
		TS_ASSERT_EQUALS(long_bool_vector[32],true);
		for(int i = 10; i < 32;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],false);
		}
		for(int i = 35; i < 59;i++){
			TS_ASSERT_EQUALS(long_bool_vector[i],false);
		}
		
	}
	
	
	
	
	void test_pointer_navigation(){
		Vector<bool>::iterator start_iterator = long_bool_vector.begin();
		start_iterator+=3;
		TS_ASSERT_EQUALS(*start_iterator,true);//3
		start_iterator-=-5;
		TS_ASSERT_EQUALS(*start_iterator,true);//8
		start_iterator++;
		TS_ASSERT_EQUALS(*start_iterator,true);//9
		start_iterator++;
		TS_ASSERT_EQUALS(*start_iterator,false);//10
		start_iterator--;
		TS_ASSERT_EQUALS(*start_iterator,true);//9
		++start_iterator;
		TS_ASSERT_EQUALS(*start_iterator,false);//10
		--start_iterator;
		TS_ASSERT_EQUALS(*start_iterator,true);//9
		
		std::advance(start_iterator,5);//14
		TS_ASSERT_EQUALS(*start_iterator,true);//14
		start_iterator++;
		TS_ASSERT_EQUALS(*start_iterator,true);//15
		start_iterator++;
		TS_ASSERT_EQUALS(*start_iterator,false);//16
		TS_ASSERT_EQUALS(std::distance(start_iterator,long_bool_vector.end()),44);
		
		start_iterator = start_iterator+44;
		TS_ASSERT_EQUALS(start_iterator,long_bool_vector.end());
		
		
	}

	void test_sizeCheck(){
		TS_ASSERT_EQUALS(k_bool_vec.size(),(std::size_t)6);
		TS_ASSERT_EQUALS(bool_vec_tttfft.size(),(std::size_t)6);
	}


    void test_initalization(){
		Vector<bool> bool_v_default();
		Vector<bool> bool_v_start_size(31);
		Vector<bool> bool_v_start_size_with_elt(20,true);
		Vector<bool> bool_v_start_size_init_list({true,true,true,false,false,true});
		
		for(auto& elt: bool_v_start_size_with_elt){
			TS_ASSERT_EQUALS(elt,true);
		}
	}
	
	void test_readindex(){
		TS_ASSERT_EQUALS(bool_vec_tttfft[0],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[1],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[2],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[3],false);
		TS_ASSERT_EQUALS(bool_vec_tttfft[4],false);
		TS_ASSERT_EQUALS(bool_vec_tttfft[5],true);
	}

	void test_assig_bracket(){
		bool_vec_tttfft[2] = false;
		bool_vec_tttfft[3] = true;
		TS_ASSERT_EQUALS(bool_vec_tttfft[0],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[1],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[2],false);
		TS_ASSERT_EQUALS(bool_vec_tttfft[3],true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[4],false);
		TS_ASSERT_EQUALS(bool_vec_tttfft[5],true);
		
		bool_vec_tttfft.push_back(true);
		TS_ASSERT_EQUALS(bool_vec_tttfft[6],true);
	}
	
	
	
	
	void test_foreach(){
		int start = 0;
		bool bool_values[] = {false,true,false,true,true,true};
		for(const auto &elt: k_bool_vec){
			TS_ASSERT_EQUALS(elt,bool_values[start]);
			start++;
		}
		bool some_bool_values[] = {true,true,true,false,false,true};
		start = 0;
		for(auto &elt: bool_vec_tttfft){
			TS_ASSERT_EQUALS(elt,some_bool_values[start]);
			start++;
		}
		
	}
 

};
	
