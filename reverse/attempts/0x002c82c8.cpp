// ?parseToken@Rva002C82C8WeaponConditionParser@@QAE_NPBDPA_N1@Z
// partial score=0.9 date=2026-09-24
// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi- /D_STLP_USE_STATIC_LIB
//
// Address-derived parser for the weapon-condition flag set stored by Horde
// RankInfo. The 0xC45530 RankInfo field callback passes its +0x14 or +0x24
// 128-bit flag block here. Retail uses the expanded name table at 0x00DBC2C8
// (104 names, beginning with the BFME1 WeaponSetFlags names), and the shared
// scanIndex worker at 0x2BCAB. The class name is address-derived; the exact EA
// typedef for this 128-bit RankInfo member has not been recovered.

typedef int Int;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" void __cdecl memset(void *, int, unsigned int);
extern "C" int rva002bcab_scanIndex(const char *, ConstCharPtrArray, Bool *, Bool);
extern "C" void rva002f681_fill(void *, int, const char *, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *, void *);

struct INIException
{
	char *message;
	int code;
};

class Rva002C82C8WeaponConditionParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	void clear() { memset(m_words, 0, sizeof(m_words)); }
	unsigned int m_words[4];
};

Bool Rva002C82C8WeaponConditionParser::parseToken(
	const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	const ConstCharPtrArray names = reinterpret_cast<ConstCharPtrArray>(0x00DBC2C8);
	Bool found;
	unsigned int bit;
	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub)
			goto mixingError;
		clear();
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal)
			goto mixingError;
		bit = (unsigned int)rva002bcab_scanIndex(token + 1, names, &found, true);
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
		*foundAddOrSub = true;
		return true;
	} else if (token[0] == '-') {
		if (*foundNormal)
			goto mixingError;
		bit = (unsigned int)rva002bcab_scanIndex(token + 1, names, &found, true);
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
		*foundAddOrSub = true;
		return true;
	} else {
		if (*foundAddOrSub)
			goto mixingError;
		if (!*foundNormal)
			clear();
		bit = (unsigned int)rva002bcab_scanIndex(token, names, &found, true);
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
		*foundNormal = true;
		return true;
	}

mixingError:
	{
		INIException e;
		rva002f681_fill(&e, 2, (const char *)0x00BBE0DC);
		_CxxThrowException(&e, (void *)0x00CFE2FC);
	}
}
