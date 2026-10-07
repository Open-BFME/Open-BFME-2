// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// FindInGameNotificationType, retail 0x0022216E (59B), from the WorldBuilder
// lead (InGameNotificationType.cpp; its "result != NULL" and name assertions
// at lines 291..292 are compiled out of retail). Retail makes sure the store
// singleton exists (0x002220DC, holder g_00DFE4C4), looks the name up in the
// store's AsciiString-keyed map at +0x28 with find (WorldBuilder's debug build
// uses operator[]) and returns the found entry's InGameNotificationType base
// (entry +8), or NULL.
//
// The store and entry types are not established and keep address-derived
// names.

#include "ascii_string.h"
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class InGameNotificationType
{
	unsigned char m_data[4];
};

struct Rva0022216EEntryHead
{
	unsigned char m_data[8];
};

struct Rva0022216EEntry : public Rva0022216EEntryHead, public InGameNotificationType
{
};

struct Rva0022216EStore
{
	unsigned char m_pad00[0x28];
	_STL::map<AsciiString, Rva0022216EEntry *> m_types;
};

class Rva00575674
{
public:
	void rva00575674(void *p);
	Rva0022216EStore *m_ptr;
};
extern Rva00575674 g_00DFE4C4;

void Rva002220DCInit();

InGameNotificationType *FindInGameNotificationType(const AsciiString &name)
{
	if (!g_00DFE4C4.m_ptr)
		Rva002220DCInit();
	_STL::map<AsciiString, Rva0022216EEntry *>::iterator it = g_00DFE4C4.m_ptr->m_types.find(name);
	if (it != g_00DFE4C4.m_ptr->m_types.end()) {
		Rva0022216EEntry *entry = (*it).second;
		return entry;
	}
	return 0;
}
