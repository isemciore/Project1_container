#include <cxxtest/TestSuite.h>
#include "matrix.hpp"
#include <iostream>
#include <sstream>
//MATRIX 2 and 7 One have unkown error
class matrix_cxxTest : public CxxTest::TestSuite {
    Matrix rect1 = Matrix(2,3);
    Matrix rect2 = Matrix(3,4);
    Matrix slim1 = Matrix(1,3);
    Matrix slim2 = Matrix(4,1);
    Matrix sq1 = Matrix(2,2);
    Matrix sq2 = Matrix(3,3);
    int a,b,c,d,e,f;

    void setUp(){
        a = 2;
        b = -5;
        c = 7;
        d = 4;
        e = 2;
        f = -9;
        rect1[0][0] = a;
        rect1[0][1] = b;
        rect1[0][2] = a;
        rect1[1][0] = d;
        rect1[1][1] = f;
        rect1[1][2] = e;

        rect2[0][0] = a;
        rect2[0][1] = b;
        rect2[0][2] = c;
        rect2[0][3] = d;
        rect2[1][0] = e;
        rect2[1][1] = f;
        rect2[1][2] = a;
        rect2[1][3] = b;
        rect2[2][0] = e;
        rect2[2][1] = c;
        rect2[2][2] = a;
        rect2[2][3] = f;


        slim1[0][0] = b;
        slim1[0][1] = c;
        slim1[0][2] = d;

        slim2[0][0] = c;
        slim2[1][0] = d;
        slim2[2][0] = e;
        slim2[3][0] = f;

        sq1[0][0] = e;
        sq1[0][1] = f;
        sq1[1][0] = b;
        sq1[1][1] = a;

        sq2[0][0] = e;
        sq2[0][1] = f;
        sq2[0][2] = b;
        sq2[1][0] = a;
        sq2[1][1] = e;
        sq2[1][2] = f;
        sq2[2][0] = b;
        sq2[2][1] = c;
        sq2[2][2] = e;

    }


public:
    void test_MtrxCopy(){
        Matrix dummy(rect1);
        TS_ASSERT_EQUALS(dummy[0][0] , a);
        TS_ASSERT_EQUALS(dummy[0][1] , b);
        TS_ASSERT_EQUALS(dummy[0][2] , a);
        TS_ASSERT_EQUALS(dummy[1][0] , d);
        TS_ASSERT_EQUALS(dummy[1][1] , f);
        TS_ASSERT_EQUALS(dummy[1][2] , e);
    }
    void test_MtrxCopyAss(){
        Matrix dummy;
        dummy = rect1;
        TS_ASSERT_EQUALS(dummy[0][0] , a);
        TS_ASSERT_EQUALS(dummy[0][1] , b);
        TS_ASSERT_EQUALS(dummy[0][2] , a);
        TS_ASSERT_EQUALS(dummy[1][0] , d);
        TS_ASSERT_EQUALS(dummy[1][1] , f);
        TS_ASSERT_EQUALS(dummy[1][2] , e);
    }

    void test_instreamAss(){
        Matrix temp;
        std::istringstream (" [ 1 3 5 -2 ; -1 4 -6 5 ; 7 2 -8 9 ] ") >> temp;
        TS_ASSERT_EQUALS(1 , temp[0][0]);
        TS_ASSERT_EQUALS(3 , temp[0][1]);
        TS_ASSERT_EQUALS(5 , temp[0][2]);
        TS_ASSERT_EQUALS(-2 , temp[0][3]);
        TS_ASSERT_EQUALS(-1 , temp[1][0]);
        TS_ASSERT_EQUALS(4 , temp[1][1]);
        TS_ASSERT_EQUALS(-6 , temp[1][2]);
        TS_ASSERT_EQUALS(5 , temp[1][3]);
        TS_ASSERT_EQUALS(7 , temp[2][0]);
        TS_ASSERT_EQUALS(2 , temp[2][1]);
        TS_ASSERT_EQUALS(-8 , temp[2][2]);
        TS_ASSERT_EQUALS(9 , temp[2][3]);

        std::istringstream(" [ 1 ] ") >> temp;
        TS_ASSERT_EQUALS(temp.cols() , (unsigned ) 1);
        TS_ASSERT_EQUALS(temp.rows() , (unsigned) 1);
        TS_ASSERT_EQUALS(temp[0][0],1);
    }



