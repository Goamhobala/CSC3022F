#define CATCH_CONFIG_MAIN
#include "catch.hpp"

unsigned int factorial( unsigned int x )
{
	return x > 1 ? factorial(x-1)*x : 1;
}

TEST_CASE ("Factorial Unit Test"){

	REQUIRE(factorial(0) == 1);
	REQUIRE(factorial(1)==1);
	REQUIRE(factorial(2)==2);
	REQUIRE(factorial(3)==6);
	REQUIRE(factorial(10)==3628800);
}
