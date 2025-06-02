#include<iostream>
#include<memory>
int main(void){
    int i_arr[5] = {2, 3, 45,6, 6};
    std::cout << i_arr << std::endl;
    std::cout << i_arr[0] << std::endl;
    std::cout << * i_arr << std::endl;

    char c_arr[4] = {'a', 'b', '\0', 'c'};
    std::cout << c_arr << std::endl;
    std::cout << * c_arr << std::endl;
    std::cout << static_cast<void *>(c_arr) << std::endl;

	std::unique_ptr<int[]> C(new int[10]);
	std::cout << C[5];
}
