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

#include "../../../../Include/Common/Rva002DC267.h"

#include "../../../../Include/Common/Rva00300489.h"

#include "../../../../Include/Common/Rva00300D7A.h"

class MapCache;
extern MapCache *TheMapCache;

// Retail's own four path-prefix pointers at RVA 0x009BD054 / 58 / 5C / 60 (.data,
// file offset 0x0096CC54): each a pointer into retail's .rdata string pool. The
// save-game path remap both directions (this unit and its inverse) and the
// three-unit startsWithNoCase walk in SaveGame/Rva002DCB9CPath.cpp read them, so
// one definition serves all three. Each definition keeps `extern` in front of it
// so the objects take external linkage.
// Symbols ?g_00DBD054@@3PBDB, ?g_00DBD058@@3PBDB, ?g_00DBD05C@@3PBDB and
// ?g_00DBD060@@3PBDB, transcribed below.
extern const char *g_00DBD054;
const char *g_00DBD054 = "Save\\";
extern const char *g_00DBD058;
const char *g_00DBD058 = "Maps\\";
extern const char *g_00DBD05C;
const char *g_00DBD05C = "UserData\\Maps\\";
extern const char *g_00DBD060;
const char *g_00DBD060 = "LivingWorldScripts\\";
// The matching single-letter replacements at RVA 0x009BD064 / 68 / 6C / 70 / 74
// (.data, file offset 0x0096CC64), each a pointer into retail's .rdata string
// pool: the packed form starts with the letter for whichever prefix matched, so
// the packer in SaveGame/Rva002DCB9CPath.cpp writes S, M, U, L or X in place of
// "Save\\", "Maps\\", "UserData\\Maps\\", "LivingWorldScripts\\" or the
// mixed form. Same ownership and the same `extern` spelling as above.
// Symbols ?g_00DBD064@@3PBDB, ?g_00DBD068@@3PBDB, ?g_00DBD06C@@3PBDB,
// ?g_00DBD070@@3PBDB and ?g_00DBD074@@3PBDB, transcribed below.
extern const char *g_00DBD064;
const char *g_00DBD064 = "S";
extern const char *g_00DBD068;
const char *g_00DBD068 = "M";
extern const char *g_00DBD06C;
const char *g_00DBD06C = "U";
extern const char *g_00DBD070;
const char *g_00DBD070 = "L";
extern const char *g_00DBD074;
const char *g_00DBD074 = "X";
// Native BBE09C is the shared backslash literal.

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
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)((Rva00300489 *)TheMapCache)->Rva00300489::getMapDir());
		((StringBase<char> *)&prefix)->concat("\\");
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD05C)) {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)((Rva00300D7A *)TheMapCache)->rva00300D7A());
		((StringBase<char> *)&prefix)->concat("\\");
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else if (((const StringBase<char> &)in).startsWithNoCase(g_00DBD060)) {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)*Rva0030062CGet());
		((StringBase<char> *)&prefix)->concat("\\");
		((StringBase<char> *)&prefix)->concat((const StringBase<char> &)getMapLeafAndDirName(in));
	} else {
		((StringBase<char> *)&prefix)->set((const StringBase<char> &)in);
	}
	((StringBase<char> *)&prefix)->toLower();
	return prefix;
}
