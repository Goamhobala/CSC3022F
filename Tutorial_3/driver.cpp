#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
int main(int argc, char * argv[]){
	
	//int a = 10;
	//float b = 15.5;

	//std::cout << "The address of variable 'a' is: " << &a << std::endl;
	//std::cout << "The address of varialbe 'b' is: " << &b << std::endl;
	
	std::string fileName;
	int rowsNum; int colsNum;
	

	// Default behaviour
	if (argc == 1){
		fileName = "2D.txt";
		rowsNum = 10;
		colsNum = 1;
	}
	// 1D array
	else if (argc == 3){
		fileName = argv[1];
		rowsNum = std::stoi(argv[2]);
		colsNum = 1;
	}
	// 2D array
	else if (argc == 4)
	{	
		fileName = argv[1];
		rowsNum = std::stoi(argv[2]) ;
		colsNum = std::stoi(argv[3]);		
	}

	std::ifstream in (fileName);
	
	if (!in){
		std::cout << "Can't open file" << std::endl;
		return 1;
	}
	
	int *values = new int [rowsNum];
	std::string rowBuffer;
	int row = 0;
	
	while (std::getline(in >> std::ws, rowBuffer)){
		int col = 0;
		for (char c : rowBuffer){
			if (c != ' '){
			// subtract the ascii value of 0;
			values[row * colsNum + col] = c - 48;
			col++;
			}

		}
		row++;
	}

	int total = 0;
	// sum up values
	for (int i = 0; i < rowsNum; i++ ){
		int rowsTotal = 0;
		for (int j = 0; j< colsNum ; j++){
			std::cout << values[i * colsNum + j] << std::endl;
			rowsTotal += values[i * colsNum + j];
		}
		total += rowsTotal/colsNum;
	}
	int rowAverage = total/rowsNum;
	
	std::cout << "Row average: " << rowAverage << std::endl;

	return 0;
}
