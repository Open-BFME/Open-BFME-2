// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva004185E4HitpointsAtLevel@@YAXPAVINI@@PAX1PBX@Z @0x004185E4 123B.
// Target evidence: the HitpointsAtLevel table entry parses Hitpoints then Level; retail inserts into the supplied int map and throws on duplicate keys.
// Structural inference: the float payload is stored as its four-byte representation in the int-valued map entry, matching the target stores.
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

void Rva004185E4HitpointsAtLevel(INI *ini, void *, void *store, const void *)
{
	union
	{
		float real;
		int bits;
	} hitpoints;
	hitpoints.real = ini->scanReal(ini->getNextSubToken("Hitpoints"));
	int level = ini->scanInt(ini->getNextSubToken("Level"));
	_STL::map<int, int> *entries = (_STL::map<int, int> *)store;
	_STL::pair<int, int> entry;
	entry.first = level;
	entry.second = hitpoints.bits;
	_STL::pair<_STL::map<int, int>::iterator, bool> inserted = entries->insert(entry);
	if (!inserted.second)
		throw INIException(1, "Duplicate hitpoint entries for level %d", level);
}
