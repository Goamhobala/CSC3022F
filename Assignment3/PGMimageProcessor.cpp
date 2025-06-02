// PGMimageProcessor.cpp
#include "PGMimageProcessor.h"
#include <algorithm>
#include <memory>
#include <set>
#include <iostream>

using namespace yhxjin001;
using ConnectedComponentPtr = std::unique_ptr<ConnectedComponent>;

PGMimageProcessor::PGMimageProcessor() : width(0), height(0) {
    inputImagePtr = std::make_unique<PGMimage>();
    components = list<ConnectedComponentPtr>();
}

PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor & rhs) : width(rhs.width), height(rhs.height){
    inputImagePtr = std::make_unique<PGMimage>(*rhs.inputImagePtr);
    components = list<ConnectedComponentPtr>();
    for (const ConnectedComponentPtr & componentPtr  : rhs.components){
        components.push_back(std::make_unique<ConnectedComponent>(*componentPtr));
    }
}
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && rhs) : width(rhs.width), height(rhs.height){
    inputImagePtr = std::move(rhs.inputImagePtr);
    components = std::move(rhs.components);
    rhs.width = 0;
    rhs.height = 0;
}

// PGMimageProcessor::~PGMimageProcessor(){}
PGMimageProcessor & PGMimageProcessor::operator=(const PGMimageProcessor & rhs){
    if (this != &rhs) // prevent self-copying;
    {   
        // To re-initialise member variables
        if (inputImagePtr){
            inputImagePtr.reset();
        }
        components.clear();
        width = rhs.width;
        height = rhs.height;

        inputImagePtr = std::make_unique<PGMimage>(*rhs.inputImagePtr);
        for (const ConnectedComponentPtr & componentPtr  : rhs.components){
            components.push_back(std::make_unique<ConnectedComponent>(*componentPtr));
        }
    }
    return *this;
}
PGMimageProcessor & PGMimageProcessor::operator=(PGMimageProcessor && rhs){
    // To prevent moving to self
    if (this != &rhs){
        // Release held resources
        if (inputImagePtr){
            inputImagePtr.reset();
        }
        components.clear();
        width = rhs.width;
        height = rhs.height;
        inputImagePtr = std::move(rhs.inputImagePtr);
        components = std::move(rhs.components);
        rhs.width = 0;
        rhs.height = 0;
    }
    return *this;
}

void PGMimageProcessor::read(const string & fileName){
    (*inputImagePtr).read(fileName);
    width=inputImagePtr->getWidth();
    height = inputImagePtr->getHeight();
}

void PGMimageProcessor::getDims(int & wd, int & ht){
    (*inputImagePtr).getDims(wd, ht);
    width= wd;
    height = ht;
}


/*
Extract the components out of the PGMimage buffer.
*/
int PGMimageProcessor::extractComponents(unsigned char threashold, int minValidSize){
    const unsigned char * buffer =  (*inputImagePtr).getBuffer();
    int totalComponents = 0;

    for (int x = 0; x < width;++x){
        for (int y = 0; y < height ; ++y){
            
            if (buffer[x + y * width] >= threashold){
                
                ConnectedComponentPtr componentPtr = std::make_unique<ConnectedComponent>();
                // A target pixel is found, do recursion
                
                int size = extractConnectedComponent(threashold, x ,y, componentPtr);
                // std::cout << size << std::endl;
                if (size >= minValidSize){
                    ++totalComponents;
                    componentPtr->set_id();
                    // std::cout << "size++ " << components.size() << std::endl;
                    components.push_back(std::move(componentPtr));
                }

            }
        }
    }
    return totalComponents;
}

/*
Recursively find all the points of a single single connected component
Return: size of component
*/

int PGMimageProcessor::extractConnectedComponent(unsigned char threashold, int x, int y, ConnectedComponentPtr & componentPtr){
    int totalPixels = 0;
    // std::cout << x << ", " << y <<std::endl;
    if ((*inputImagePtr)(x, y) >= threashold){
        
        ++totalPixels;
        // std::cout<< "seg fault?" << x << ", " << y << std::endl;
        (*componentPtr).add_point(x, y);
        // std::cout<< "no seg fault at "<< x << ", " << y << std::endl;
        
        // Set the pixel to its default value so it doesn't get added again.
        
        (*inputImagePtr)(x, y)  = 0;

        for (int i = 0; i < 2; ++i){
            if (x + 1 < width) totalPixels += extractConnectedComponent(threashold, x + 1, y, componentPtr);
            if (x - 1 > 0) totalPixels += extractConnectedComponent(threashold, x - 1 , y, componentPtr);
        }
    
        for (int j = 0 ; j < 2; ++j){
            if (y + 1 < height) totalPixels += extractConnectedComponent(threashold, x, y + 1, componentPtr);
            if (y - 1 > 0) totalPixels += extractConnectedComponent(threashold, x, y - 1, componentPtr);
        }
    }

    return totalPixels;
}


/* iterate - with an iterator - though your container of connected components 
and filter out (remove) all the components which do not obey the size criteria,
 [minSize, maxSize] passed as arguments. The number remaining after this operation
  should be returned. NOTE: minSize need not be the minValidSize above
*/ 
int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
    components.remove_if([&minSize, &maxSize](const ConnectedComponentPtr & componentPtr ){
        int size = componentPtr -> size;
        return (size < minSize || size > maxSize);
    });
    return components.size();
}
/*
Write the components to a PGMimage, if the pixel is part of a component, then set value to 255, else 0;
*/
bool PGMimageProcessor::writeComponents(const std::string & outputName){
    using ComponentYSetPtr = std::unique_ptr<std::set<int>>;
    using ComponentMap = unordered_map<int, ComponentYSetPtr>;
    PGMimage output;
    // initialise buffer values to 0
    unsigned char * buffer = new unsigned char [width * height]();

    for (ConnectedComponentPtr & componentPtr : components){
        ComponentMap & componentPixels = *(componentPtr->pixels);
        for (const std::pair<int, ComponentYSetPtr &> & keyVal : componentPixels){
            int x = keyVal.first;
            std::set<int> & ySet = *(keyVal.second);
            for (int y : ySet){
                buffer[y * width + x] = 255;
            }
        }  
    }
    output.setImageData(buffer, width, height);
    return output.write(outputName);
}
void PGMimageProcessor::sort(){
    components.sort(
     [](const ConnectedComponentPtr& x, const ConnectedComponentPtr& y){
        return x->size < y->size;
        }
    );
}
int PGMimageProcessor::getLargestSize(){
    sort();
    return ((*std::prev(components.end()))->size);
}
int PGMimageProcessor::getSmallestSize(){
    sort();
    return ((*components.begin())->size);
}
void PGMimageProcessor::printComponentData(const ConnectedComponent & component) const{
    std::cout << component.id << std::endl;
    std::cout << component.size << std::endl;
}