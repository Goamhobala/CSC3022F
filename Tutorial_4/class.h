#ifndef __PIECE__
#define __PIECE__

namespace TUTORIAL4{
	

	class Piece{
		// local vars
		int row, col;
		char *id;
		
		public:
		Piece(); //Default constructor
		Piece(const int row, const int col, const char id); // Custom Constructor
		~Piece();	//Destructor

		Piece(const Piece& p); // copy constructor
		Piece(Piece && p); // Move constructor
		
		Piece& operator=(const Piece& rhs); // Copy assignment operator
		Piece& operator-(Piece&& rhs); // Move assignment operator


	};
}
//endif
