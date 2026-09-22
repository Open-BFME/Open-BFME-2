// cl: /O1 /EHsc
// stlport
//
// ??0VersionBlockParser@@QAE@PBD@Z at retail 0x00428C04 (63B).
// Constructs the parser over the 512-byte version block: clears the header
// word, default-builds the 0x18-byte record vector at +4 through the
// Vector_base body pinned at 0x00211E58, then parses the block through the
// member pinned at 0x004289B8. Single EH state from the vector member.
// The parser destructor is unrowed so it stays declared-only here; the
// VersionDestructor TU keeps the buffer model that the rowed inner
// destructor (0x002385FF) verifies against.
#include <vector>

// Retail stores 0x18-byte records with the key string at +0 and the value
// string at +0xC (VersionBlockSearch TU); spelled for readability, the
// constructor only needs the extent.
struct VersionBlockEntry
{
	const char *m_key; // +0
	char m_padAfterKey[8]; // +4, contents unproven
	const char *m_value; // +0xC
	char m_padTail[8]; // +0x10, contents unproven
};

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
	~VersionBlockParser();
private:
	int m_unk0;
	_STL::vector<VersionBlockEntry> m_records;
	void parse(const char *versionBlock);
};

VersionBlockParser::VersionBlockParser(const char *versionBlock)
	: m_unk0(0), m_records()
{
	parse(versionBlock);
}
