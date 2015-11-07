#include "matrix.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>
int main () {
    Matrix n;
    assert(n.cols()==0);
    assert(n.rows()==0);


    std::cout << "*****\n SQUARE MATRIX TESTS \n********\n";
    std::cout << "Contian correct element via [][]"<<"\n";
    Matrix m (2, 2);
    int a = 4;
    int b = 9;
    int c = -2;
    int d = 3;
    m[0][0] = a;
    m[0][1] = b;
    m[1][0] = c;
    m[1][1] = d;
    Matrix base = m;
    assert(a==m[0][0]);
    assert(b==m[0][1]);
    assert(c==m[1][0]);
    assert(d==m[1][1]);
    std::cout << "verifing copy\n";
    assert(a==base[0][0]);
    assert(b==base[0][1]);
    assert(c==base[1][0]);
    assert(d==base[1][1]);



    std::cout << "scalar mtrx mult\n"; //Matrix 3 fails afterwards:
    m = m*2;
    assert(2*a==m[0][0]);
    assert(2*b==m[0][1]);
    assert(2*c==m[1][0]);
    assert(2*d==m[1][1]);
    //Undef m = m*2;
    std::cout << "testing addition\n"; //Matrix 1 fails here
    m = m+m;
    assert(4*a==m[0][0]);
    assert(4*b==m[0][1]);
    assert(4*c==m[1][0]);
    assert(4*d==m[1][1]);
    std::cout << "testing subtraction\n";
    m = m-base;
    assert(3*a==m[0][0]);
    assert(3*b==m[0][1]);
    assert(3*c==m[1][0]);
    assert(3*d==m[1][1]);
    std::cout << "elementwise add \n";
    m = m+7;
    assert(3*a+7==m[0][0]);
    assert(3*b+7==m[0][1]);
    assert(3*c+7==m[1][0]);
    assert(3*d+7==m[1][1]);

    std::cout << "elementwise add neg\n";
    m = m+(-2);
    assert(3*a+5==m[0][0]);
    assert(3*b+5==m[0][1]);
    assert(3*c+5==m[1][0]);
    assert(3*d+5==m[1][1]);

    std::cout << "negativeMatrix\n";
    m = -m;
    assert(-(3*a+5)==m[0][0]);
    assert(-(3*b+5)==m[0][1]);
    assert(-(3*c+5)==m[1][0]); //matrix 6 fail
    assert(-(3*d+5)==m[1][1]);

    std::cout << "negative multiplication sclar\n";
    m = m*-1;
    assert(3*a+5==m[0][0]);
    assert(3*b+5==m[0][1]);
    assert(3*c+5==m[1][0]);
    assert(3*d+5==m[1][1]);

    m = std::move(base);
    std::cout << "Testing move assign\n";
    assert(a==m[0][0]);
    assert(b==m[0][1]);
    assert(c==m[1][0]);
    assert(d==m[1][1]);

    std::cout << "testing matrix subtraction\n";
    Matrix mtrsib(m-(m+1));
    assert(-1==mtrsib[0][0]);
    assert(-1==mtrsib[0][1]);
    assert(-1==mtrsib[1][0]);
    assert(-1==mtrsib[1][1]);
    assert(mtrsib.rows()==2);
    assert(mtrsib.cols()==2);

    std::cout << "testing matrix addition \n";
    Matrix mtradd(m+mtrsib);
    assert(mtradd[0][0] = a-1);
    assert(mtradd[0][1] = b-1);
    assert(mtradd[1][0] = c-1);
    assert(mtradd[1][1] = d-1);


    std::cout << "move construct\n";
    Matrix moveTest = std::move(base);
    assert(a==moveTest[0][0]);
    assert(b==moveTest[0][1]);
    assert(c==moveTest[1][0]);
    assert(d==moveTest[1][1]);

    std::cout << "original unaffected\n";
    Matrix mulTest = moveTest*m;
    Matrix mulTes2 = m*base;
    assert(a==moveTest[0][0]);
    assert(b==moveTest[0][1]);
    assert(c==moveTest[1][0]);
    assert(d==moveTest[1][1]);
    assert(a==m[0][0]);
    assert(b==m[0][1]);
    assert(c==m[1][0]);
    assert(d==m[1][1]);
    assert(a==base[0][0]);
    assert(b==base[0][1]);
    assert(c==base[1][0]);
    assert(d==base[1][1]);

    std::cout << "veryfing square\n"; //multiplication error matrix 5
    assert((a*a+b*c) == mulTest[0][0]);
    assert((a*b+b*d) == mulTest[0][1]);
    assert((c*a+d*c) ==mulTest[1][0]);
    assert((c*b+d*d) == mulTest[1][1]);
    assert((a*a+b*c)== mulTes2[0][0]);
    assert((a*b+b*d) == mulTes2[0][1]);
    assert((c*a+d*c)  ==mulTes2[1][0]);
    assert((c*b+d*d) == mulTes2[1][1]);
    assert(2 == mulTes2.cols());
    assert(2 == mulTes2.rows());
    assert(2 == mulTest.cols());
    assert(2 == mulTest.rows());
    assert(2 == m.cols());
    assert(2 == m.rows());
    assert(2 == base.cols());
    assert(2 == base.rows());
    assert(2 == moveTest.cols());
    assert(2 == moveTest.rows());

    std::ostringstream outStream, out2Stream;
    outStream << m;
    out2Stream <<moveTest;
    std::cout << "outstream test\n";
    assert( out2Stream.str() == outStream.str());

    out2Stream.str("");
    out2Stream.clear();
    outStream.str("");
    outStream.clear();
    outStream<<mulTes2;
    out2Stream<<mulTest;
    assert(out2Stream.str() == outStream.str());


    std::cout << "chained events\n";
    Matrix res = m*m+m+m-m;
    assert(2==res[0][0]);
    assert(72==res[0][1]);
    assert(-16==res[1][0]);
    assert(-6==res[1][1]);

    Matrix res2 = m*m+m*m*(m+m)-m;
    assert(-274==res2[0][0]);
    assert(396==res2[0][1]);
    assert(-88==res2[1][0]);
    assert(-318==res2[1][1]);
    res2[0][1] = 20;
    assert(20==res2[0][1]);

    assert(res.cols()==2);
    assert(res.rows()==2);
    assert(res2.cols()==2);
    assert(res2.rows()==2);



    std::cout << "******\n RECTANGULAR \n*******\n";
    std::cout << "string input \n";
    Matrix rect0 = Matrix(2,3);
    Matrix rect1 = Matrix(3,4);
    std::istringstream (" [ 7 5 -3 ; -1 2 -3 ] ") >> rect0;
    assert(7 == rect0[0][0]);
    assert(5 == rect0[0][1]);
    assert(-3 == rect0[0][2]); //matrix4 fails here
    assert(-1 == rect0[1][0]);
    assert(2 == rect0[1][1]);
    assert(-3 == rect0[1][2]);

    std::istringstream (" [ 1 3 5 -2 ; -1 4 -6 5 ; 7 2 -8 9 ] ") >> rect1;
    assert(1 == rect1[0][0]);
    assert(3 == rect1[0][1]);
    assert(5 == rect1[0][2]);
    assert(-2 == rect1[0][3]);
    assert(-1 == rect1[1][0]);
    assert(4 == rect1[1][1]);
    assert(-6 == rect1[1][2]);
    assert(5 == rect1[1][3]);
    assert(7 == rect1[2][0]);
    assert(2 == rect1[2][1]);
    assert(-8 == rect1[2][2]);
    assert(9 == rect1[2][3]);


    Matrix slim1 = Matrix(1,3);
    std::istringstream (" [ 7 5 -3 ] ") >> slim1;
    Matrix slim2 = Matrix(4,1);
    std::istringstream (" [ 1 ; 2 ; -4 ; 5 ] ") >> slim2;
    Matrix sclValue = slim1*rect1*slim2;
    assert(sclValue[0][0]==-145);
    assert(sclValue.cols()==1);
    assert(sclValue.rows()==1);


    Matrix rect3;
    rect3 = rect0*rect1;

    std::ostringstream outTest;
    outTest << rect3;
    std::cout << "checking stringoutput corectness\n";
    assert(outTest.str() == "[\n     -19     35     29    -16 ;\n     -24     -1      7    -15 ]\n");
    assert(rect3[0][0] == -19);
    assert(rect3[0][1] == 35);
    assert(rect3[0][2] == 29);
    assert(rect3[0][3] == -16);
    assert(rect3[1][0] == -24);
    assert(rect3[1][1] == -1);
    assert(rect3[1][2] ==  7);
    assert(rect3[1][3] == -15);



    std::cout << "Different conversions\n";
    std::istringstream(" [ 1 2 ; -3 -9 ] ") >> rect3;
    outTest.str("");
    outTest.clear();
    outTest << rect3;
    assert(outTest.str() == "[\n       1      2 ;\n      -3     -9 ]\n");


    std::cout << "const test\n";
    const Matrix a_mtrx = rect1;
    assert(1 == a_mtrx[0][0]);
    assert(3 == a_mtrx[0][1]);
    assert(5 == a_mtrx[0][2]);
    assert(-2 == a_mtrx[0][3]);
    assert(-1 == a_mtrx[1][0]);
    assert(4 == a_mtrx[1][1]);
    assert(-6 == a_mtrx[1][2]);
    assert(5 == a_mtrx[1][3]);
    assert(7 == a_mtrx[2][0]);
    assert(2 == a_mtrx[2][1]);
    assert(-8 == a_mtrx[2][2]);
    assert(9 == a_mtrx[2][3]);


    std::cout << "sizeTest\n";
    Matrix sizeTest(rect0);
    assert(sizeTest.rows() == 2);
    assert(sizeTest.cols() == 3);
    sizeTest = rect1;
    assert(sizeTest.rows() == 3);
    assert(sizeTest.cols() == 4);
    sizeTest = slim1;
    assert(sizeTest.rows() == 1);
    assert(sizeTest.cols() == 3);
    sizeTest = slim2;
    assert(sizeTest.rows() == 4);
    assert(sizeTest.cols() == 1);

    std::cout << "selfassign \n";
    sizeTest=sizeTest;
    assert(sizeTest.rows() == 4);
    assert(sizeTest.cols() == 1);
    assert(sizeTest[0][0] == 1);
    assert(sizeTest[1][0] == 2);
    assert(sizeTest[2][0] == -4);
    assert(sizeTest[3][0] == 5);
    sizeTest = std::move(sizeTest);
    assert(sizeTest.rows() == 4);
    assert(sizeTest.cols() == 1);
    assert(sizeTest[0][0] == 1);
    assert(sizeTest[1][0] == 2);
    assert(sizeTest[2][0] == -4);
    assert(sizeTest[3][0] == 5);



    Matrix rect9 = Matrix(3,2);
    rect9[2][1] = -99999;
    assert(rect9[2][1]==-99999);
    rect9[2][1] = -2;
    assert(rect9[2][1]==-2);

    Matrix rect8 = Matrix(0,19);
    assert(rect8.cols() == 19);
    assert(rect8.rows() == 0);
    rect8 = Matrix(20,0);
    assert(rect8.cols() == 0);
    assert(rect8.rows() == 20);



    Matrix innerTest(1,1);
    innerTest[0][0] = 5;
    innerTest[0][1] = 1;
    assert(innerTest.cols() == 1);
    assert(innerTest.rows() == 1);


    //2,7 and 8 can assign value outside of COLUMN range
    //rect1[0][10] = 5;
    //std::cout << rect1[0][10]<<"\n";
    //addition of two difference sizes matrix works :/;

    //should segfault
    //Matrix derp = rect1*rect0;
    //a_mtrx[1] = 5;
    /* but works...
    Matrix derp = rect0+rect1;
    std::cout << rect0<<"\n";
    std::cout << rect1<<"\n";
    std::cout << derp << "\n";
    */

    //9 definetly leaking


    //2 7 8 unkown error
}
