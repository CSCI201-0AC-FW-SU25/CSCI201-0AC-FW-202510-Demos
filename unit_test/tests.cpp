#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>
#include <cmath>
#include "../07_09_25/clock.h"

using namespace std;

TEST(twentyFourHrClockTest, equality)
{
	EXPECT_NO_THROW(twentyFourHrClock c1(13, 0, 0););
	EXPECT_ANY_THROW(twelveHrClock c5(21, 0, 0, partType::PM));
	EXPECT_THROW(twentyFourHrClock c4(44, 0, 0), invalid_hour);
	twelveHrClock c2(1, 0, 0, partType::PM);
	twentyFourHrClock c3(13, 3, 3);
	// EXPECT_TRUE(c1 == c2);
	// EXPECT_FALSE(c1 == c3);
	//  your test code goes here.
	//  see https://google.github.io/googletest/ for more information on writing a unit test
	//  assertions reference https://google.github.io/googletest/reference/assertions.html
}

// do not change any code below this comment
extern "C" int startTest(int x, char **y)
{
	// cout << "begin" << endl;
	// int x = 0;
	// char ** y = NULL;
	testing::InitGoogleTest(&x, y);
	// cout << "Init Complete"<< endl;
	int code = RUN_ALL_TESTS();
	// exit(code);
	return code;
}
// int i = startTest();
extern "C" int __wrap_main(int x, char **y)
{
	return startTest(x, y);
}