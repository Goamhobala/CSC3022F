#ifndef __MATRIX__
#define __MATRIX__


#include <iostream>

class Matrix
{
	int width, height;
	float** data;


	public:

	Matrix(); // Default Constructor
	Matrix(const int width, const int height, const float fill = 0.0); // Custom Constructor

	~Matrix() // Destructor

	Matrix(const Matrix & rhs); // Copy Constructor
	Matrix(Matrix && rhs); // Move Constructor


	Matrix & operator=(const Matrix & rhs); // Copy Assignment
	Matrix operator=(Matrix && rhs); // Move Assignment


	// Other Functions
	void reshape(const int i, const int j, const float fill = 0.0); // Resizes 'data' to be of size [i][j]. 
		//Any new positions in the Matrix should be filled with the value of 'fill' 


	float operator()(const int i, const int j) const; // This is the index get() function ie: float val = matrix(i,j);
	float& operator()(const int i, const int j); // This is the index set() function ie: matrix(i,j) = float_val;

	Matrix operator+(const float val) const;
	Matrix& operator+=(const float);

	Matrix operator+(const Matrix& rhs) const;
	Matrix& operator+=(const Matrix& rhs);

	Matrix operator*(const float val) const;
	Matrix& operator*=(const float val);

	Matrix operator*(const Matrix& rhs) const;
	Matrix& operator*=(const Matrix& rhs);

	Matrix operator-(const float val) const;
	Matrix& operator-=(const float val);

	Matrix operator-(const Matrix& rhs) const;
	Matrix& operator-=(const Matrix& rhs);

	Matrix operator!() const; // Inverse function
	Matrix operator-() const; // Negate function

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
	
	friend std::ostream& operator<<(std::ostream & s, Matrix & rhs);
	friend std::istream& operator>>(std::istream & s, Matrix & rhs);

	//////////////////////////////////////Some Useful Functions/////////////////////////////////////////////////////

	inline bool isSquare()
	{
		return this->width == this->height;
	}


	Matrix& identity() // Converts the current matrix object into an identity matrix. 
	//The function returns 'this` so you can use the function as follows Matrix id = Matrix(4,4).identity();
	{

		for (int i = 0; i < this->width; ++i)
		{
			for (int j = 0; j < this->height; ++j)
			{
				if (i == j) this->data[i][j] = 1;
				else this->data[i][j] = 0;
			}
		}

		return *this
	}

	void show() const // You don't need to unit test this function. It is just for debugging purposes
	{
		for (int i = 0; i < this->width; ++i)
		{
			for (int j = 0; j < this->height; ++j)
			{
				std::cout << this->data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

};

#endif