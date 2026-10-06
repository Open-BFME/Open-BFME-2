// ?parse@VersionBlockParser@@AAE_NPBD@Z
// partial score=0.9042 date=2026-10-05
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parse@VersionBlockParser@@AAE_NPBD@Z @0x004289B8 367B.
// Private version-block parser: validates ||VER1| header and size via strncmp
// sscanf strlen then splits key=value pairs on = and | into records pushed
// into the vector and finally sorts them. Evidence: pinned name (void spelling
// covers bool body); strings ||VER1| and %d|; callees all rowed;
// caller VersionBlockParserCtor 0x428C2D.
#include <vector>
#include <string>
#include <algorithm>

extern "C" int __cdecl strncmp(const char *a, const char *b, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);
extern "C" void __cdecl free(void *p);

struct VersionBlockEntry
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	VersionBlockEntry();
	~VersionBlockEntry();
};

struct VersionBlockKeyCompare
{
	bool operator()(const VersionBlockEntry &a, const VersionBlockEntry &b) const { return a.m_key < b.m_key; }
};

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
private:
	int m_size;
	_STL::vector<VersionBlockEntry> m_records;
	bool parse(const char *versionBlock);
};

// ?parse@VersionBlockParser@@AAE_NPBD@Z present-unmatched
bool VersionBlockParser::parse(const char *versionBlock)
{
	if (strncmp(versionBlock, "||VER1|", 7) != 0)
		return false;
	char *p = (char *)(versionBlock + 7);
	if (sscanf(p, "%d|", &m_size) != 1)
		return false;
	if (strlen(versionBlock) >= (unsigned int)m_size)
		return false;
	char *s = p;
	while (*s != 0)
	{
		if (*s == '|')
			break;
		++s;
	}
	if (*s != 0)
		++s;
	while (*s != 0)
	{
		char *keyStart = s;
		while (*s != 0 && *s != '=' && *s != '|')
			++s;
		if (*s != '=')
			continue;
		_STL::basic_string<char> key(keyStart, s);
		++s;
		char *valStart = s;
		while (*s != 0 && *s != '|')
			++s;
		_STL::basic_string<char> val(valStart, s);
		VersionBlockEntry e;
		e.m_key.assign(key);
		e.m_value.assign(val);
		m_records.push_back(e);
		if (*s != 0)
			++s;
	}
	_STL::sort(m_records.begin(), m_records.end(), VersionBlockKeyCompare());
	return true;
}
