// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// parseAllowedFactions, retail 0x00534FFB (140 bytes). Built from the banked
// attempt reverse/attempts/0x00534ffb.cpp, which was already byte-exact; its
// set<AsciiString> swap callee is the ICF-folded tree swap at 0x0032AC92,
// now pinned as an alias. Uses the shared ascii_string.h so the emitted
// ??_GAsciiString copy calls releaseBuffer like the kept WOLBuddyOverlay copy;
// drops /Oy- (EH keeps the body framed, and /Oy- forced a framed ??_G).
// stlport
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
class INI { public: static void parseAsciiStringVector(INI *,void *,void *,const void *); };
struct SideFlags { unsigned char human,computer,ai; int team; _STL::set<AsciiString> factions; };
void parseAllowedFactions(INI *ini, void *instance, void *, const void *)
{
    _STL::vector<AsciiString> names;
    INI::parseAsciiStringVector(ini,0,&names,0);
    _STL::set<AsciiString> factions;
    _STL::copy(names.begin(),names.end(),_STL::inserter(factions,factions.begin()));
    ((SideFlags *)instance)->factions.swap(factions);
}
