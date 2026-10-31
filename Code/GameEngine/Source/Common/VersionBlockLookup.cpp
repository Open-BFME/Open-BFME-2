// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// Version-block lookup over the 0x18-byte records. The search helper
// writes the found record pointer into a local output slot.
#include <vector>
#include <string>
#include <string.h>
#pragma intrinsic(memset)

struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
};

struct VersionBlockEntry : public BfmeNarrowRecord00427F75
{
	VersionBlockEntry();
	VersionBlockEntry(const VersionBlockEntry &other);
	~VersionBlockEntry();
};

struct Rva00427F14KeyPrefix;

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
	~VersionBlockParser();
	const char *lookupVersionValue(const char *key, const char *defaultValue);
	_STL::basic_string<char> rva00427F14Text(const Rva00427F14KeyPrefix &key);
	_STL::basic_string<char> rva00427F46Text(const Rva00427F14KeyPrefix &key, const Rva00427F14KeyPrefix &fallback);
private:
	int m_size;
private:
	_STL::vector<BfmeNarrowRecord00427F75> m_records;
private:
	bool parse(const char *versionBlock);
public:
	void rva00428B27(const char *key, const char *value);
public:
	void rva00428BF0(const _STL::basic_string<char> &key, const _STL::basic_string<char> &value);
public:
	static const void *findEntry(const void *found, const void *first, const void *last, const char *const *key, const void *match);
public:
	static const void *lowerBound(const void *first, const void *last, const char *const *key, const void *comp, int filler);
public:
	static const void *upperBound(const void *first, const void *last, const char *const *key, const void *comp, int filler);
public:
	static const void *searchEntries(const void *found, const void *first, const void *last, const char *const *key, const void *match, int flags);
public:
	static const void *forwardLowerBound(const void *first, const void *last, const char *const *key, const void *match);
public:
	static const void *forwardUpperBound(const void *first, const void *last, const char *const *key, const void *match);
};

// Retail pushes the record bounds straight from the vector's members, not
// through inlined begin() and end() temporaries.
struct VersionRecordBounds : _STL::vector<BfmeNarrowRecord00427F75>
{
	using _STL::vector<BfmeNarrowRecord00427F75>::_M_start;
	using _STL::vector<BfmeNarrowRecord00427F75>::_M_finish;
};

const char *VersionBlockParser::lookupVersionValue(const char *key, const char *defaultValue)
{
	const VersionBlockEntry *found;
	volatile char match;
	memset((void *)&match, 0, 1);
	findEntry(&found, ((VersionRecordBounds &)m_records)._M_start, ((VersionRecordBounds &)m_records)._M_finish, &key, (const void *)(unsigned)*(volatile unsigned *)&match);
	if (found == (const VersionBlockEntry *)(unsigned)*(volatile unsigned *)&match)
		return defaultValue;
	return found->m_value.c_str();
}
