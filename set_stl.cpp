#include "set_stl.h"

namespace stl {
    CSet::CSet(int size_n, bool dense) {
        s.resize(size_n, false);
        if (dense)
            for (int i = 0; i < size_n; i++)
                AddElement(i);       
    }

    int CSet::Cardinality() const {
        return value_list.size();
    }

    bool CSet::HasElement(int i) const {
        return s[i];
    }
    CSet::const_iterator CSet::begin() const {
        return value_list.begin();
    }
    void CSet::clear() {
        s.resize(s.size(), false);
        value_list.clear();
    }
    CSet::const_iterator CSet::end() const {
        return value_list.end();
    }
    void CSet::AddElement(int i, bool check_pos) {
        // we assume value_list is sorted
        if (s[i])
            return;
        s[i] = true;
        if(check_pos){
            for (const_iterator it = begin(); it != end(); it++)
                if (*it > i) {
                    value_list.insert(it, i);
                    return;
                }            
        }
        value_list.push_back(i);
    }
    //! return true if this has empty intersection with A
    //! make sure all value_lists are sorted
    bool CSet::Intersection_Empty(const stl::CSet & A) {
        iterator self_element = value_list.begin();
        const_iterator it = A.begin();
        while (self_element != value_list.end() && it != A.end()) {
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
    bool CSet::IsEmpty() { return value_list.size() == 0; }

    std::ostream& operator << (std::ostream & stream, const CSet & X) {
        stream << "{";
        int cnt = 0;
        int limiter = X.Cardinality();
        for (CSet::const_iterator it = X.begin(); it != X.end(); it++) {
            stream << *it;
            cnt++;
            if (cnt != limiter) {
                stream << ", ";
            }
        }
        stream << "}";
        return stream;
    }

    Partition::Partition() {}
    void Partition::AddElement(const CSet& cset) {
        p_list.push_back(cset);
    }
    void Partition::clear() {
        p_list.clear();
    }
    int Partition::Cardinality() const {
        return p_list.size();
    }
    Partition::iterator Partition::removeElement(iterator pos) {
        return p_list.erase(pos);
    }
    Partition Partition::makeFine(int size) {
        Partition p;
        for (int i = 0; i < size; i++) {
            stl::CSet A(size);
            A.AddElement(i);
            p.AddElement(A);
        }
        return p;
    }
	void Partition::expand(stl::CSet& A) {        
        std::list<CSet>::iterator it = p_list.begin();
        while(it != p_list.end()) {
            if (it->Intersection_Empty(A)) {
                it++;
            }
            else {
                for (CSet::const_iterator it_inner = it->begin(); it_inner != it->end(); it_inner++)
                    A.AddElement(*it_inner, true);
                it = removeElement(it);
            }
        }
        if (!A.IsEmpty())
            AddElement(A);        
	}
    Partition::const_iterator Partition::begin() const {
        return p_list.begin();
    }

    Partition::const_iterator Partition::end() const {
        return p_list.end();
    }

    std::ostream& operator << (std::ostream& stream, const Partition& P) {
        stream << "{";
        int cnt = 0;
        int limiter = P.Cardinality();
        for (Partition::const_iterator it = P.begin(); it != P.end(); it++) {
            stream << *it;
            cnt++;
            if (cnt != limiter) {
                stream << ", ";
            }
        }
        stream << "}";
        return stream;
    }
}