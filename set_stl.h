# pragma once
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
namespace stl{
    template <class T>
    class Set {
    public:
        using element_type = T;
        using value_type = element_type;
        typedef typename std::set<element_type>::iterator iterator;
        typedef typename std::set<element_type>::const_iterator const_iterator;
        //! empty set
        Set() {}

        std::size_t Cardinality() const {
            return s.size();
        }
        bool HasElement(element_type i) const {
            return static_cast<bool>(s.count(i));
        }
        bool IsSubSet(const Set& X) const {
            for (element_type i : s) {
                if (!X.HasElement(i))
                    return false;
            }
            return true;
        }
        void AddElement(element_type i) {
            s.insert(i);
        }
        iterator insert(iterator position, const element_type& val) {
            return s.insert(position, val);
        }
        iterator begin() {
            return s.begin();
        }
        iterator end() {
            return s.end();
        }
        const_iterator begin() const {
            return s.begin();
        }
        const_iterator end() const {
            return s.end();
        }
        bool IsEmpty() { return s.size() == 0; }
        friend std::ostream& operator << (std::ostream& stream, const Set& X) {
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
        friend bool operator==(const Set& a, const Set& b) {
            return a.s == b.s;
        }
        friend bool operator!=(const Set& a, const Set& b) {
            return a.s != b.s;
        }

        Set Union(const Set& X) const {
            Set a;
            std::set_union(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
            return a;
        }
        Set Intersection(const Set& X) const {
            Set a;
            std::set_intersection(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
            return a;
        }

    private:
        std::set<element_type> s;
    };
//! a thin wrapper around std::set
class CSet : public Set<std::size_t> {
public:
    CSet(){}
    CSet(const std::string& str);
    //! generate a set $\{0, 1, \dots, n-1\}$
    static CSet MakeDense(element_type n);
    //! generate an empty set, the parameter is not used, reserved for compatibility consideration
    static CSet MakeEmpty(element_type n);    
    // return self
    CSet GetMembers() const;
    CSet Complement(std::size_t n) const;
    CSet Union(const CSet& X) const {
        CSet a;
        std::set_union(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
        return a;
    }
    CSet Intersection(const CSet& X) const {
        CSet a;
        std::set_intersection(X.begin(), X.end(), begin(), end(), std::inserter(a, a.begin()));
        return a;
    }
    friend bool operator<(const CSet& X, const CSet& Y) {
        //alphebatical order
        iterator it_x = X.begin(), it_y = Y.begin();
        while (it_x != X.end() && it_y != Y.end()) {
            if (*it_x > *it_y)
                return false;
            else if (*it_x < *it_y)
                return true;
            it_x++;
            it_y++;
        }
        return false;
    }
};

}