#include "../UtilSet.h"
#include <iostream>

int main() {
	for(int i = 0; i < 100; i++) {
		uint64_t idVal = UtilSet::generateUUID();
		std::cout << idVal << std::endl;
	}
	return 0;	
}
