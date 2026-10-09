// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0040DB0E@Rva0040DB0ERegistry@@QAEHABVAsciiString@@@Z, retail 0x0040DB0E (68 bytes, ret 4). Owner and
// element type are unproven (address token): how many of the 8-byte (key, entry) records at +0x40/+0x44
// hold an entry whose AsciiString at +0x04 equals the argument. WorldBuilder twin 0x0108BA90 is unnamed.
#include <vector>
#include "ascii_string.h"

struct Rva0040DB0EEntry
{
	char m_pad00[4];
	AsciiString m_name;		// +0x04
};

struct Rva0040DB0ERecord
{
	int m_key;
	Rva0040DB0EEntry *m_entry;
};

class Rva0040DB0ERegistry
{
public:
	int rva0040DB0E(const AsciiString &name);
private:
	char m_pad00[0x40];
	_STL::vector<Rva0040DB0ERecord> m_records;	// +0x40
};

int Rva0040DB0ERegistry::rva0040DB0E(const AsciiString &name)
{
	int count = 0;
	for (int i = 0; i < (int)m_records.size(); ++i) {
		Rva0040DB0EEntry *entry = m_records[i].m_entry;
		if (entry->m_name.compare(name) == 0)
			++count;
	}
	return count;
}
