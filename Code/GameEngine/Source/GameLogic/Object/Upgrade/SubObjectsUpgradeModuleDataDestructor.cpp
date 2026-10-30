// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1SubObjectsUpgradeModuleData@@UAE@XZ @0x004B5214, 127 bytes.
// Target identity is supported by the audited SubObjectsUpgrade registration,
// the data factory at 0x0025780C, constructor at 0x00257768, and vtable
// 0x00BF41A8 (see deleting-destructor-identity-audit.md). Ghidra confirms the
// retail destructor clears the vector at +0x13C through the helper at
// 0x004C0628, destroys vectors at +0x13C/+0x130/+0x124/+0x118, then restores
// Snapshot's vtable. Member order and replacement-model semantics follow the
// BFME1 donor at the current reference pointer. Retail Ghidra evidence shows
// that BFME2 stores 8-byte replacement-model values in the final vector, so
// this target-specific declaration uses values rather than donor pointers.

#include <vector>


#include "ascii_string.h"
#include "Common/Snapshot.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

struct Rva00B6CF1
{
	~Rva00B6CF1();

	AsciiString m_source;
	AsciiString m_replacement;
};

// The replacement-model vector's destructor and range erase are retail's
// rowed copies (0x000C03D8 and 0x000C0628, stlport_vector_rva00b6cf1_*.cpp);
// declaring the specializations keeps this unit from emitting its own.
namespace _STL {
template <> vector<Rva00B6CF1, allocator<Rva00B6CF1> >::~vector();
template <> _Vector_base<Rva00B6CF1, allocator<Rva00B6CF1> >::~_Vector_base();
template <> Rva00B6CF1 *vector<Rva00B6CF1, allocator<Rva00B6CF1> >::erase(Rva00B6CF1 *first, Rva00B6CF1 *last);
}

class SubObjectsUpgradeModuleData : public Snapshot
{
public:
	virtual ~SubObjectsUpgradeModuleData();
	unsigned char m_pad[0x118 - 4];
	_STL::vector<AsciiString> m_showSubObjects;
	_STL::vector<AsciiString> m_hideSubObjects;
	_STL::vector<AsciiString> m_excludeSubobjects;
	_STL::vector<Rva00B6CF1> m_textureSwaps;
	float m_fadeTime;
	float m_waitBeforeFade;
	unsigned char m_flag150;
	unsigned char m_flag151;
	unsigned char m_flag152;
	unsigned char m_flag153;
};

SubObjectsUpgradeModuleData::~SubObjectsUpgradeModuleData()
{
	m_textureSwaps.clear();
}
