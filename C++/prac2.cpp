#include <iostream>

int* subImage(int ** ptr, int h_start, int h_end, int v_start, int v_end){
	
	int v_diff = v_end - v_start;
	int h_diff = h_end - h_start;
	int * subPtr = new int[h_diff * v_diff];

	for (int x = h_start; x < h_end; x++){
		for (int y = v_start; y < v_end; y++){
			subPtr[(x-h_start) * v_diff + (y-v_start)] = ptr[x][y];
		}
	}
	return subPtr;
}

int main(void){
	int width; int height;
	width = 40;
	height = 40;

	int ** pixels = new int*[width];
	for (int i = 0; i<width; i++){
		pixels[i] = new int[height];
		for (int j = 0 ; j < height; j++){
			pixels[i][j]= i * height + j;
			std::cout << pixels[i][j]<<std::endl;
		}
	}

	int divide = 3;
	int **subImages = new int *[divide * divide]; //an array of pointers to sub images

	int subWidth = width/divide;
	int subHeight = height/divide;


	for (int i =0 ; i < divide ; i++){
		for (int j = 0; j < divide ; j++){
			int h_start = subWidth * i;
			int v_start = subHeight * j;
			subImages[i * divide + j] = subImage(pixels, h_start, h_start + subWidth, v_start, v_start + subHeight);

		}
	}

	// Checking
//	std::cout << **subImages[0][0] << std::endl;
//	std::cout << **subImages[0][1] << std::endl;
//	std::cout << **subImages[1][0] << std::endl;
//	std::cout << **subImages[2][2] << std::endl;
	

	// To change everything in a subimage to 1
	int oneRow = 1; int oneCol = 2;
	int * oneSubImage = subImages[5];
	for (int x = 0; x < subWidth ; x++){
		for (int y=0 ; y < subHeight ; y++){
			oneSubImage[x * subHeight + y]=1;
		}	
	}

	std::cout << *subImages[5] << std::endl;
	std::cout << oneSubImage[12] << std::endl;
	std::cout << oneSubImage[144]<< std::endl;
	



	for (int i = 0; i < divide; i++){
		delete[] subImages[i];
	}

	for (int i = 0; i < width; i++){
		delete[] pixels[i];
	}


	delete[] pixels;
	delete[] subImages;

	return 0;
}





