// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?portableMapPathToRealMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z @0x002DC9F7 421B:
// GameState portable-to-real remap, inverse of realMapPathToPortable at
// 0x002DC833. Portable save prefix g_00DBD054 maps to Unicode save dir
// rva002DC267 at 0x002DC267 plus leaf base at 0x002DC802; portable map
// prefixes g_00DBD058/5C/60 map to MapCache getMapDir at 0x00300489, user
// maps rva00300D7A at 0x00300D7A and LivingWorldScripts Rva0030062CGet at
// 0x0030062C, each plus g_00BBE09C backslash plus leaf-and-dir at 0x002DC2DD;
// else copy input. toLower then copy into hidden return. Donor BFME1
// GameState.cpp portableMapPathToRealMapPath plus retail 4th
// LivingWorldScripts branch. Callers 0x0030637B 0x004D6342.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

class Rva00300489
{
public:
	virtual AsciiString rva00300489() const;
};

class Rva00300D7A : public Rva00300489
{
public:
	AsciiString rva00300D7A();
};

class MapCache;
extern MapCache *TheMapCache;

extern const char *g_00DBD054;
extern const char *g_00DBD058;
extern const char *g_00DBD05C;
extern const char *g_00DBD060;
extern const char g_00BBE09C[];

AsciiString *Rva0030062CGet();

class GameState
{
public:
	AsciiString getMapLeafName(const AsciiString &in) const;
	AsciiString portableMapPathToRealMapPath(const AsciiString &in) const;
};

// Local static with same signature as the rowed 0x002DC2DD helper. Defined in
// this TU so the caller uses the retail static-internal esi-edi convention
// (lea edi + call, no pushes) like the same-TU retail build does.
static const char *findLastBackslashInRangeInclusive(const char *start, const char *end)
{
	while (end >= start) {
		if (*end == '\\')
			return end;
		--end;
	}
	return 0;
}
static AsciiString getMapLeafAndDirName(const AsciiString &in)
{
	const char *start = in.str();
	const char *end = in.str() + in.getLength() - 1;
	const char *q = findLastBackslashInRangeInclusive(start, end);
	if (q) {
		const char *q2 = findLastBackslashInRangeInclusive(start, q - 1);
		if (q2)
			return q2 + 1;
		return in;
	}
	return in;
}

AsciiString GameState::portableMapPathToRealMapPath(const AsciiString &in) const
{
	AsciiString prefix;
	if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD054)) {
		prefix = ((const Rva002DC267 *)this)->rva002DC267();
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD058)) {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)((Rva00300489 *)TheMapCache)->Rva00300489::rva00300489());
		((StringBase<char> *)&prefix)->concat(g_00BBE09C);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD05C)) {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)((Rva00300D7A *)TheMapCache)->rva00300D7A());
		((StringBase<char> *)&prefix)->concat(g_00BBE09C);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD060)) {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)*Rva0030062CGet());
		((StringBase<char> *)&prefix)->concat(g_00BBE09C);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)in);
	}
	((StringBase<char> *)&prefix)->toLower();
	return prefix;
}
