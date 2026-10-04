// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Give VC7.1 a declared pair destructor that explicit instantiation can emit.
#define _STLP_TRIVIAL_DESTRUCTOR_BUG
#include <utility>

class AsciiString;
class UnicodeString;

#include "string_base.h"

// Retail copies each string through its matching narrow or wide StringBase body.
#include "ascii_string.h"

#include "unicode_string.h"

// LadderPreferences::loadProfile fills these same offsets; the names agree
// with the upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    inline __declspec(noinline) LadderPref(const LadderPref &source);

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

// Keep the copy out of the pair constructor, whose retail body calls it at +0x13.
inline LadderPref::LadderPref(const LadderPref &source)
    : name(source.name), address(source.address), port(source.port), lastPlayDate(source.lastPlayDate)
{
}

typedef std::pair<const long, LadderPref> LadderPrefPair;
template LadderPrefPair::pair(const long &, const LadderPref &);
template LadderPrefPair::~pair();

// This TU owns the LadderPref copy row; other TUs emit header/implicit copies,
// so emit ours as a select-any COMDAT rather than a strong duplicate. The anchor
// forces emission here for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitLadderPrefCopy@@YAXPAVLadderPref@@ABV1@@Z present-unmatched
void bfmeEmitLadderPrefCopy(LadderPref *out, const LadderPref &source)
{
	out->LadderPref::LadderPref(source);
}
#pragma inline_depth()
