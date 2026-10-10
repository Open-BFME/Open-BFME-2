// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native319924..31996D RET4. Same8B registry records as rowed40DB0E,
// reached through outer+78. The rowed40CB2C getter returns the second
// record word, which native dereferences as an entry with AsciiString+4.
// The count/equality role and these offsets are target facts. Original
// class and method identifiers remain unknown; address names are retained.
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

class Rva0040CB2CIndexedField {
public:
 int get(int index) const;
 char prefix[0x40];
 _STL::vector<Rva0040DB0ERecord> records;
};
class Rva00319924 {
public:
 int count(const AsciiString& name);
 char prefix[0x78];
 Rva0040CB2CIndexedField *registry;
};
int Rva00319924::count(const AsciiString&name) {
 int count=0;
 for(int i=0;i<(int)registry->records.size();++i) {
  Rva0040DB0EEntry*entry=(Rva0040DB0EEntry*)registry->get(i);
  if(entry->m_name.compare(name)==0) ++count;
 }
 return count;
}
