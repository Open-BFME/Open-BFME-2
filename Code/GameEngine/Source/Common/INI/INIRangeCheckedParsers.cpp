// cl: /DNDEBUG /MD /GX-
//
// Range-checked FieldParse procs (names address-derived):
//   0x004E8D8C 90B TargetPriorityModifiers (0x00BFD824): reals for every token
//       into the store's float array, throwing INIException (argument count 2)
//       "In an AIKINDOF list, each type may only appear once\n" past 16 entries.
//   0x00403233 71B Category (0x00C38698): the next token's single bit in the
//       15-bit flag names (rowed BitFlags<15>::getSingleBitFromName 0x003182F3)
//       must fall in 1..14, else INIException (argument count 3) "Invalid
//       Category encountered by ModifierList::Category".

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	float scanReal(const char *token);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

template <int NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

// ?Rva004E8D8CParse@@YAXPAVINI@@PAX1PBX@Z
void Rva004E8D8CParse(INI *ini, void *, void *store, const void *)
{
	float *values = (float *)store;
	int i = 0;
	for (const char *token = ini->getNextToken(); token; token = ini->getNextTokenOrNull(), ++i)
	{
		if (i >= 16)
			throw INIException(2, "In an AIKINDOF list, each type may only appear once\n");
		values[i] = ini->scanReal(token);
	}
}

// ?Rva00403233Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00403233Parse(INI *ini, void *, void *store, const void *)
{
	int bit = BitFlags<15>::getSingleBitFromName(ini->getNextToken());
	if (bit > 0 && bit < 15)
	{
		*(int *)store = bit;
		return;
	}
	throw INIException(3, "Invalid Category encountered by ModifierList::Category");
}
