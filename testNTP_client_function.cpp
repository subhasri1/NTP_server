
#include <cppunit/TestCase.h> 

#include <cppunit/TestCaller.h> 

#include <cppunit/TestSuite.h> 

#include <cppunit/ui/text/TestRunner.h> 
#include "NTP_client_header.h"

using namespace CppUnit; 

#include <iostream> 

using namespace std; 

#include "testNTP_client_function.h"

 

void NTP_client_functionTestCase::testnewUserDataInOneString()

{	 
newUser obj("124536","Aman","aman123","aman1234","aman@gmail.com","aman123");
string s="2aman123,aman1234,aman@gmail.com,124536,Aman";
string s1="2aman123,aman1234,aman@gmail.com,124536,Aman";
CPPUNIT_ASSERT(s==obj.newUserDataInOneString()); 
CPPUNIT_ASSERT(s1==obj.newUserDataInOneString()); 
} 

 
//creating suite of tests for various functionalities 

Test* NTP_client_functionTestCase::suite() 

{ 

TestSuite *testsuite = new TestSuite("NTP_client_functionTestCase");	 

testsuite->addTest(new TestCaller< NTP_client_functionTestCase>("testnewUserDataInOneString",& NTP_client_functionTestCase ::testnewUserDataInOneString)); 


return testsuite; 

} 

int main(int argc, char *argv[]) 

{ 

if (argc!=2) 

{ 

cout << "usage error " << endl; 

cout << "tester <name of the class to be tested> " << endl; 

exit(1); 

} 

 

CppUnit::TextUi::TestRunner testrunner; 

testrunner.addTest(NTP_client_functionTestCase::suite()); 

testrunner.run(); 

} 
