// copyright, Patrick Marais
// Department of Computer Science
// University of Cape Town
// (c) 2025

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "PGMimage.h"

using namespace std;

int main(int argc, char* argv[])
{
    // check command line args: note a basic check - should be more robust, assumes all args are correct

    if (argc != 4)
    {
        cerr << "Found " << argc - 1 << " arguments; expected 3\n";
        return 1;
    }

    // grid size
    int boardSize = atoi(argv[1]);

    // input image and output image names
    string inImage = argv[2];
    string outImage  = argv[3];

    cout << "Parameters:\n";
    cout << " - board size: " << boardSize << endl;
    cout << " - input image: " << inImage << endl;
    cout << " - output image: " << outImage << endl;

    // read in initial image.

    PGMimage image; 
    
    // note - the destructor will remove  the internal storage on heap when this variable leaves scope at end of main. DO NOT DELETE THE POINTER TO IMAGE STORAGE 
    // if needed, make a copy

    image.read(inImage);

    // work out tiles size
    int imageWidth, imageHeight, tileWd, tileHt;

    image.getDims(imageWidth, imageHeight);

    tileWd = int(float(imageWidth) / boardSize);
    tileHt = int(float(imageHeight) / boardSize);

    // check if  you need correct image size before actual split.
    
    
    image.write(outImage);
    // do stuff....
    // an array to store the subimages
    int tiles = boardSize * boardSize;

    PGMimage* subImages = new PGMimage[tiles]{};
    
    // divide up the image buffer into subimages buffer
    for (int i = 0; i < tiles; i ++){
	unsigned char * tile_buffer = new unsigned char[tileWd * tileHt];
    	for (int x = 0; x < tileWd; x++){
		for (int y = 0; y < tileHt; y++){
			tile_buffer[x* tileHt + y] =image.getBuffer()[i * tileWd * tileHt + x * tileHt + y];	
		}// end for y
	}//end for x
	subImages[i].setImageData(tile_buffer, tileWd, tileHt);	
    }//end for i
    // test subImage 
    
    // randomly shuffle tiles
    subImages[7].write("Test_sub.pgm");
    std::random_shuffle(subImages, subImages + tiles);
    
    // test shuffled
    subImages[7].write("Test_sub_shuffled.pgm");

    // combine shuffled files

    unsigned char * combinedBuffer = new unsigned char[imageWidth * imageHeight];
    for (int i = 0 ; i < tiles ; i++){
	const unsigned char * tileBuffer = subImages[i].getBuffer();
    	for (int x=0; x < tileWd; x++){
		for (int y = 0; y<tileHt ; y++){
			combinedBuffer[i * tileWd * tileHt + x * tileHt + y] = tileBuffer[x*tileHt +y];
		}
	}
    }

   PGMimage outputImage;
   outputImage.setImageData(combinedBuffer, imageWidth, imageHeight);
   outputImage.write(outImage);

   return 0;
}
