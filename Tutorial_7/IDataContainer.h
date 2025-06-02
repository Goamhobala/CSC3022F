#ifndef __DATACONTAINER__
#define __DATACONTAINER__

#include <string>

class IDataContainer
{
    protected:
	std::string id;
	int quantity;

    public:
	IDataContainer(std::string id) : id(id), quantity(0) {}

	std::string getID(){ return id;}
	int getQuantity() {return quantity;}

	bool modifyQuantity(int amount)
	{
		quantity += amount;
		bool isEmpty = quantity < 0; 
		quantity =  isEmpty ? 0 : quantity;

		return isEmpty;
	}
};

#endif	