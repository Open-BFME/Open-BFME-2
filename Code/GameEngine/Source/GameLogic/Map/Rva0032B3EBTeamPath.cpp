// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?Rva0032B3EBTeamPath@@YA?AVAsciiString@@PBVDict@@PA_N@Z, retail 0x0032B3EB
// (194 bytes). Free function returning a team's "owner/name" path from its
// team dictionary: the teamOwner string (exists flag passed through) and
// when the flag is cleared the empty string; otherwise '/' and the teamName
// string are appended and the flag is checked again. No call site or data
// reference in game.dat; WorldBuilder twin 0x00A87EE0 (unnamed; alignment
// evidence) has the same call sequence. It sits right after the sibling
// path join Rva0032B389Join in the SidesList code. Evidence (target): keys
// TheKey_teamOwner 0x009BD9FC and TheKey_teamName 0x009BD9F4 through the
// pinned StaticNameKey::key 0x00148F5E; pinned Dict::getAsciiString
// 0x0031359F; rowed AsciiString operator+=(char) 0x000065FA; StringBase
// concat 0x00006987 and releaseBuffer 0x00036410; copy of
// AsciiString::TheEmptyString (0x009E0878) through StringBase copy
// 0x000365F0. EH cleanup funclet 0x0077B652 belongs to this body.

#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const; // 0x00148F5E
private:
	mutable NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_teamOwner; // 0x009BD9FC
extern const StaticNameKey TheKey_teamName; // 0x009BD9F4

class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const; // 0x0031359F
};

AsciiString Rva0032B3EBTeamPath(const Dict *dict, Bool *exists)
{
	AsciiString path = dict->getAsciiString(TheKey_teamOwner.key(), exists);
	if (exists && !*exists)
		return AsciiString::TheEmptyString;
	path += '/';
	path += dict->getAsciiString(TheKey_teamName.key());
	if (exists && !*exists)
		return AsciiString::TheEmptyString;
	return path;
}
