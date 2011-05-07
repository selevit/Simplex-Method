#include <iostream>

class Basis:public SourceData {
	public:
		void pr()
		{
			SourceData * test = new SourceData;
			std::cout << std::endl;
			std::cout <<  test -> numOfSourceVars << std::endl;
			std::cout << std::endl;
		}
	private:
		SourceData * inputData;
		double ** simplexTable;
};
