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

bool isSorted(const vector<Thing>& v, function<bool(const Thing& a, const Thing&b)> comparethings){
    for(unsigned int i = 0; i<v.size()-1; ++i){
        if(v[i]>v[i+1]){
            return false;
        }
    }
    return true;
}

void printV(vector<int> v){
    for(int i = 0; i<v.size(); ++i){
        cout << v[i] << ", ";
    }
    cout << endl;
}

//, function<bool(const Thing& a, const Thing&b)> comp

void Sort(vector<Thing>& v, function<bool(const Thing& a, const Thing&b)> comparethings)
          {
    if(v.size()==1 || v.size() == 0){
        return;
    }
    vector<Thing> a;
    vector<Thing> b;

    for(unsigned int i = 0; i<v.size(); ++i){
        if(i<(v.size()/2)) {
            a.push_back(v[i]);
        } else {
            b.push_back(v[i]);
        }
    }
    Sort(a, comparethings);
    Sort(b, comparethings);
    unsigned int aindex = 0;
    unsigned int bindex = 0;
    for(unsigned int vi = 0; vi < v.size(); ++vi)
    {
        if(aindex<a.size()){
            if(bindex<b.size()){
                if(comparethings(a[aindex], b[bindex])){
                    v[vi].id = a[aindex].id;
                    v[vi].thingnyum = v[vi].thingnyum;
                    ++aindex;
                }
                else{
                    v[vi]=b[bindex];
                    ++bindex;
                }
            } else {
                for(int j = vi; j<v.size(); ++j){
                    cout << aindex   << "aindex" << endl;
                    v[j].id = a[aindex].id;
                    v[j].thingnyum = a[aindex].thingnyum;
                    ++aindex;
                }
            }
        }  else {
            if(bindex<b.size()){
                for(int i = vi; i<v.size(); ++i){
                    v[i].id = b[bindex].id;
                    v[i].thingnyum = b[bindex].thingnyum;
                    ++bindex;

                }
            }
        }
        /*if(bindex<b.size()){
            if(aindex<a.size()){
                if(b[bindex]<a[aindex]){
                    v[vi] = b[bindex];
                    ++bindex;
                }
            }
        } else {
            if(aindex<a.size()){
                for(int j = vi; j<v.size(); ++j){
                    cout<< aindex   << "aindex" << endl;
                    v[j] = a[aindex];
                    ++aindex;

                }
            }
      }*/
    }
    return;
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
    vector<Thing> test = {23, 21, 13, 5, 7, 2, 5, 3 ,9, 20, 32, 2, 5, 7};
    Sort(test, comparethings);
    ASSERT_TRUE(isSorted(test, comparethings));
}

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
