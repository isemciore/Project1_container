#include "matrix.hpp"
#include <gtest/gtest.h>



class matrixTest : public ::testing::Test{
	protected:
		matrixTest(){}
		~matrixTest(){}
		virtual void SetUp(){m[0][0] = 1;}
		Matrix m ( 2,2);		
};

	
TEST_F(matrixTest, containRight){
	EXPECT_EQ(1,m[0][0]);
}


int main(int argc, char**argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
