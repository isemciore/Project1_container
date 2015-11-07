/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "matrix_cxxTest.cpp"

static matrix_cxxTest suite_matrix_cxxTest;

static CxxTest::List Tests_matrix_cxxTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_matrix_cxxTest( "matrix_cxxTest.cpp", 6, "matrix_cxxTest", suite_matrix_cxxTest, Tests_matrix_cxxTest );

static class TestDescription_matrix_cxxTest_test_MtrxCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_MtrxCopy() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 71, "test_MtrxCopy" ) {}
 void runTest() { suite_matrix_cxxTest.test_MtrxCopy(); }
} testDescription_matrix_cxxTest_test_MtrxCopy;

static class TestDescription_matrix_cxxTest_test_MtrxCopyAss : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_MtrxCopyAss() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 80, "test_MtrxCopyAss" ) {}
 void runTest() { suite_matrix_cxxTest.test_MtrxCopyAss(); }
} testDescription_matrix_cxxTest_test_MtrxCopyAss;

static class TestDescription_matrix_cxxTest_test_instreamAss : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_instreamAss() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 91, "test_instreamAss" ) {}
 void runTest() { suite_matrix_cxxTest.test_instreamAss(); }
} testDescription_matrix_cxxTest_test_instreamAss;

static class TestDescription_matrix_cxxTest_test_outStream : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_outStream() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 115, "test_outStream" ) {}
 void runTest() { suite_matrix_cxxTest.test_outStream(); }
} testDescription_matrix_cxxTest_test_outStream;

static class TestDescription_matrix_cxxTest_test_matAddmat : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_matAddmat() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 124, "test_matAddmat" ) {}
 void runTest() { suite_matrix_cxxTest.test_matAddmat(); }
} testDescription_matrix_cxxTest_test_matAddmat;

static class TestDescription_matrix_cxxTest_test_mattSubmat : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_mattSubmat() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 136, "test_mattSubmat" ) {}
 void runTest() { suite_matrix_cxxTest.test_mattSubmat(); }
} testDescription_matrix_cxxTest_test_mattSubmat;

static class TestDescription_matrix_cxxTest_test_mtrxMult : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_mtrxMult() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 148, "test_mtrxMult" ) {}
 void runTest() { suite_matrix_cxxTest.test_mtrxMult(); }
} testDescription_matrix_cxxTest_test_mtrxMult;

static class TestDescription_matrix_cxxTest_test_matrxSclMULT : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_matrxSclMULT() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 184, "test_matrxSclMULT" ) {}
 void runTest() { suite_matrix_cxxTest.test_matrxSclMULT(); }
} testDescription_matrix_cxxTest_test_matrxSclMULT;

static class TestDescription_matrix_cxxTest_test_matrxAddScl : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_matrxAddScl() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 241, "test_matrxAddScl" ) {}
 void runTest() { suite_matrix_cxxTest.test_matrxAddScl(); }
} testDescription_matrix_cxxTest_test_matrxAddScl;

static class TestDescription_matrix_cxxTest_test_negMatrix : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_negMatrix() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 262, "test_negMatrix" ) {}
 void runTest() { suite_matrix_cxxTest.test_negMatrix(); }
} testDescription_matrix_cxxTest_test_negMatrix;

static class TestDescription_matrix_cxxTest_test_accessBracket : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_accessBracket() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 280, "test_accessBracket" ) {}
 void runTest() { suite_matrix_cxxTest.test_accessBracket(); }
} testDescription_matrix_cxxTest_test_accessBracket;

static class TestDescription_matrix_cxxTest_test_size : public CxxTest::RealTestDescription {
public:
 TestDescription_matrix_cxxTest_test_size() : CxxTest::RealTestDescription( Tests_matrix_cxxTest, suiteDescription_matrix_cxxTest, 302, "test_size" ) {}
 void runTest() { suite_matrix_cxxTest.test_size(); }
} testDescription_matrix_cxxTest_test_size;

#include <cxxtest/Root.cpp>
