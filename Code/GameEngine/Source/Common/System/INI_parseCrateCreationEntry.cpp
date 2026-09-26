// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD
// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z, retail
// 0x0035CD23, 188 bytes. Serves the CrateObject entry of the table at
// 0x8162A0. Zero Hour CrateSystem.cpp proves the name and shape: read two
// tokens, build an AsciiString crate name, sscanf a float crate value
// (INIException(3, ...) plus _CxxThrowException on failure, scanReal
// precedent), fill a crateCreationEntry and push it onto the
// list<crateCreationEntry> m_possibleCrates at instance+0x3c (ZH
// CrateSystem.h: crateCreationEntryList). The store push lowers to the
// unclaimed list push_back at 0x0035CBFE (sole caller, twin pin). The
// AsciiString model mirrors SkirmishPreferences (inline default zeroes
// the entry name slot, inline PBD delegates to the rowed StringBase
// ctor at 0x0037BA0, teardown/assign ride the pinned 0x36410/0x366F0).

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *str);
	~StringBase();

private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *str) : StringBase<char>(str) {}
	AsciiString &operator=(const AsciiString &other);
};

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class list
{
public:
	void push_back(const T &value);
};
}

class INI
{
public:
	const char *getNextToken(const char *seps);
};

class CrateTemplate
{
public:
	static void parseCrateCreationEntry(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);

	char *mFailureMessage;
	int m_argumentCount;
};

__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, filled from retail by the gate -- scanReal precedent).
// Its content is never compared; the real chain lives in the retail image.
struct ParseCrateThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseCrateThrowInfoAnchor parseCrateThrowInfoAnchor = { 0, 0, 0, 0 };

// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z
void CrateTemplate::parseCrateCreationEntry(INI *ini, void *instance, void *, const void *)
{
	CrateTemplate *self = (CrateTemplate *)instance;

	const char *token = ini->getNextToken(0);
	AsciiString crateName = token;

	token = ini->getNextToken(0);
	float crateValue;
	if (sscanf(token, "%f", &crateValue) != 1) {
		INIException e(3, "Floating point value expected instead of '%s'", token);
		_CxxThrowException(&e, (void *)&parseCrateThrowInfoAnchor);
	}

	crateCreationEntry newEntry;
	newEntry.crateName = crateName;
	newEntry.crateChance = crateValue;

	((_STL::list<crateCreationEntry> *)((unsigned char *)self + 0x3c))->push_back(newEntry);
}
