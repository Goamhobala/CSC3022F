#include <iostream>
#include <string>
#include<vector>

class Shape
{

protected:
	float * properties;
	int length;

public:
	Shape(int prop) // Custom Constructor
	{
		length = prop;
		properties = new float[prop];
	}

	Shape(const Shape & other) // Copy Constructor
	{
		length = other.length;


		properties = new float[length];
		for (int i = 0; i < length; ++i)
		{
			properties[i] = other[i];
		}
	}

	Shape(Shape && other) // Move Constructor
	{
		length = other.length;
		properties = other.properties;
		other.properties = nullptr;
	}

	virtual ~Shape()
	{
		if(properties != nullptr)
			delete [] properties;
	}

	float operator[](int index) const
	{
		return properties[index];
	}
	
	float* getProperties() const
	{
		return properties;
	}

	virtual float getArea() const
	{
		return 0.0;
	}

	virtual std::string getType() const
	{
		return "SHAPE";
	}

};

class Square : public Shape{
	int width; int height;
	
	public:
	Square(int width, int height): width(width), height(height), Shape(2){
	}
	float getArea() const override{
		return width * height;
	}

	std::string getType() const override{
		return "SQUARE";
	}

};


int main(int argc, char const *argv[])
{
	std::vector<Shape*> shapes;
	shapes.push_back(new Shape(2));
	shapes.push_back(new Square(5, 3));
	for (Shape* s : shapes){
		std::cout << "The following is a " << s->getType() << " with an area " << s->getArea() << std::endl;
	}
	for (Shape* s : shapes){
		delete (s);
	}
	return 0;


}