    void test_outStream(){
        Matrix writeThis;
        std::istringstream (" [ 1 3 5 -2 ; -1 4 -6 5 ; 7 2 -8 9 ] ") >> writeThis;
        std::ostringstream outTest;
        outTest << writeThis;
        TS_ASSERT_EQUALS(outTest.str(),"[\n       1      3      5     -2 ;\n      -1      4     -6      5 ;\n       7      2     -8      9 ]\n")
    }


    void test_matAddmat(){
        Matrix temp(2,3);
        std::istringstream(" [ 1 3 4 ; -6 -9 2 ] ") >> temp;
        temp = temp+rect1;
        TS_ASSERT_EQUALS(temp[0][0], 1 +a );
        TS_ASSERT_EQUALS(temp[0][1], 3 + b ); ///MATRIX 1 FAILS ADDITION
        TS_ASSERT_EQUALS(temp[0][2], 4 +a );
        TS_ASSERT_EQUALS(temp[1][0], -6+d );
        TS_ASSERT_EQUALS(temp[1][1], -9+f );
        TS_ASSERT_EQUALS(temp[1][2], 2 +e);
    }

    void test_mattSubmat(){
        Matrix temp(2,3);
        std::istringstream(" [ 1 3 4 ; -6 -9 2 ] ") >> temp;
        temp = temp-rect1;
        TS_ASSERT_EQUALS(temp[0][0], 1 -a );
        TS_ASSERT_EQUALS(temp[0][1], 3 - b );
        TS_ASSERT_EQUALS(temp[0][2], 4 -a );
        TS_ASSERT_EQUALS(temp[1][0], -6-d );
        TS_ASSERT_EQUALS(temp[1][1], -9-f );
        TS_ASSERT_EQUALS(temp[1][2], 2 -e);
    }

    void test_mtrxMult(){
        Matrix res = slim1*rect2*slim2;
        TS_ASSERT_EQUALS(res.rows() , (unsigned) 1);
        TS_ASSERT_EQUALS(res.cols() , (unsigned) 1);
        TS_ASSERT_EQUALS(res[0][0] , 837);

        Matrix resb = slim1*rect2;
        TS_ASSERT_EQUALS(resb[0][0] , 12);
        TS_ASSERT_EQUALS(resb[0][1] , -10);
        TS_ASSERT_EQUALS(resb[0][2] , -13);
        TS_ASSERT_EQUALS(resb[0][3] , -91);
        TS_ASSERT_EQUALS(resb.rows() , (unsigned) 1);
        TS_ASSERT_EQUALS(resb.cols() , (unsigned) 4);

        Matrix resc = rect2*slim2;

        TS_ASSERT_EQUALS(resc[0][0] , -28);
        TS_ASSERT_EQUALS(resc[1][0] , 27);
        TS_ASSERT_EQUALS(resc[2][0] , 127);
        TS_ASSERT_EQUALS(resc.rows() , (unsigned) 3);
        TS_ASSERT_EQUALS(resc.cols() , (unsigned) 1);


        Matrix res2 = sq1*sq1*sq1*sq1;
        TS_ASSERT_EQUALS(res2[0][0], 3121);
        TS_ASSERT_EQUALS(res2[0][1], -3528);
        TS_ASSERT_EQUALS(res2[1][0], -1960);
        TS_ASSERT_EQUALS(res2[1][1], 3121);
        TS_ASSERT_EQUALS(res2.rows() , (unsigned) 2);
        TS_ASSERT_EQUALS(res2.cols() , (unsigned) 2);



    }


