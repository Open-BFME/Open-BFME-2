// cl: /O1 /G7 /arch:SSE /EHsc /MD /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// SidesList::parseCastleTemplateMaps, retail 0x0032F84F (439 bytes), with the declarations
// of SidesListDataChunks.cpp it needs. WorldBuilder's debug twin wb 0xA8BBC0 (SidesList.cpp:2957)
// fixes the shape: the map name is copy-constructed, an empty name returns, the file name is
// copy-constructed from the path, and a missing file skips to the next name after a
// DEBUG_ASSERTCRASH(fileFound) that release compiles out; written as
// `if (!fileFound) continue;` it gives retail's EBX zero register and frame homes.
//
// BuildListInfo layout (target): BuildListInfoCtor.cpp, 0x80 bytes, built by
// the ctor 0x0032A0CE and destroyed by 0x0032A186 on the parser's stack.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
#include <vector>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree_base<AsciiString, allocator<AsciiString> >::~_Rb_tree_base(); }
namespace _STL { template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base(); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * allocator<_Rb_tree_node<AsciiString> >::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString>, allocator<_Rb_tree_node<AsciiString> > >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *, unsigned int); }
namespace _STL { template <> void allocator<_Rb_tree_node<AsciiString> >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int) const; }
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, unsigned int) const; }
// bfme link decl-only end


enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };

#include "../../../Include/Common/DataChunkInfo.h"

class ChunkInputStream
{
};

// The cached file stream the build-list loader reads (BFME 1's
// CachedFileInputStream), rowed under its constructor's address name: ctor
// 0x00240000, dtor 0x0023F4F0 and open 0x00308050; its close is rowed under
// Rva003079ED below. 0x20 bytes on the loader's stack.
class Rva00240000 : public ChunkInputStream
{
public:
	Rva00240000() throw(); // 0x00240000
	~Rva00240000(); // 0x0023F4F0
	bool rva00308050(AsciiString path); // 0x00308050, open
private:
	char m_data[0x20]; // +0x00
};

class Rva003079ED
{
public:
	void rva003079ED();					// 0x003079ED, close
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
class Dict;
#include "../../../Include/Common/DataChunk.h"

// DataChunkInput's parser unregistration (WB DataChunkInput::unregisterParser),
// rowed under its address-era spelling.
#include "../../../Include/GameLogic/Q1Forwardee0000871A.h"

// The chunk parser binding: registers its label on construction and
// unregisters itself on destruction; its base dtor is inline here (vtable
// 0x007C9574), its ctor out of line.
class BfmeParserRegistryVE;

class BfmeParserBindingBaseVE
{
public:
	__declspec(dllimport) __forceinline virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	int m_token;						// +0x08
};

// BFME 2's SidesList has two bases (SidesList_sidesInfo.cpp), so its member
// pointers are the 8-byte multiple-inheritance form; this view flattens them.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class SidesList
{
public:
	SidesList();						// 0x0032EE24
	virtual ~SidesList();				// 0x0032EC63

	void parseCastleTemplateMaps();		// 0x0032F84F
	bool parseCastleTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);

private:
	char m_bases[0x20 - 4];
	_STL::list<AsciiString> m_castleTemplateMaps;	// +0x20
	char m_rest[0x11B0 - 0x24];
};

// The castle build-list and path maps' clear (this +0x24 and +0x30).
struct Rva0032EAA1Node;
class Rva0032D3D3
{
public:
	void rva0032DCB7();
private:
	void *m_head;
private:
	int m_flag;
public:
	~Rva0032D3D3();
};

class Rva0032EAA1
{
public:
	void rva0032EAA1(void *p);
	void rva0032EB5E();
	Rva0032EAA1Node *m_header;
	int m_count;
};

class Rva0032ED61
{
public:
	void rva0032ED61();
	char m_pad00[0x24];
private:
	Rva0032D3D3 m_24; // +0x24
	char m_pad2C[0x4];
	Rva0032EAA1 m_30; // +0x30
};

// The SidesList chunk binding (BfmeDataChunkParserBinding.cpp): its callback
// is an 8-byte member pointer, its base destructor the inline one above.
#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef bool (SidesList::*BfmeSidesListChunkCallback)(DataChunkInput &, DataChunkInfo *);

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
		DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel);	// 0x000AD73D

	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	SidesList *m_owner;
	BfmeSidesListChunkCallback m_callback;
};

void SidesList::parseCastleTemplateMaps()
{
	((Rva0032ED61 *)this)->rva0032ED61();
	for (_STL::list<AsciiString>::iterator it = m_castleTemplateMaps.begin(); it != m_castleTemplateMaps.end(); ++it) {
		AsciiString mapName = *it;
		if (mapName.isEmpty())
			return;
		AsciiString path("Bases\\");
		path.concat(mapName);
		path.concat("\\");
		path.concat(mapName);
		path.concat(".bse");
		AsciiString fileName(path);
		Rva00240000 fileStrm;
		bool fileFound = fileStrm.rva00308050(fileName);
		if (!fileFound)
			continue;
		{
			DataChunkInput file(&fileStrm);
			BfmeParserBindingVE parser(this, &SidesList::parseCastleTemplateDataChunk, &file, "CastleTemplates", AsciiString::TheEmptyString);
			if (!file.parse(0))
				throw ERROR_CORRUPT_FILE_FORMAT;
			((Rva003079ED *)&fileStrm)->rva003079ED();
		}
	}
}
