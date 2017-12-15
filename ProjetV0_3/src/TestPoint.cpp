#include "../cppunit/include/cppunit/TestCase.h"
#include "../cppunit/include/cppunit/TestFixture.h"
#include "../cppunit/include/cppunit/ui/text/TextTestRunner.h"
#include "../cppunit/include/cppunit/extensions/HelperMacros.h"
#include "../cppunit/include/cppunit/extensions/TestFactoryRegistry.h"
#include "../cppunit/include/cppunit/TestResult.h"
#include "../cppunit/include/cppunit/TestResultCollector.h"
#include "../cppunit/include/cppunit/TestRunner.h"
#include "../cppunit/include/cppunit/BriefTestProgressListener.h"
#include "../cppunit/include/cppunit/CompilerOutputter.h"
#include "../cppunit/include/cppunit/XmlOutputter.h"

#include "../include/Point.h"

class TestPoint : public CppUnit::TestCase{
	public :
		Point test = new Point();
		Point t2 = new Point(0.,1.,0.);
		
		void runTest()
		{
			float xtmp=5.;
			test.setX(xtmp);
			t2.setX(xtmp);
			CPPUNIT_ASSERT(test.x == xtmp && t2.x == xtmp);
		}
		
		
}
