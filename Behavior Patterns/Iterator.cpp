#include <iostream>
#include <vector>
using namespace std;

template < typename T > class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T    next()    = 0;
};

template < typename T > class VectorIterator : public Iterator< T > {
public:
    VectorIterator(vector< T >& v) : vec(v), index(0) {}

    bool hasNext() override {
        return index < vec.size();
    }

    T next() override {
        return vec[index++];
    }

private:
    vector< T >& vec;
    int          index;
};

template < typename T > class Aggregate {
public:
    virtual Iterator< T >* createIterator() = 0;
};

template < typename T > class VectorAggregate : public Aggregate< T > {
public:
    VectorAggregate(vector< T >& v) : vec(v) {}

    Iterator< T >* createIterator() override {
        return new VectorIterator< T >(vec);
    }

private:
    vector< T >& vec;
};

int main() {
    vector< int >     v   = { 1, 2, 3, 4, 5 };
    Aggregate< int >* agg = new VectorAggregate< int >(v);

    Iterator< int >*  it  = agg->createIterator();
    while (it->hasNext()) {
        cout << it->next() << " ";
    }

    cout << endl;
    
    delete it;
    delete agg;
    return 0;
}