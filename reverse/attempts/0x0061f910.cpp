// ?subtract@Rva0061F720SetHolder@@QAEAAV1@ABV1@@Z
// partial score=0.85 date=2026-10-08
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// Retail 0x009EC4B0: merge one pointer set into another, removing the
// destination node when insert_unique reports a duplicate.
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <vector>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class Rva0061F720SetHolder
{
public:
	Rva0061F720SetHolder &merge(Rva0061F720SetHolder &other);
	Rva0061F720SetHolder &subtract(const Rva0061F720SetHolder &other);

	Rva001408C0Set m_values;
	unsigned int m_treeLayoutPad;
	volatile bool m_changed;
};

Rva0061F720SetHolder &Rva0061F720SetHolder::merge(Rva0061F720SetHolder &other)
{
	if (other.m_values.size() == 0)
		return *this;

	Rva001408C0Set::iterator it = other.m_values.begin();
	while (it != other.m_values.end())
	{
		_STL::pair<Rva001408C0Set::iterator, bool> result =
			m_values.insert(*it);
		if (!result.second)
			m_values.erase(result.first);
		++it;
	}
	m_changed = true;
	return *this;
}

Rva0061F720SetHolder &Rva0061F720SetHolder::subtract(const Rva0061F720SetHolder &other)
{
    _STL::vector<Rva001408C0Key> found;
    for (Rva001408C0Set::iterator it = m_values.begin(); it != m_values.end(); ++it)
        if (other.m_values.find(*it) != other.m_values.end())
            found.push_back(*it);
    if (!found.empty()) {
        for (_STL::vector<Rva001408C0Key>::iterator v=found.begin(); v!=found.end(); ++v)
            m_values.erase(*v);
        m_changed=true;
    }
    return *this;
}
