// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?realMapPathToPortableMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z @0x002DC833 452B:
// GameState save/map portable remap. Empty input returns itself via StringBase
// copy at 0x000365F0. Else Ascii save dir from Unicode rva002DC267 at
// 0x002DC267 plus Ascii ctor at 0x00038250, then MapCache "Maps" virtual
// getMapDir at 0x00300489, user maps rva00300D7A at 0x00300D7A and
// LivingWorldScripts Rva0030062CGet at 0x0030062C, each via startsWithNoCase
// at 0x0002C42F. Save branch sets g_00DBD054 and concats GameState
// getMapLeafName at 0x002DC802; map branches set g_00DBD058/5C/60 and concat
// getMapLeafAndDirName at 0x002DC2DD (static custom esi-edi); else set copy at
// 0x000366F0. toLower at 0x00036A70 then copy into hidden return. Donor BFME1
// GameState.cpp realMapPathToPortableMapPath plus retail 4th
// LivingWorldScripts branch and Unicode save dir. Callers 0x0030634E 0x004007A4.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

#include "../../../../Include/Common/Rva00300489.h"

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

AsciiString *Rva0030062CGet();

#include "../../../../Include/Common/GameState.h"

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
// ?getMapLeafAndDirName@@YA?AVAsciiString@@ABV1@@Z present-unmatched
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

AsciiString GameState::realMapPathToPortableMapPath(const AsciiString &in) const
{
	if (((const StringBase<char> &)in).getLength() == 0)
		return in;
	AsciiString prefix;
	if (((const StringBase<char> &)in).startsWithNoCase((const StringBase<char> &)AsciiString(((const Rva002DC267 *)this)->rva002DC267()))) {
		((StringBase<char> *)&prefix)->set(g_00DBD054);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase((const StringBase<char> &)((Rva00300489 *)TheMapCache)->Rva00300489::getMapDir())) {
		((StringBase<char> *)&prefix)->set(g_00DBD058);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase((const StringBase<char> &)((Rva00300D7A *)TheMapCache)->rva00300D7A())) {
		((StringBase<char> *)&prefix)->set(g_00DBD05C);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase((const StringBase<char> &)*Rva0030062CGet())) {
		((StringBase<char> *)&prefix)->set(g_00DBD060);
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)in);
	}
	((StringBase<char> *)&prefix)->toLower();
	return prefix;
}
