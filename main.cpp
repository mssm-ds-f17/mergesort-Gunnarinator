#include <iostream>
#include <functional>
#include <vector>
#include <gtest/gtest.h>


using namespace std;

bool isSorted(const vector<int>& v){
    for(unsigned int i = 0; i<v.size()-1; ++i){
        if(v[i]>v[i+1]){
            return false;
        }
    }
    return true;
}



class Thing{
public:
    int id;
    int thingnyum;
  //  Thing();
    Thing(int i = 0);
};
/*
Thing::Thing(){
    id = 0;
}
*/
bool operator>(const Thing& a, const Thing& b){
    return a.id>b.id;
}

Thing::Thing(int i){
    id = i;
}

bool comparethings(const Thing& a, const Thing& b){
    return a.id<b.id;
}

bool isSorted(const vector<Thing>& v, function<bool(const Thing& a, const Thing&b)> comp){
    for(unsigned int i = 0; i<v.size()-1; ++i){
        if(v[i]>v[i+1]){
            return false;
        }
    }
    return true;
}

//, function<bool(const Thing& a, const Thing&b)> comp

void Sort(vector<int>& v){
    int size = v.size();
    vector<int> a(size/2);
    vector<int> b(size/2);
    if(size>1){
    for(unsigned int i = 0; i<size/2; ++i){
        a[i] = v[i];
    }
    for(unsigned int i = (size/2)+1; i<size; ++i){
        b[i] = v[i];
    }
    Sort(a);
    Sort(b);
    }
    unsigned int vindex = 0;
    unsigned int aindex = 0;
    unsigned int bindex = 0;
    while(vindex<=size-1 || aindex<=a.size()-1 || bindex<=b.size()-1){
            if(comparethings(a[aindex], b[bindex]) == true && aindex<a.size()){
                v[vindex] = a[aindex];
                ++aindex;
                ++vindex;
            }
            if(comparethings(b[bindex], a[aindex]) == true && bindex<b.size()){
                v[vindex] = b[bindex];
                ++bindex;
                ++vindex;
            }
        }
}

vector<Thing> makerandom(int count, int max){
    vector<Thing> retval;
    for(int i = 0; i < count; ++i){
        Thing value;
        value.id = rand()%max;
        value.thingnyum = i+1;
        retval.push_back(value);
    }
    return retval;
}

// assuming sorted:
bool isStable(vector<Thing> vec){
    int system;
    for(int i = 0; i<vec.size()-1; ++i){
        if(vec[i].id == vec[i+1].id){
            if(vec[i].thingnyum > vec[i+1].thingnyum){
                return false;
            }
        }
    }
    return true;
}

void printVector(vector<Thing> values){
    for(int i = 0; i<values.size(); ++i){
        cout << values[i].thingnyum << ", " << values[i].id << endl;
    }
}


TEST(SortTest, isSortedVectorSorted){
    vector<Thing> vec = makerandom(5, 101);
    printVector(vec);
    vector<Thing> v = {1, 2, 3, 3, 4};
  //  ASSERT_TRUE(isSorted(v, comparethings));
    vector<int> test = {4, 21, 13, 5, 6, 2};
    Sort(test);
    ASSERT_TRUE(isSorted(test));
}

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
