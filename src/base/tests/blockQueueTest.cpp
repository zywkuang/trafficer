#include <iostream>
#include <string>
#include "../BoundedBlockingQueue.h"

int main() {
	BoundedBlockingQueue<std::string> strQueue(64);
	std::string str1 = "hello";
	std::string str2 = "world";	

	strQueue.offer(str1);
	strQueue.offer(str2);

	std::cout << strQueue.poll() << std::endl;
	std::cout << strQueue.poll() << std::endl;
	return 0;
}
