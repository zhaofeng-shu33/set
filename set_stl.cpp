#include "set_stl.h"

namespace stl {
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
                    A.AddElement(*it_inner);
                it = removeElement(it);
            }
        }
        if (!A.IsEmpty())
            AddElement(A);        
	}
}