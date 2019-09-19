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
    CSet(int size_n, bool dense = false);

    int Cardinality() const;

    bool HasElement(int i) const;
    const_iterator begin() const;
    void clear();
    const_iterator end() const;
    void AddElement(int i, bool check_pos = false);
    //! return true if this has empty intersection with A
    bool Intersection_Empty(const stl::CSet& A);
    bool IsEmpty();

    friend std::ostream& operator << (std::ostream& stream, const CSet& X);

private:
    std::vector<bool> s;
    std::list<int> value_list;
};


class Partition {
public:
    typedef typename std::list<CSet>::iterator iterator;
    typedef typename std::list<CSet>::const_iterator const_iterator;

	static Partition makeFine(int size);
    Partition();
	void expand(stl::CSet& A);    
    void AddElement(const CSet& cset);
    void clear();
    int Cardinality() const;
    const_iterator begin() const;
    const_iterator end() const;
    friend std::ostream& operator << (std::ostream& stream, const Partition& P);

private:
    iterator removeElement(iterator pos);
    std::list<CSet> p_list;
};
}