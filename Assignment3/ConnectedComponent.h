#include <unordered_map>
#include <set>
#include <memory>

#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H
namespace yhxjin001{
    using namespace std;
    using ComponentMap = unordered_map<int, unique_ptr<set<int>>>; 
    class ConnectedComponent{
        private:
        static int count;
        public:
        unique_ptr<ComponentMap> pixels; // To store the pixels in a connected component
        int id;
        size_t size;

        ConnectedComponent();
        ConnectedComponent(const ConnectedComponent & rhs);
        ConnectedComponent(ConnectedComponent && rhs);
        ~ConnectedComponent(){};
        ConnectedComponent & operator=(const ConnectedComponent  & rhs);
        ConnectedComponent & operator=(ConnectedComponent && rhs);

        void add_point(int x, int y);
        bool operator<(const ConnectedComponent & rhs)const;
        void set_id();
    }; 
}
#endif