#include "set_stl.h"
#include <algorithm>
#include <iterator>
namespace stl {
    Set::Set(const std::string& str)       
    {
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '1') {
                AddElement(i);
            }
        }
    }
    Set Set::MakeDense(Set::element_type n) {
        // use range constructor
        Set a;
        for (Set::element_type i = 0; i < n; i++)
            a.AddElement(i);
        return a;
    }
    Set Set::MakeEmpty(element_type n) {
        return Set();
    }
    bool Set::HasElement(Set::element_type i) const {
        return static_cast<bool>(s.count(i));
    }
    void Set::AddElement(Set::element_type i) {
        s.insert(i);
    }
    Set::iterator Set::begin() {
        return s.begin();
    }
    Set::iterator Set::end() {
        return s.end();
    }
    std::set<Set::element_type>::const_iterator Set::begin() const {
        return s.begin();
    }
    std::set<Set::element_type>::const_iterator Set::end() const {
        return s.end();
    }
    Set::iterator Set::insert(Set::iterator position, const Set::element_type& val) {
        return s.insert(position, val);
    }
    Set Set::Intersection(const Set& X) const {
        Set a;
        std::set_intersection(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
        return a;
    }
    Set Set::Union(const Set& X) const {
        Set a;
        std::set_union(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
        return a;
    }
    std::size_t Set::Cardinality() const {
        return s.size();
    }
    Set Set::GetMembers() const {
        return *this;
    }
    bool Set::IsSubSet(const Set& s) const {
        for (element_type i : GetMembers()) {
            if (!s.HasElement(i))
                return false;
        }
        return true;
    }

    std::ostream& operator << (std::ostream& stream, const Set& X) {
        stream << "{";
        std::size_t cnt = 0, limiter = X.Cardinality();
        for (Set::iterator i = X.begin(); i != X.end(); i++) {
            stream << *i;
            cnt++;
            if (cnt != limiter) {
                stream << ", ";
            }
        }
        stream << "}";
        return stream;
    }
    bool operator==(const Set& a, const Set& b) {
        return a.IsSubSet(b) && b.IsSubSet(a);
    }
}