    void test_matrxSclMULT(){
            rect1 = rect1*5;
            sq2 = sq2*4;
            slim2 = slim2*2;

            TS_ASSERT_EQUALS(sq2[0][0] , e*4);
            TS_ASSERT_EQUALS(sq2[0][1] , f*4);
            TS_ASSERT_EQUALS(sq2[0][2] , b*4);
            TS_ASSERT_EQUALS(sq2[1][0] , a*4);
            TS_ASSERT_EQUALS(sq2[1][1] , e*4);
            TS_ASSERT_EQUALS(sq2[1][2] , f*4); //MATRIX8 FAILS
            TS_ASSERT_EQUALS(sq2[2][0] , b*4);
            TS_ASSERT_EQUALS(sq2[2][1] , c*4);
            TS_ASSERT_EQUALS(sq2[2][2] , e*4);

            TS_ASSERT_EQUALS(rect1[0][0] , a*5);
            TS_ASSERT_EQUALS(rect1[0][1] , b*5);
            TS_ASSERT_EQUALS(rect1[0][2] , a*5);
            TS_ASSERT_EQUALS(rect1[1][0] , d*5);
            TS_ASSERT_EQUALS(rect1[1][1] , f*5);
            TS_ASSERT_EQUALS(rect1[1][2] , e*5); //MATRIX8 FAILS

            TS_ASSERT_EQUALS(slim2[0][0] , c*2);
            TS_ASSERT_EQUALS(slim2[1][0] , d*2);
            TS_ASSERT_EQUALS(slim2[2][0] , e*2);
            TS_ASSERT_EQUALS(slim2[3][0] , f*2);


            rect1 = rect1*(-5);
            sq2 = sq2*(-4);
            slim2 = slim2*(-2);

            TS_ASSERT_EQUALS(sq2[0][0] , e*4*(-4));
            TS_ASSERT_EQUALS(sq2[0][1] , f*4*(-4));
            TS_ASSERT_EQUALS(sq2[0][2] , b*4*(-4));
            TS_ASSERT_EQUALS(sq2[1][0] , a*4*(-4));
            TS_ASSERT_EQUALS(sq2[1][1] , e*4*(-4));
            TS_ASSERT_EQUALS(sq2[1][2] , f*4*(-4)); //MATRIX8 FAILS
            TS_ASSERT_EQUALS(sq2[2][0] , b*4*(-4));
            TS_ASSERT_EQUALS(sq2[2][1] , c*4*(-4));
            TS_ASSERT_EQUALS(sq2[2][2] , e*4*(-4));

            TS_ASSERT_EQUALS(rect1[0][0] , a*5*(-5));
            TS_ASSERT_EQUALS(rect1[0][1] , b*5*(-5));
            TS_ASSERT_EQUALS(rect1[0][2] , a*5*(-5));
            TS_ASSERT_EQUALS(rect1[1][0] , d*5*(-5));
            TS_ASSERT_EQUALS(rect1[1][1] , f*5*(-5));
            TS_ASSERT_EQUALS(rect1[1][2] , e*5*(-5)); //MATRIX8 FAILS

            TS_ASSERT_EQUALS(slim2[0][0] , c*2*(-2));
            TS_ASSERT_EQUALS(slim2[1][0] , d*2*(-2));
            TS_ASSERT_EQUALS(slim2[2][0] , e*2*(-2));
            TS_ASSERT_EQUALS(slim2[3][0] , f*2*(-2));


    }

    void test_matrxAddScl(){
        Matrix dummy = rect1+5;
        Matrix dummy2= rect1+(-2);

        TS_ASSERT_EQUALS(dummy[0][0] , a+5);
        TS_ASSERT_EQUALS(dummy[0][1] , b+5);
        TS_ASSERT_EQUALS(dummy[0][2] , a+5);
        TS_ASSERT_EQUALS(dummy[1][0] , d+5);
        TS_ASSERT_EQUALS(dummy[1][1] , f+5);
        TS_ASSERT_EQUALS(dummy[1][2] , e+5);
        TS_ASSERT_EQUALS(dummy2[0][0] , a-2);
        TS_ASSERT_EQUALS(dummy2[0][1] , b-2);
        TS_ASSERT_EQUALS(dummy2[0][2] , a-2);
        TS_ASSERT_EQUALS(dummy2[1][0] , d-2);
        TS_ASSERT_EQUALS(dummy2[1][1] , f-2);
        TS_ASSERT_EQUALS(dummy2[1][2] , e-2);
    }




