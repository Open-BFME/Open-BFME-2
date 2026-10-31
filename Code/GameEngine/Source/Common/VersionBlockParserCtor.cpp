// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
//
// ??0VersionBlockParser@@QAE@PBD@Z at retail 0x00428C04 (63B).
// Constructs the parser over the 512-byte version block: clears the header
// word, default-builds the 0x18-byte record vector at +4 through the
// Vector_base body pinned at 0x00211E58, then parses the block through the
// member pinned at 0x004289B8. Single EH state from the vector member.
// The parser destructor is unrowed so it stays declared-only here; the
// VersionDestructor TU keeps the buffer model that the rowed inner
// destructor (0x002385FF) verifies against.
// Retail stores 0x18-byte records with the key string at +0 and the value
// string at +0xC. The rowed parser at 0x004289B8 returns success in AL; this
// caller discards it.
// string at +0xC (VersionBlockSearch TU); spelled for readability, the
// constructor only needs the extent.
#include <vector>
#include <string>

struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
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
	// The rowed parser at 0x004289B8 returns success in AL; this caller
	// intentionally discards it. Keep the declaration identical to its owner.
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

VersionBlockParser::VersionBlockParser(const char *versionBlock)
	: m_size(0), m_records()
{
	parse(versionBlock);
}
