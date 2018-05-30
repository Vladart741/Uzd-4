#include "Vector.h"
#include <vector>
#include <chrono>

int main()
{
	// Prad�ti v1 u�pildymo laiko matavim�
	std::vector<int> v1;
	for (int j = 10; j < 1000000000; j = j * 10)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 1; i <= j; ++i)
			v1.push_back(i);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Programos vykdymo laikas su std::vector su " << j << " elementu: " << elapsed.count() << " s\n";
		v1.clear();
	}
	std::cout << std::endl;
	// Baigti v1 u�pildymo laiko matavim�

	// Prad�ti v2 u�pildymo laiko matavim�
	Vector<int> v2;
	for (int j = 10; j < 1000000000; j = j * 10)
	{
		auto start1 = std::chrono::high_resolution_clock::now();
		for (int i = 1; i <= j; ++i)
			v2.push_back(i);
		
		auto finish1 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed1 = finish1 - start1;
		std::cout << "Programos vykdymo laikas su Vector su "<<j<<" elementu: " << elapsed1.count() << " s\n";
		v2.clear();
	}
	// Baigti v2 u�pildymo laiko matavim�
	
	system("pause");
	return 0;
}