    void test_negMatrix(){
        Matrix dummy = -rect2;
        TS_ASSERT_EQUALS(dummy[0][0] , -a);
        TS_ASSERT_EQUALS(dummy[0][1] , -b);
        TS_ASSERT_EQUALS(dummy[0][2] , -c);
        TS_ASSERT_EQUALS(dummy[0][3] , -d);
        TS_ASSERT_EQUALS(dummy[1][0] , -e);
        TS_ASSERT_EQUALS(dummy[1][1] , -f);
        TS_ASSERT_EQUALS(dummy[1][2] , -a);
        TS_ASSERT_EQUALS(dummy[1][3] , -b);
        TS_ASSERT_EQUALS(dummy[2][0] , -e);
        TS_ASSERT_EQUALS(dummy[2][1] , -c);
        TS_ASSERT_EQUALS(dummy[2][2] , -a);
        TS_ASSERT_EQUALS(dummy[2][3] , -f);
    }



    void test_accessBracket(){
        const Matrix conMtx = rect1;
        TS_ASSERT_EQUALS(conMtx[0][0] , a);
        TS_ASSERT_EQUALS(conMtx[0][1] , b);
        TS_ASSERT_EQUALS(conMtx[0][2] , a);
        TS_ASSERT_EQUALS(conMtx[1][0] , d);
        TS_ASSERT_EQUALS(conMtx[1][1] , f);
        TS_ASSERT_EQUALS(conMtx[1][2] , e);
        Matrix temp(1,2);
        std::istringstream(" [ 1 -2 ] ") >> temp;
        temp = temp*conMtx;
        TS_ASSERT_EQUALS(temp[0][0] , a -2*d);
        TS_ASSERT_EQUALS(temp[0][1] , b -2*f);
        TS_ASSERT_EQUALS(temp[0][2] , a -2*e);

        TS_ASSERT_EQUALS( (temp[0][0])=50000 , 50000);
        TS_ASSERT_EQUALS( (temp[0][1])=70000 , 70000);
        TS_ASSERT_EQUALS( (temp[0][2])=-20000 , -20000);
    }



    void test_size(){
        TS_ASSERT_EQUALS(rect1.rows(),2);
        TS_ASSERT_EQUALS(rect1.cols(),3);
        rect1 = rect1+1;
        TS_ASSERT_EQUALS(rect1.rows(),2);
        TS_ASSERT_EQUALS(rect1.cols(),3);
        rect1 = sq1*rect1;
        TS_ASSERT_EQUALS(rect1.rows(),2);
        TS_ASSERT_EQUALS(rect1.cols(),3);
        rect1 = rect1*2;
        TS_ASSERT_EQUALS(rect1.rows(),2);
        TS_ASSERT_EQUALS(rect1.cols(),3);


        TS_ASSERT_EQUALS(rect2.rows(),3);
        TS_ASSERT_EQUALS(rect2.cols(),4);
        rect2 = rect2+2;
        TS_ASSERT_EQUALS(rect2.rows(),3);
        TS_ASSERT_EQUALS(rect2.cols(),4);
        rect2 = rect2*(-2);
        TS_ASSERT_EQUALS(rect2.rows(),3);
        TS_ASSERT_EQUALS(rect2.cols(),4);




        TS_ASSERT_EQUALS(slim1.rows(),1);
        TS_ASSERT_EQUALS(slim1.cols(),3);

        TS_ASSERT_EQUALS(slim2.rows(),4);
        TS_ASSERT_EQUALS(slim2.cols(),1);

        TS_ASSERT_EQUALS(sq1.rows(),2);
        TS_ASSERT_EQUALS(sq1.cols(),2);

        TS_ASSERT_EQUALS(sq2.rows(),3);
        TS_ASSERT_EQUALS(sq2.cols(),3);



    }


};