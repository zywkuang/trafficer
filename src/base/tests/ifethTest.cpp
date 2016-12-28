#include "../UtilSet.h"
#include <iostream>

int main() {
	std::string ifaddr = UtilSet::getHostAddress();
	std::cout << ifaddr << std::endl;
	return 0;
}
