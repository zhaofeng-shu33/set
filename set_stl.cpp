#include "set_stl.h"

namespace stl {
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