// ?rva003FB508@Rva003FB3B8@@QAEXPAVINI@@PAX@Z
// partial score=1.0 date=2026-10-07
// cl: /Oy- /DNDEBUG /MD /EHs /Oi-
//
// ?rva0033AFBB@Rva0033AFBB@@QAE_NPBDPA_N1@Z @0x0033AFBB 308B
// Single-token VeterancyLevel bitstring worker. Evidence: the pinned
// BitFlags<21> name table VeterancyLevelNames at 0x00DBAA40 is baked in as an
// immediate, the "you may not mix normal and +- ops in bitstring lists"
// INIException filler-throw matches INI_parseBitString32, and the two call
// sites in 0x0033B84E drive it per token (false return = NONE break).

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

// VeterancyLevelNames: the retail string table at VA 0xdbaa40 (88B: 21 string pointers + NULL).
const char *VeterancyLevelNames[22] = {
	"VETERAN",
	"ELITE",
	"HERO",
	"PLAYER_UPGRADE",
	"WEAK_VERSUS_BASEDEFENSES",
	"ALTERNATE_FORMATION",
	"MOUNTED",
	"PLAYER_UPGRADE_2",
	"PLAYER_UPGRADE_3",
	"UNBESIEGEABLE",
	"AS_TOWER",
	"CREATE_A_HERO_01",
	"CREATE_A_HERO_02",
	"CREATE_A_HERO_03",
	"CREATE_A_HERO_04",
	"CREATE_A_HERO_05",
	"CREATE_A_HERO_06",
	"CREATE_A_HERO_07",
	"CREATE_A_HERO_08",
	"CREATE_A_HERO_09",
	"CREATE_A_HERO_10",
	0,
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class Rva0033AFBB
{
public:
	Bool rva0033AFBB(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" int rva002bcab_scanIndex(const char *token, ConstCharPtrArray nameList, Bool *found, Bool doThrow);
extern "C" void *memset(void *dst, Int val, unsigned n);

Bool Rva0033AFBB::rva0033AFBB(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, VeterancyLevelNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, VeterancyLevelNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, VeterancyLevelNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

// Five more single-token bitstring workers of the same 308-byte shape, each over
// its own BitFlags name table (the immediate the scans push); only that operand
// and the call displacements differ from rva0033AFBB. Two tables are defined
// elsewhere (g_rva0033A3F4Table, CommandSetNames); the other three are defined
// here from retail .data, NULL-terminated as retail is. Owners keep addresses.

extern const char *g_rva0033A3F4Table[];

class Rva0021AAFE
{
public:
	Bool rva0021AAFE(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

Bool Rva0021AAFE::rva0021AAFE(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_rva0033A3F4Table, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_rva0033A3F4Table, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, g_rva0033A3F4Table, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

// g_Va00DD263CNames: the retail string table at VA 0xdd263c.
const char *g_Va00DD263CNames[8] = {
	"Planning",
	"MoveArmies",
	"ResolveBattles",
	"FakePhaseOne",
	"PlanRetreats",
	"RetreatArmies",
	"Complete",
	0,
};

class Rva003B44EE
{
public:
	Bool rva003B44EE(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

Bool Rva003B44EE::rva003B44EE(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DD263CNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DD263CNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, g_Va00DD263CNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

// g_Va00DC17CCNames: the retail string table at VA 0xdc17cc.
const char *g_Va00DC17CCNames[8] = {
	"ZOOMED_IN",
	"ZOOMED_OUT",
	"ZOOMING_IN",
	"VISIBLE",
	"ONCE",
	"NO_KILL",
	"FADE_IN",
	0,
};

class Rva003FB3B8
{
public:
	Bool rva003FB3B8(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
	void rva003FB508(class INI *, void *);

private:
	unsigned m_words[1];
};

Bool Rva003FB3B8::rva003FB3B8(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DC17CCNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DC17CCNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, g_Va00DC17CCNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

// g_Va00DC85C4Names: the retail string table at VA 0xdc85c4.
const char *g_Va00DC85C4Names[9] = {
	"AutoResolveUnit_Soldier",
	"AutoResolveUnit_Archer",
	"AutoResolveUnit_Pikemen",
	"AutoResolveUnit_Cavalry",
	"AutoResolveUnit_Monster",
	"AutoResolveUnit_Hero",
	"AutoResolveUnit_Fortress",
	"AutoResolveUnit_INVALID",
	0,
};

class Rva00417C23
{
public:
	Bool rva00417C23(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

Bool Rva00417C23::rva00417C23(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DC85C4Names, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, g_Va00DC85C4Names, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, g_Va00DC85C4Names, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

extern const char *CommandSetNames[];

class Rva0049B750
{
public:
	Bool rva0049B750(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

Bool Rva0049B750::rva0049B750(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, CommandSetNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, CommandSetNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, CommandSetNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

// Native INI list drivers: 0x003FB508 and 0x003B1017, both 234B RET 8.
// Control flow and every call are independently read from retail. The quoted
// token loop uses the existing string wrapper at 0x37BA0/0x36D90/0x36410,
// token reader 0x2DFE2 and receiver-independent join helper 0x49B6AE.
// The worker calls establish the existing Rva003FB3B8 and Rva003339CE views;
// original list-driver names are unknown. Algorithm follows the verified
// ModelCondition sibling 0xB937E in AssetListOperatorInsert.cpp. EHs is needed
// by the two local string lifetimes; all six original workers still verify.

class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr000B937E(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}


// Existing receiver-independent join helper binding; no new callee alias.
class Rva000B937E { public: void rva000B937EAppend(const char *, Rva0033B84ETok *); };

void Rva003FB3B8::rva003FB508(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr000B937E(part);
				((Rva000B937E*)this)->rva000B937EAppend(s, accum);
				if (!rva003FB3B8(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva000B937E*)this)->rva000B937EAppend(token, accum);
			if (!rva003FB3B8(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}

class Rva003339CE {public: bool rva003339CE(const char *,bool *,bool *); void rva003B1017(INI *,void *); private: unsigned m_words[4];};
void Rva003339CE::rva003B1017(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr000B937E(part);
				((Rva000B937E*)this)->rva000B937EAppend(s, accum);
				if (!rva003339CE(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva000B937E*)this)->rva000B937EAppend(token, accum);
			if (!rva003339CE(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
