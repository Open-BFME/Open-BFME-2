// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// Target Ghidra [0x001EAD69,0x001EADD4),107B. This body consumes an
// INI pointer and an owner pointer, reads through the independently rowed
// getNextAsciiString233, builds an8B pair of strings with only the first
// assigned, and pushes it onto the list at owner+0x138.
// Native callers/registration, original owner/name and additional unused
// parameters remain unproved. The C++ function exposes only the consumed
// cdecl argument prefix; no original callback signature is claimed.
// Entry fields0/4 and ownership are independently established by the full
// rowed53B two-string destructor at1EA443 and canonical AsciiString operations.
// Full rowed28B push_front at1EA994 establishes the container call ABI;
// only its address is consumed by the owner view, not the owner's total size.
#include "ascii_string.h"
class INI {public:AsciiString getNextAsciiString();};
struct Rva001EAD69Entry {AsciiString text;AsciiString unknown;~Rva001EAD69Entry();};
typedef char EntrySizeIsEight[sizeof(Rva001EAD69Entry)==8?1:-1];
class Rva001EAD69List {public:void push_front(const Rva001EAD69Entry&);};
struct Rva001EAD69Owner {unsigned char unknown[0x138];Rva001EAD69List entries;};
void parseStringEntryRva001EAD69(INI*ini,Rva001EAD69Owner*owner) {
 AsciiString text=ini->getNextAsciiString();
 Rva001EAD69Entry entry;
 entry.text=text;
 owner->entries.push_front(entry);
}

#pragma comment(linker, "/alternatename:??1Rva001EAD69Entry@@QAE@XZ=??1Rva001EA443@@QAE@XZ")

#pragma comment(linker, "/alternatename:?push_front@Rva001EAD69List@@QAEXABURva001EAD69Entry@@@Z=?push_front@?$list@UBfmeStringRecord001EA478@@V?$allocator@UBfmeStringRecord001EA478@@@_STL@@@_STL@@QAEXABUBfmeStringRecord001EA478@@@Z")
