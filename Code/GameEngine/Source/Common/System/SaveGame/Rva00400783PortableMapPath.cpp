// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva00400783Get@@YA?AVAsciiString@@ABV1@_N@Z, retail 0x00400783 (277 bytes).
// Portable map-path builder: TheGameState->realMapPathToPortableMapPath
// (pinned 0x002DC833), then when the flag is set the path is remapped through
// the GameState method at 0x002DCB9C (row retyped from a stdcall free function
// in the same commit: retail loads TheGameState into ecx before that call,
// which the earlier free-function model read as a dead load), then the path
// is split on "\\" with nextToken and rejoined with '/' while a backslash is
// still present (backslash to slash conversion). Callers 0x00400B3E 0x00447CFE. Honest address name.
#include "ascii_string.h"

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
	AsciiString packPortableMapPath(const AsciiString &in) const;
};

extern GameState *TheGameState;

AsciiString __cdecl Rva00400783Get(const AsciiString &mapPath, bool flag)
{
	AsciiString portable = TheGameState->realMapPathToPortableMapPath(mapPath);
	if (flag != false) {
		((StringBase<char> *)&portable)->set(*(const StringBase<char> *)&TheGameState->packPortableMapPath(portable));
	}
	AsciiString accum;
	if (((const StringBase<char> *)&portable)->getLength() > 0) {
		const char *backslash = "\\/";
		AsciiString token;
		while (true) {
			((StringBase<char> *)&portable)->nextToken((StringBase<char> *)&token, backslash);
			if (((const StringBase<char> *)&portable)->find('\\') == NULL)
				break;
			if (((const StringBase<char> *)&accum)->getLength() > 0) {
				char sep = '/';
				((StringBase<char> *)&accum)->concat(&sep, 1);
			}
			((StringBase<char> *)&accum)->concat(*(const StringBase<char> *)&token);
		}
	}
	return accum;
}
