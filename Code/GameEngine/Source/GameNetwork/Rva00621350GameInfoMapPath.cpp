// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?_Rva00621350GameInfoMapPath@@YA?AVAsciiString@@ABV1@_N@Z retail 0x00400898, 367 bytes.
// Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/Rva00621350GameInfoMapPath.cpp at 1281192f68
// (donor flags /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc plus BFME 2's /O1). The
// donor's private StringBase/AsciiString view is replaced by the shared
// BFME 2 header (concat(char) keeps the donor's concat(&c, 1) form). Compiled
// that way the body places uniquely on unclaimed game.dat .text by masked whole-.text
// search (tools/donor_sweep.py) and reproduces retail byte for byte. The name is
// the donor's address-derived one, carried over unchanged.
//
// Callees, read from retail's REL32 displacements at the placement: the
// GameState map-path coder 0x002DC340 and portableMapPathToRealMapPath
// 0x002DC9F7, MapCache::getMapExtension 0x003004A5 (the ledger's 'map'
// extension getter), and the StringBase<char> copy/set/nextToken/concat/dtor
// bodies already in the ledger.

typedef bool Bool;

#include "ascii_string.h"

// The donor's AsciiString::concat(char) appends through
// StringBase<char>::concat(&c, 1): retail stores the byte to a stack slot and
// calls concat(text, len) at 0x000369A0. The shared header's concat(char)
// reaches StringBase<char>::concat(char) instead, so spell the donor's form.
static inline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

class GameState
{
public:
	AsciiString rva0010e580MapPathCode(const AsciiString &path) const;
	AsciiString portableMapPathToRealMapPath(const AsciiString &path) const;
};

class MapCache
{
public:
	AsciiString getMapExtension() const;
};

extern GameState *TheGameState;
extern MapCache *TheMapCache;

// ?_Rva00621350GameInfoMapPath@@YA?AVAsciiString@@ABV1@_N@Z
AsciiString _Rva00621350GameInfoMapPath(const AsciiString &input, Bool option)
{
	AsciiString path = input;
	if (option)
		path = TheGameState->rva0010e580MapPathCode(path);

	AsciiString actualpath;
	AsciiString token;
	path.nextToken(&token, "\\/");
	while (path.getLength() > 0)
	{
		actualpath.concat(token);
		concatChar(actualpath, '\\');
		path.nextToken(&token, "\\/");
	}

	actualpath.concat(token);
	concatChar(actualpath, '\\');
	actualpath.concat(token);
	concatChar(actualpath, '.');
	actualpath.concat(TheMapCache->getMapExtension());
	actualpath = TheGameState->portableMapPathToRealMapPath(actualpath);
	return actualpath;
}
