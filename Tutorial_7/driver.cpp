#include <iostream>
#include <string>
#include <vector>
#include <cmath>


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
// virtual enables late binding
	virtual float getArea() =0;

	virtual std::string getType() const = 0;
};

class Circle : public Shape{
	public:
	Circle(float radius) : Shape(1){
		properties[0] = radius;
	}

	float getArea(){
		return 3.141596 * std::pow(properties[0], 2);
	}

	std::string getType() const override{
		return "CIRCLE";
	}

};

class Square : public Shape{
	public:
	Square(float width, float height) : Shape(2){
		properties[0] = width;
		properties[1] = height;
	}

	std::string getType() const override{
		return "SQUARE";
	}

	float getArea() override{
		return properties[0] * properties[1];
	}
};

int main(int argc, char const *argv[])
{
	
	std::vector<Shape *> shapes;
	shapes.push_back(new Square(10,5));
	shapes.push_back(new Circle(1));

	for (Shape* s : shapes){
		std::cout << s->getType() << std::endl;
		std::cout << "Area: " << s->getArea() << std::endl;
		delete s;
	}
	/*
	Circle c(1.0);
	std::cout << "The circle has an area of " << c.getArea() << std::endl;
	std::cout << "And a radius of " << c.getRadius() << std::endl;
	std::cout << "The address of the properties attribute is " << c.getProperties() << std::endl;
	*/	
	return 0;
}