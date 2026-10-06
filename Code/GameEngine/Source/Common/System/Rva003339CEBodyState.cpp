// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?rva003339CE@Rva003339CE@@QAE_NPBDPA_N1@Z @0x003339CE 308B
// Single-token BodyState bitstring worker. Evidence: the BodyStateNames table
// at VA 0xda5f30 is baked in as an immediate, the "you may not mix normal and
// +- ops in bitstring lists" INIException filler-throw matches
// INI_parseBitString32, the 0x10 memset clears four words for 101 BodyState
// bits, and callers at 0x00334546 0x003B1084 0x003B10D0 drive it per token.

// ?rva002C82C8@Rva002C82C8@@QAE_NPBDPA_N1@Z @0x002C82C8 308B is the same
// worker over the BitFlags<104> names (VETERAN, ELITE, HERO...) at VA
// 0xdbc2c8, the table BitFlags104VeterancyGetSingleBitFromName.cpp reads;
// callers at 0x002C87C1 and 0x002C880D drive it per token.
// ?rva000B664E@Rva000B664E@@QAE_NPBDPA_N1@Z @0x000B664E 308B: the same worker
// over the 591 ModelCondition names at VA 0xdbaa98 (TOPPLED, FRONTCRUSHED...),
// clearing 0x4C bytes (19 words); driven per token by 0x0033394D.

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

extern const char *BodyStateNames[];
extern const char *VeterancyNames104[];
extern const char *const ModelConditionNames[];

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class Rva003339CE
{
public:
	Bool rva003339CE(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[4];
};

class Rva000B664E
{
public:
	Bool rva000B664E(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[19];
};

class Rva002C82C8
{
public:
	Bool rva002C82C8(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[4];
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" int rva002bcab_scanIndex(const char *token, ConstCharPtrArray nameList, Bool *found, Bool doThrow);
extern "C" void *memset(void *dst, Int val, unsigned n);

Bool Rva003339CE::rva003339CE(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
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
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, BodyStateNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, BodyStateNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, BodyStateNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

Bool Rva002C82C8::rva002C82C8(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
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
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, VeterancyNames104, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, VeterancyNames104, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, VeterancyNames104, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}

Bool Rva000B664E::rva000B664E(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
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
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, ModelConditionNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, ModelConditionNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, ModelConditionNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}
