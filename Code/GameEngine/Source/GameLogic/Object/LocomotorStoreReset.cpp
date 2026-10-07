// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?reset@LocomotorStore@@UAEXXZ retail 0x001E681D (66 bytes), from the
// WorldBuilder lead (LocomotorStore::reset in Locomotor.cpp) and Zero Hour's
// Locomotor.cpp: drop each template's overrides and erase the entries whose
// template goes away with them (erase(it++)).
//
// Target facts: m_locomotorTemplates sits at +0xC (as in the sibling
// LocomotorStoreFindTemplate.cpp view); the member is spelled map<int, void*>
// so the emitted erase names the rowed int/void* tree erase 0x005530A8
// (identical tree mechanics), and the stored pointer is the template's
// Overridable base (deleteOverrides 0x001E35ED).

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Overridable
{
public:
	Overridable *deleteOverrides();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
};

class LocomotorStore : public SubsystemInterface
{
public:
	void init();
	void reset();

private:
	char m_pad04[0xC - 4];
	_STL::map<int, void *> m_locomotorTemplates;
};

void LocomotorStore::reset()
{
	_STL::map<int, void *>::iterator it;
	for (it = m_locomotorTemplates.begin(); it != m_locomotorTemplates.end(); ) {
		Overridable *locoTemp = ((Overridable *)(*it).second)->deleteOverrides();
		if (!locoTemp)
			m_locomotorTemplates.erase(it++);
		else
			++it;
	}
}
