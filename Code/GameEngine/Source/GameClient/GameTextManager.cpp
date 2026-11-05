// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /EHsc
// stlport
// ??1GameTextManager@@UAE@XZ 0x002E66F2 89B
// Evidence: chain from 0x002E6551 clear plus vectorAscii 0x0002CC70 plus wide release 0x00036E70 plus base 0x001B4E74; vtables 0x00804FA8 0x00804E90; caller 0x002E67D1.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

// Base dtor at 0x001B4E74 by its row name ??1SubsystemInterface@@UAE@XZ (SubsystemInterface.cpp).
typedef bool Bool;
#include "subsystem_interface.h"

extern "C" const void *const __identifier("??_7Rva002E55D8@@6B@")[];

class Rva002E66F2Mid : public SubsystemInterface
{
public:
	virtual ~Rva002E66F2Mid() { *(const void **)this = __identifier("??_7Rva002E55D8@@6B@"); }
};

class Rva002E674B
{
public:
	void rva002E674B(_STL::vector<AsciiString> &out, const AsciiString &filter);
};

class GameTextTable;

namespace _STL
{
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *);
}

class GameTextManager : public Rva002E66F2Mid
{
public:
	virtual ~GameTextManager();
	virtual void init();
	virtual bool vslot04(int);
	virtual void reset();
	virtual void update() {}
	virtual UnicodeString fetch(const char *label, Bool *exists);
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists);
	virtual UnicodeString *fetchPtr(const char *label, Bool *exists);
	virtual UnicodeString *fetchPtr(const AsciiString &label, Bool *exists);
	virtual _STL::vector<AsciiString> &getStringsWithLabelPrefix(const AsciiString &filter);
	virtual void initMapStringFile(const AsciiString &filename);
	virtual void setTranslateMode(int mode);
	virtual int getTranslateMode() { return m_translateMode; }
	virtual void deinit();

private:
	char m_pad0C[0x11];
	unsigned char m_flag1d;
	char m_pad1e[0x02];
	UnicodeString m_wide20;
	void *m_list24;
	char m_pad28[0x04];
	GameTextTable *m_textTable;
	GameTextTable *m_mapTable;
	_STL::vector<AsciiString> m_asciiStringVec;
	int m_translateMode;
};

GameTextManager::~GameTextManager()
{
	GameTextManager::deinit();
}

// ?getStringsWithLabelPrefix@GameTextManager@@UAEAAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@ABVAsciiString@@@Z @0x002E67EA 60B
// Evidence: vslot 18 offset 0x48 of vtable 0x00804FA8 class GameTextManager;
// clears the vector at +0x34, enumerates the tables at +0x2C and +0x30,
// then returns the vector. Member names agree with GameText.cpp.
_STL::vector<AsciiString> &GameTextManager::getStringsWithLabelPrefix(const AsciiString &filter)
{
	_STL::vector<AsciiString> &vec = m_asciiStringVec;
	vec.erase(vec.begin(), vec.end());
	if (m_textTable)
		((Rva002E674B *)m_textTable)->rva002E674B(vec, filter);
	if (m_mapTable)
		((Rva002E674B *)m_mapTable)->rva002E674B(vec, filter);
	return vec;
}
