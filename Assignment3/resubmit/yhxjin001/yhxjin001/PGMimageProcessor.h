// PGMimageProcessor.h
#include "PGMimage.h"
#include "ConnectedComponent.h"
#include <list>
#include <string>
#include <memory>

#ifndef PGM_PROCESSOR_H
#define PGM_PROCESSOR_H

namespace yhxjin001{
    using namespace std;
    using ConnectedComponentPtr = std::unique_ptr<ConnectedComponent>;
    class PGMimageProcessor{
        private:
        list<ConnectedComponentPtr> components;
        unique_ptr<PGMimage> inputImagePtr;
        int width;
        int height;
   
        public:
        // consturctors
        PGMimageProcessor();
        PGMimageProcessor(const PGMimageProcessor & rhs);
        PGMimageProcessor(PGMimageProcessor && rhs);
        // operator overloadings
        PGMimageProcessor & operator=(const PGMimageProcessor & rhs);  
        PGMimageProcessor & operator=(PGMimageProcessor && rhs);
        // destructor
        ~PGMimageProcessor(){}
        // class methods
        void read(const string & fileName);
        void getDims(int & wd, int & ht);
        int extractComponents(unsigned char threashold, int minValidSize);
        // int extractConnectedComponent(unsigned char threashold);
        int extractConnectedComponent(unsigned char threashold, int x, int y, ConnectedComponentPtr & component);
        int filterComponentsBySize(int minSize, int maxSize);
        bool writeComponents(const std::string & outputName);
        void sort();
        int getLargestSize();
        int getSmallestSize();
        void printComponentData(const ConnectedComponent & component) const;
        const list<ConnectedComponentPtr> & getComponentPtrs(){
            return components;
        }
    };
}

#endif