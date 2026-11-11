// cl:   /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE
// stlport
// Retail 0x0033DBE5..0x0033DC9C, 183 bytes, cdecl FieldParse callback.
// The 0x0033DC9C UnitSpecificSounds parser supplies this callback to INI.
// ZH/BFME1 ThingTemplate::parseArbitrarySoundsIntoMap is the semantic lead;
// target calls independently establish token lookup, the 8-byte shared sound
// value, two 12-byte records, tree insertion, and cleanup in reverse order.
// The original callback and record type names remain unknown.
//
// Keep userData as const void* and decode name in a separate local: MSVC reuses
// that dead argument home for the temporary string. The converting insertion
// wrapper expresses the temporary base-record lifetime and retains retail's
// explicit address reload after its copy constructor. It adds no data members
// and makes no claim about an original target class. Real provider bodies and
// all four EH cleanup states are checked separately from the code bytes.
// This sibling TU preserves the target ABI views without changing the broader
// ThingTemplate.cpp donor unit or its unrelated unmatched definitions.
#include "ascii_string.h"
#include <set>
struct FieldParse;
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
#include "../../../Include/Common/Rva002390CB.h"
#include "../../../Include/Common/Rva002390CBInlines.h"
struct BfmeStringRecord002CF550 {
 AsciiString text; Rva002390CB sound;
 BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &);
 ~BfmeStringRecord002CF550();
};
struct BfmeStringRecord0033B1DE { AsciiString text; Rva002390CB sound; ~BfmeStringRecord0033B1DE(); };
struct Rva0033B830 : BfmeStringRecord0033B1DE {
 operator const BfmeStringRecord002CF550 &() const { return *(const BfmeStringRecord002CF550 *)this; }
};
Rva0033B830 Rva0033BEF5Make(const StringBase<char> &, const Rva002390CB &);
void Rva00339235(const char *, void *);
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > TreeR;
template <> _STL::pair<TreeR::iterator, bool> TreeR::insert_unique(const TreeR::value_type &);
template <> void TreeR::clear();
struct SoundMapInsertRecord : BfmeStringRecord002CF550 {
 SoundMapInsertRecord(const Rva0033B830 &value):BfmeStringRecord002CF550(value) {}
};

typedef char SoundValueExtent[sizeof(Rva002390CB) == 8 ? 1 : -1];
typedef char RecordExtent[sizeof(SoundMapInsertRecord) == 12 ? 1 : -1];

void Rva0033DBE5Parse(INI *ini, void *instance, void *, const void *userData) {
 const char *name=(const char *)userData;
 const char *token = ini->getNextToken();
 Rva002390CB sound;
 Rva00339235(token, &sound);
 ((TreeR *)instance)->insert_unique(SoundMapInsertRecord(Rva0033BEF5Make(*(const StringBase<char> *)&AsciiString(name), sound)));
}

// Retail VA 0x00C10C2C: wildcard callback followed by the complete zero sentinel.
// The descriptive data name does not assert an original spelling.
extern const FieldParse BfmeUnitSpecificSoundFields[] = {
 {0, Rva0033DBE5Parse, 0, 0}, {0, 0, 0, 0}
};

// Retail 0x0033DC9C..0x0033DCB8. Target calls establish the map clear and INI
// dispatch; ThingTemplate::parsePerUnitSounds is the donor semantic lead.
void Rva0033DC9CParse(INI *ini, void *, void *store, const void *) {
 ((TreeR *)store)->clear();
 ini->initFromINI(store, BfmeUnitSpecificSoundFields);
}
