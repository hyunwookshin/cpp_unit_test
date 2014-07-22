#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

/**********************************************
         _     _ __   _ _____ _______
         |     | | \  |   |      |
         |_____| |  \_| __|__    | (FOR C++)

 UNIT TESTING MODULE FOR OBJECT ORIENTED SOFTWaRE
 AUTHOR hyunwookjamesshin at gmail dot com
 FreeBSD License

***********************************************
About

    *this file is included in main
     and where you create a customized unit test suite
    *add unittest.cc that goes with this file
    *each test is a function that takes no
    input and returns void. One
    can call another function inside it

**********************************************/
//Levels of hiearchy
//     group :  groups using namespace multiple test suites together
//              and it contains all sample tests to be used by the test suites
//     suite :  each class within the group runs a sequence of sample tests
//     test  :  a sample test to be run (does not have to run at all, or can run
//              in two or more test suites)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>  //io_emulator using stringstream
#include <fstream>  //io_emulator using fstream
//-------------------------------------------------
//  @note (unittest.h) Change the namespace for Unit Testing Suite (optional)
//-------------------------------------------------

#define NAMESPACE my_name_space

//--------------------------------------------------
//  @note (unittest.h) OPTIONAL MACROS (see examples below for usage)
//--------------------------------------------------
#define VOID        static void
#define IS_UNITTEST public  NAMESPACE::UnitTestSuite
#define PUSH(x)     unittests.push_back(&x);

//-------------------------------------------------
// Do Not Change This Section (This is the short activation macro)
// You may change the names 'RUN_UNIT' or 'RUN_UNIT_S'
//-------------------------------------------------

# define RUN_UNIT(nspace,suitename,name) nspace::suitename name = nspace::suitename();\
name.execute_all();

# define RUN_UNIT_S(suitename,name) suitename name = suitename();\
name.execute_all();

//------------------------------------------------
//  @note (unittest.h) HOW TO RUN THE UNIT TESTS IN MAIN
//-------------------------------------------------
/*
// Option 1. Without Macro

#include "unittest.h"

int main () {
    NAMESPACEexample::ExampleSuite suite = NAMESPACEexample::ExampleSuite();
    suite.execute_all();
}

// Option 2. With Macro

int main () {
    RUN_UNIT(NAMESPACEexample,ExampleSuite,suite1);
}

// Option 3. No namespace

int main () {
    RUN_UNIT(ExampleSuite,suite1);
}

*/

//--------------------------------------------------
// DO NOT CHANGE BELOW
//--------------------------------------------------
typedef void (*UNITTEST)();

namespace NAMESPACE {
    class UnitTestSuite {
        protected:
            std::vector<UNITTEST> unittests;
        public:
            void add_unit(UNITTEST);
            void execute_all();
    };
}
//--------------------------------------------------
//  @note (unittest.h) IOSTREAM TESTING - USING STRINGSTREAM (DO NOT CHANGE)
//--------------------------------------------------
// This is for testing programs with stdin and stdout

// io_emulator injects string buffer into stdin (cin)
// and gets output as stringstream
// stream operator "<<" is used to inject/get stream
// To use cin_emulator, call interupt();
// and then call release(), to disable cin_emulator
// see examples below for details
namespace NAMESPACE {
    class io_emulator {
        std::stringstream is;
        std::stringstream os;
        std::streambuf* previous_i_buffer;
        std::streambuf* previous_o_buffer;
    public:
        void interrupt();
        void release();
        void refresh();
        void fread(std::string filename);
        friend io_emulator & operator<< (io_emulator &ce, std::string s);
        friend io_emulator & operator>> (io_emulator &ce, std::string &s);
    };
}
//--------------------------------------------------
// @note (unittest.h) IOSTREAM TESTING - USING FILES (DO NOT CHANGE)
//--------------------------------------------------
namespace NAMESPACE {
    class file_io_emulator {
        std::ifstream* inf;
        std::ofstream* outf;
        std::string inputfile;
        std::string outputfile;
        std::string reffile;        //reference file (optional)
        std::streambuf* previous_i_buffer;
        std::streambuf* previous_o_buffer;
        void interrupt();           // activate redirection

    public:
        // for checking I/O with reference file
        file_io_emulator(std::string inputfile,std::string outputfile,std::string reffile);
        // for simply writing to the output file
        file_io_emulator(std::string inputfile,std::string outputfile);
        file_io_emulator();
        void checkoutput();
        ~file_io_emulator();
        void release();           // restore cin/cout
    };
}
#endif
