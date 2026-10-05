// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setVolume@OptionPreferences@@QAEXHM@Z, retail 0x002E545A,
// 144 bytes. Dedicated TU.
//
// BFME2-new indexed volume setter over the inline 20-byte volume-name table
// (SFX/Voice/Music/Ambient/MovieVolume). Same push-sink recipe as the landed
// setCampaignDifficulty sibling: the key is a NAMED local and the slot is a
// NAMED reference so the text push sinks below the op[] call. /G7 keeps the
// index*20 scaling as imul; folding the table base with compound assignment
// emits add-esi. Same string plumbing as the getter siblings with pinned
// operator[]/set/ctor/release/format callees. Retail keeps default EH.

#include <map>

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

static const char volumeNames[5][20] =
{
	"SFXVolume",
	"VoiceVolume",
	"MusicVolume",
	"AmbientVolume",
	"MovieVolume"
};

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void setVolume(Int index, Real value);
};

// ?setVolume@OptionPreferences@@QAEXHM@Z
void OptionPreferences::setVolume(Int index, Real value)
{
	if (index < 0 || index >= 5)
		return;
	AsciiString text;
	text.format("%f", value);
	// Retail scales the index with an integer imul and adds the table base
	// (imul esi,esi,0x14 + add esi,table). A plain index*20 subscript or
	// multiply is strength-reduced to lea/shift sequences instead (/G7 keeps
	// the imul), and the table address must fold into the scaled index with
	// compound assignment (add esi,imm) rather than a fresh lea.
	index *= 20;
	index += (Int)volumeNames;
	AsciiString key((const char *)index);
	AsciiString &slot = (*this)[key];
	((StringBase<char> *)&slot)->set(*(const StringBase<char> *)&text);
}
