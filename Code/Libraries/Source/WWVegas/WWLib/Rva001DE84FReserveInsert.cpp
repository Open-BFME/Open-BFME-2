// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001DE84F@Rva001DE556@@QAEPAUInsertResult@@PAU2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x001DE84F 36B reserve-then-insert wrapper.
// Evidence: packet disassembly; callees pin reserve 0x00212858 rowed insert 0x001DE556; m_size10 at +0x10; callers 0x001DED52 0x001DF518 0x001DF65F 0x001DF787 0x001DF862 0x001DFA20.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "ascii_string.h"

struct NoCaseTreeValue4
{
	char m_body[4];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct HashNode
{
	HashNode *m_next;
	AsciiString m_key;
	NoCaseTreeValue4 m_value;
};

struct InsertResult
{
	HashNode *m_node;
	void *m_table;
	unsigned char m_inserted;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
};

class Rva001DE556
{
public:
	InsertResult *rva001DE556(InsertResult *out, const NocasePair &obj);
	InsertResult *rva001DE84F(InsertResult *out, const NocasePair &obj);
private:
	void *m_00;
	HashNode **m_buckets04;
	void *m_08;
	void *m_0C;
	int m_size10;
};

InsertResult *Rva001DE556::rva001DE84F(InsertResult *out, const NocasePair &obj)
{
	((Rva000427195 *)this)->rva00212858((unsigned int)m_size10 + 1);
	rva001DE556(out, obj);
	return out;
}
