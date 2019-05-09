#include "set_stl.h"

namespace stl {
    CSet::CSet(const std::string& str)
    {
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '1') {
                AddElement(i);
            }
        }
    }
	CSet::CSet(std::size_t n, unsigned long val)
	{
		for (std::size_t i = 0; i < n; i++) {
			if ((val >> i & 1) == 1)
				AddElement(i);
		}
	}
    CSet CSet::MakeDense(CSet::element_type n) {
        // use range constructor
        CSet a;
        for (CSet::element_type i = 0; i < n; i++)
            a.AddElement(i);
        return a;
    }
    CSet CSet::MakeEmpty(element_type n) {
        return CSet();
    }
   
   
 
    
    CSet CSet::GetMembers() const {
        return *this;
    }
   
    CSet CSet::Complement(std::size_t n) const {
        CSet::iterator max_value_it = end();
        max_value_it--;
        std::size_t range_n = std::max(n, *max_value_it + 1);
        CSet a;
        CSet::iterator b_it = begin();
        for (std::size_t i = 0; i <= *max_value_it; i++) {
            if (*b_it == i) {
                b_it++;
            }
            else {
                a.AddElement(i);
            }
        }
        for (std::size_t i = *max_value_it + 1; i < range_n; i++)
            a.AddElement(i);
        return a;
    }
	Partition Partition::makeFine(int size) {
		Partition p;
		for (int i = 0; i < size; i++) {
			stl::CSet A;
			A.AddElement(i);
			p.AddElement(A);
		}
		return p;
	}
	Partition Partition::makeDense(int size) {
		Partition p;
		p.AddElement(stl::CSet::MakeDense(size));
		return p;
	}
	Partition Partition::expand(const stl::CSet& A) {
		Partition p;
		stl::CSet A_extend = A;
		for (auto it = begin(); it != end(); it++) {
			if (it->Intersection(A).IsEmpty()) {
				p.AddElement(*it);
			}
			else {
				A_extend = A_extend.Union(*it);
			}
		}
		if(!A_extend.IsEmpty())
			p.AddElement(A_extend);
		return p;
	}
}