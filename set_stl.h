# pragma once
#include<set>
#include<string>
namespace stl{
//! a thin wrapper around std::set
class Set {
public:
    using element_type = std::size_t;
    using value_type = element_type;
    using iterator = std::set<element_type>::iterator;
    //! empty set
    Set() {}
    Set(const std::string& str);
    //! generate a set $\{0, 1, \dots, n-1\}$
    static Set MakeDense(element_type n);
    //! generate an empty set, the parameter is not used, reserved for compatibility consideration
    static Set MakeEmpty(element_type n);
    Set Union(const Set& X) const;
    Set Intersection(const Set& X) const;
    std::size_t Cardinality() const;
    bool HasElement(element_type i) const;
    bool IsSubSet(const Set& s) const;
    Set GetMembers() const;
    void AddElement(element_type i);
    iterator insert(iterator position, const element_type& val);
    iterator begin();
    iterator end();
    std::set<element_type>::const_iterator begin() const;
    std::set<element_type>::const_iterator end() const;
    
    friend std::ostream& operator << (std::ostream&, const Set&);
private:
    std::set<element_type> s;
};
bool operator==(const Set& a, const Set& b);
}