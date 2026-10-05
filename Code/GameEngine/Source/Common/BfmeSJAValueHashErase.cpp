// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?erase@?$hash_map@VAsciiString@@URva004609B0Mapped@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@_STL@@@6@@_STL@@QAEXU?$_Ht_iterator@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@_STL@@@2@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@URva004609B0Mapped@@@_STL@@@2@@2@@Z @0x00411066 30B leaf hash_map iterator eraser via explicit instantiation like ArmorHashMapErase.
// Evidence: caller 0x00411B3B in bfmeLoadSJA; callee 0x00410AC7 rowed Rva0041097BDelete; same 30B EBP-frame shape as 0x001E2861.
#include <hash_map>
#include <cstddef>
#include "ascii_string.h"

namespace rts
{
template <class T> struct hash;
template <> struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const;
};
}

struct Rva004609B0Mapped
{
	char m_body[44];
};

typedef _STL::hash_map<AsciiString, Rva004609B0Mapped, rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeSJAValueHash;

template void BfmeSJAValueHash::erase(BfmeSJAValueHash::iterator);
