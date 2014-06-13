#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	std::cout << argc << " " << argv[0] << std::endl;

	std::unique_ptr<int> p(new int);
	return 0;
}
