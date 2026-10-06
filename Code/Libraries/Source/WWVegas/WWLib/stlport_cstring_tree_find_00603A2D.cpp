// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??$_M_find@PBD@?$_Rb_tree@PBDU?$pair@QBDURva00603A00Mapped@@@_STL@@U?$_Select1st@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@URva006038D4Less@@V?$allocator@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@QBDURva00603A00Mapped@@@_STL@@@1@ABQBD@Z @ 0x00603A2D (82B).
// C-string keyed _Rb_tree _M_find in the 0x00600854-0x00604518 strcmp-keyed family.
// Evidence: SGI _M_find shape (y=header x=root loop with _S_key at +0x10 via rowed C-string Less 0x006038D4); prev/next rows 0x00603A00/0x00603A7F share header layout ([ebx]=header [edi+4]=root left+8 right+12) and // cl: flags; callers 0x00600B58 0x00603C2B 0x006045CA unblock on landing; node key at +0x10 compared via Less.
// Comparator Rva006038D4Less is the shared strcmp ordering whose operator() body is byte-identical (27B) to the rowed free helper 0x006038D4; it is declared only here and pinned there as ICF twin. Mapped is the opaque 4-byte placeholder from the sibling erase TU; _M_find bytes are independent of trivial mapped type.
// Both spellings consume two stack pointers and return the same bool; the
// free provider ignores the comparator's extra ECX `this` value.
#pragma comment(linker, "/alternatename:??RRva006038D4Less@@QBE_NPBD0@Z=?Rva0006038D4CStrLess@@YG_NPBD0@Z")
#include <map>

struct Rva00603A00Mapped
{
	unsigned int m_bits;
};

struct Rva006038D4Less
{
	bool operator()(const char *a, const char *b) const;
};

typedef _STL::pair<const char* const, Rva00603A00Mapped> Rva00603A2DPair;
typedef _STL::_Rb_tree<const char*, Rva00603A2DPair, _STL::_Select1st<Rva00603A2DPair>, Rva006038D4Less, _STL::allocator<Rva00603A2DPair> > Rva00603A2DTree;

template Rva00603A2DTree::_Link_type Rva00603A2DTree::_M_find<const char*>(const char* const &) const;
