// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva0022CA95@@MAE@XZ, retail 0x002149AA..0x00214A6E (196 bytes, EH): the
// AttributeModifier store's destructor (constructor 0x0022CA95, table
// 0x00BE5348, slot-0 scalar deleting destructor 0x00214A6E; its slots 4 and
// 5 are the RIF reload notices in ReloadIniFileNotices.cpp). It deletes
// every entry of its two pointer vectors at +0xC and +0x18 by index (entry
// destructor rowed 0x004043FF); then both vectors' storage goes to GameFree
// (unwind copies 0x0007FAB3) and SubsystemInterface dies last. The vectors
// are spelled with their entry pointer type: vector<void *>'s out-of-line
// destructor is the /Od body 0x00027370, not that unwind copy.
#include <vector>

class Rva002146F7;
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<Rva002146F7 *, allocator<Rva002146F7 *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
}

// Use the same proven twelve-byte subsystem base as the constructor.
typedef bool Bool;
#include "subsystem_interface.h"

struct Rva00214B22Record;
class AsciiString;
class Rva002146F7
{
public:
	~Rva002146F7();
private:
	_STL::vector<Rva00214B22Record> m_values; // +0x00
	unsigned m_word0C; // +0x0C
	AsciiString m_name10; // +0x10
	unsigned char m_unreconstructed14[0xCC - 0x14]; // +0x14
	unsigned char *m_storageCC; // +0xCC
	unsigned char m_flagsD0[4]; // +0xD0
};

class Rva0022CA95 : public SubsystemInterface
{
public:
	Rva0022CA95();
protected:
	virtual ~Rva0022CA95();
private:
	_STL::vector<Rva002146F7 *> m_first;	// +0x0C
	_STL::vector<Rva002146F7 *> m_second;	// +0x18
};

Rva0022CA95::~Rva0022CA95()
{
	unsigned int i;
	for (i = 0; i < m_first.size(); ++i)
		delete m_first[i];
	for (i = 0; i < m_second.size(); ++i)
		delete m_second[i];
}
