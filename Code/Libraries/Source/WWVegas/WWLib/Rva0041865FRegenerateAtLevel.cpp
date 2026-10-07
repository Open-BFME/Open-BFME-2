// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva0041865FRegenerateAtLevel@@YAXPAVINI@@PAX1PBX@Z @0x0041865F 123B.
// Target evidence: the adjacent table entry identifies RegenerateAtLevel; retail parses Regenerate then Level, inserts into the supplied int map, and throws on duplicate keys.
#include <map>

class INI
{
public:
	const char *getNextSubToken(const char *name);
	float scanReal(const char *text);
	int scanInt(const char *text);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int code, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

void Rva0041865FRegenerateAtLevel(INI *ini, void *, void *store, const void *)
{
	union
	{
		float real;
		int bits;
	} regenerate;
	regenerate.real = ini->scanReal(ini->getNextSubToken("Regenerate"));
	int level = ini->scanInt(ini->getNextSubToken("Level"));
	_STL::map<int, int> *entries = (_STL::map<int, int> *)store;
	_STL::pair<int, int> entry;
	entry.first = level;
	entry.second = regenerate.bits;
	_STL::pair<_STL::map<int, int>::iterator, bool> inserted = entries->insert(entry);
	if (!inserted.second)
		throw INIException(1, "Duplicate regenerate rate entries for level %d", level);
}
