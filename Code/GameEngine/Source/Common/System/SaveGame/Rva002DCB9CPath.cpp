// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?packPortableMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z, retail 0x002DCB9C, 351 bytes.
// Retyped 2026-10-01 from the stdcall free function ?Rva002DCB9C@@YG?AVAsciiString@@ABV1@@Z:
// its caller 0x004007B4 (Rva00400783PortableMapPath.cpp) loads TheGameState
// into ecx before the call, so it is a GameState method that never touches
// this (thiscall with an unused this is byte-identical to stdcall here).
// AsciiString path remap: startsWithNoCase against g_00DBD054/58/5C/60 then
// set g_00DBD064/68/6C/70 plus suffix after prefix, else set g_00DBD074 plus
// whole input; toLower; return. Evidence: startsWith/set/concat/toLower rows,
// strlen via ji_00629170 thunk, str null-check to g_Rva0107301CEmptyString,
// ret 8 with hidden return at ebp+8 and ref at ebp+0xC (ecx unused), caller
// 0x004007C2. Neighbours Rva002DC802BaseName and rva002DCCFB same flags.
typedef unsigned int UInt;

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"


extern const char *g_00DBD054;
extern const char *g_00DBD058;
extern const char *g_00DBD05C;
extern const char *g_00DBD060;
extern const char *g_00DBD064;
extern const char *g_00DBD068;
extern const char *g_00DBD06C;
extern const char *g_00DBD070;
extern const char *g_00DBD074;
#include <string.h>

#include "../../../../Include/Common/GameState.h"

AsciiString GameState::packPortableMapPath(const AsciiString &in) const
{
	AsciiString out;
	if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD054)) {
		((StringBase<char> *)&out)->set(g_00DBD064);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD054));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD058)) {
		((StringBase<char> *)&out)->set(g_00DBD068);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD058));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD05C)) {
		((StringBase<char> *)&out)->set(g_00DBD06C);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD05C));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD060)) {
		((StringBase<char> *)&out)->set(g_00DBD070);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD060));
	} else {
		((StringBase<char> *)&out)->set(g_00DBD074);
		((StringBase<char> *)&out)->concat((const StringBase<char> &)in);
	}
	((StringBase<char> *)&out)->toLower();
	return out;
}

// GameState::unpackPortableMapPath, retail 0x002DC340 (376 bytes; WB
// 0x00E6E0B0, GameState.cpp:1572): the inverse of the packer above. A packed
// path starting with S, M, U or L gets its directory prefix back in front of
// the rest; X (the mixed form) keeps the rest as is; anything else is copied.
AsciiString GameState::unpackPortableMapPath(const AsciiString &in) const
{
	AsciiString out;
	if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD064)) {
		((StringBase<char> *)&out)->concat(g_00DBD054);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD064));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD068)) {
		((StringBase<char> *)&out)->concat(g_00DBD058);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD068));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD06C)) {
		((StringBase<char> *)&out)->concat(g_00DBD05C);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD06C));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD070)) {
		((StringBase<char> *)&out)->concat(g_00DBD060);
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD070));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD074)) {
		const char *s = in.str();
		((StringBase<char> *)&out)->concat(s + strlen(g_00DBD074));
	} else {
		((StringBase<char> *)&out)->set((const StringBase<char> &)in);
	}
	return out;
}
