#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

int main(int argc, char* argv[]){
    std::string fileName;
    std::vector<std::string> menu_items;
 //   std:ostringstream outFileItems;    
    if(argc == 1){
        fileName = "./menu_1.txt";
    }
    else {
        fileName = argv[1];
    }


    std::ifstream inputFile(fileName);
    std::string line;

    if (!inputFile){
        std::cout << "File not found" << std::endl;
    }

    while(std::getline(inputFile,line)){
        menu_items.push_back(line);
        //for (char c : line){
           // outInputItems << "\t";
           // while(c != 'R'){
             //   outInputItems << c;
           // }

        
    }

    inputFile.close();
    // output menu size
    std::cout << menu_items.size() << " Items on the menu" << std::endl;
    
    //output menu items line by line
    


}
