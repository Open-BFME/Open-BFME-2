// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// Complete boundaries: 427F14..427F46 (50B), 427F46..427F75 (47B).
// The two complete retail returns call rowed VersionBlockParser lookup
// 427EDA, then construct the caller's return storage with rowed STLport
// narrow-string constructor 9100. Key/default arguments expose only word 0;
// their original C++ wrapper types and these method spellings are unknown.
// stlport46
#include <vector>
#include <string>
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }

struct BfmeNarrowRecord00427F75;

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

typedef std::string NarrowString;

struct Rva00427F14KeyPrefix {
    const char *first;
    const char *text() const { return first; }
};

NarrowString VersionBlockParser::rva00427F14Text(const Rva00427F14KeyPrefix &key) {
    const char *text = lookupVersionValue(key.text(), 0);
    if (!text) text = "";
    return NarrowString(text);
}
NarrowString VersionBlockParser::rva00427F46Text(const Rva00427F14KeyPrefix &key,
                                               const Rva00427F14KeyPrefix &fallback) {
    return NarrowString(lookupVersionValue(key.text(), fallback.text()));
}
