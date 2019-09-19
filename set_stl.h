# pragma once
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <iostream>
namespace stl{
class CSet {
public:
    typedef typename std::list<int>::iterator iterator;
    typedef typename std::list<int>::const_iterator const_iterator;

    //! empty set
    CSet(int size_n, bool dense= false) {
        s.resize(size_n, dense);
        if(dense)
            for (int i = 0; i < size_n; i++)
                AddElement(i);
        size = size_n;
    }

    int Cardinality() const {
        return size;
    }

    bool HasElement(int i) const {
        return s[i];       
    }
    const_iterator begin() const {
        return value_list.begin();
    }

    const_iterator end() const {
        return value_list.end();
    }
    void AddElement(int i) {
        s[i] = true;
        // we assume value_list is sorted
        value_list.push_back(i);
    }
    //! return true if this has empty intersection with A
    bool Intersection_Empty(const stl::CSet& A) {
        iterator self_element = value_list.begin();
        const_iterator it = A.begin();
        while(self_element != value_list.end() && it != A.end()) {
            if (*self_element > * it) {
                it++;
            }
            else if (*self_element < *it) {
                self_element++;
            }
            else
                return false;
        }
        return true;
    }
    bool IsEmpty() { return size == 0; }

    friend std::ostream& operator << (std::ostream& stream, const CSet& X) {
        stream << "{";
        for (int i = 0; i < X.size - 1; i++) {
            if(X.HasElement(i))
                stream << i << ", ";
        }
        if (X.HasElement(X.size - 1))
            stream << (X.size - 1);
        stream << "}";
        return stream;
    }

private:
    std::vector<bool> s;
    int size;
    std::list<int> value_list;
};


class Partition {
public:
    typedef typename std::list<CSet>::iterator iterator;
	static Partition makeFine(int size);
	Partition() {}
	void expand(stl::CSet& A);    
    void AddElement(const CSet& cset);
    void clear();
    int Cardinality() const;
    
private:
    iterator removeElement(iterator pos);
    std::list<CSet> p_list;
};
}