// cl: /DNDEBUG /MD /GX-
//
// Thin token FieldParse procs (original names unproven; address names):
//   0x001DFBC7 33B / 0x001DFC09 33B Type (0x00BDD7F4 / 0x00BDD8A0, store
//       +0x148): scanLookupList of the next token over the lookup tables at
//       0x00BDD0B4 / 0x00BDD1D0 into the int store.
//   0x00492F6A 79B ChangeWeather (0x00C4E7F8): weather index over the names at
//       0x00DCAE84 into the store, throwing INIException "Invalid Weather
//       setting: '%s'." (passing the store pointer) outside 0..5.
//   0x0035AECF 5B DoubleClick (0x00C15638): forwards to INI::parseBool (a
//       tail jump).
//   0x0035B864 70B Stances (0x00C15778): every token's index over the names
//       at 0x00C3C210 that falls in 0..5 is appended to the 4-byte enum vector
//       at the store (push_back fold 0x002E01C6).

#define NULL 0

struct LookupListRec;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
	int scanIndexList(const char *token, const char *const *names);
	int scanLookupList(const char *token, const LookupListRec *table);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

struct RGBColor
{
	float red;
	float green;
	float blue;
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

extern const LookupListRec g_00BDD0B4[];
extern const LookupListRec g_00BDD1D0[];
extern const char *g_00DCAE84[];
extern const char *g_00C3C210[];

enum StanceType
{
	STANCE_INVALID = -1
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<StanceType, allocator<StanceType> >
{
public:
	void push_back(const StanceType &x);
private:
	StanceType *m_start;
	StanceType *m_finish;
	StanceType *m_endOfStorage;
};
}

// ?Rva001DFBC7Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva001DFBC7Parse(INI *ini, void *, void *store, const void *)
{
	*(int *)store = ini->scanLookupList(ini->getNextToken(), g_00BDD0B4);
}

// ?Rva001DFC09Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva001DFC09Parse(INI *ini, void *, void *store, const void *)
{
	*(int *)store = ini->scanLookupList(ini->getNextToken(), g_00BDD1D0);
}

// ?Rva00492F6AParse@@YAXPAVINI@@PAX1PBX@Z
void Rva00492F6AParse(INI *ini, void *, void *store, const void *)
{
	int weather = ini->scanIndexList(ini->getNextToken(), g_00DCAE84);
	*(int *)store = weather;
	if (weather < 0 || weather > 5)
		throw INIException(3, "Invalid Weather setting: '%s'.", store);
}

// ?Rva0035B864Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0035B864Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	while (token)
	{
		StanceType stance = (StanceType)ini->scanIndexList(token, g_00C3C210);
		if (stance >= 0 && stance < 6)
			((_STL::vector<StanceType, _STL::allocator<StanceType> > *)store)->push_back(stance);
		token = ini->getNextTokenOrNull();
	}
}

// ?Rva0035AECFParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0035AECFParse(INI *ini, void *instance, void *store, const void *userData)
{
	INI::parseBool(ini, instance, store, userData);
}

// ?Rva001DFC2AParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x001DFC2A, 168 bytes.
// Evidence: REF table slot 0x007DD27C neighbour "Color"; strings "R" "G" "B"
// and "color value %s=%i out of range (0..255)"; callees getNextSubToken
// 0x0002E06B scanInt 0x0002ECCF INIException 0x0002F681 plus float 1/255 at
// 0x007BB8F0; shape follows INI::parseRGBColor with lower bound -255 per
// retail cmp eax,0xffffff01.
void Rva001DFC2AParse(INI *ini, void *, void *store, const void *)
{
	const char *names[3] = { "R", "G", "B" };
	int colors[3];
	for (int i = 0; i < 3; i++)
	{
		colors[i] = ini->scanInt(ini->getNextSubToken(names[i]));
		if (colors[i] < -255 || colors[i] > 255)
			throw INIException(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
	}
	RGBColor *theColor = (RGBColor *)store;
	theColor->red = colors[0] * (1.0f / 255.0f);
	theColor->green = colors[1] * (1.0f / 255.0f);
	theColor->blue = colors[2] * (1.0f / 255.0f);
}
