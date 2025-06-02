#include<string>
#include<sstream>
#include<iostream>

std::string print_letter_counts(int lc[], int size){
	std::ostringstream output;
	for (int i =0;  i < size; i++ ){
		if (lc[i] != 0){
			output << char(i + 97) << ":" << lc[i] << " "; 
		} 
	}
	return output.str();
}

int main(void){
	std::string input;
	int lineCount = 0;
	int wordCount = 0;
	int letter_counts[26]={};	
	//ascii for A=65, a=97
	int ascii;
	while(std::getline(std::cin >> std::ws, input)){
	  lineCount++;
	  bool word = false;
	  for(int i = 0; i < input.size(); i++){
		std::cout << input[i] << std::endl;
		if (input[i] == ' '){
		// new word
			i++;
			word=false;
		}

		ascii = int(input[i]);
		// convert to lower to be handled more easily
		if (ascii <= 90) ascii += 32;
				
		if (ascii <= 122 && ascii >= 97){
			if (!word){
                                word = true;
                                wordCount++;}

			letter_counts[ascii - 97]++;}
	}}
	std::cout << lineCount << " " << wordCount << " [ " << print_letter_counts(letter_counts, 26) << "]"<< std::endl;
	return 0;
}
