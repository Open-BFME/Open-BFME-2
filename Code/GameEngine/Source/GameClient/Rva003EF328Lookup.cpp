// cl: /DNDEBUG /MD
//
// ?rva003EF328@Rva003EF328@@QAEPAXPBVAsciiString@@@Z @0x003EF328 34B, dump
// range 18. Looks up the AsciiString key in the Rva00056F61 bucket table at
// this+0x0C through the rowed 0x0041534B find (which returns its 8-byte
// iterator by value, hence the hidden return buffer as the second push);
// null node yields null, else the payload at node+8. Layout after the
// Rva00056F61IterFind.cpp home TU; the +0x0C adjustment is retail's own
// add ecx idiom.
class AsciiString;
class Rva00056F61;

struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva003EF328
{
public:
	void *rva003EF328(const AsciiString *key);
private:
	char m_pad[0x0C];
	Rva00056F61 m_table0C;
};

void *Rva003EF328::rva003EF328(const AsciiString *key)
{
	Rva0041534BIter it = m_table0C.rva0041534B(key);
	if (it.m_node == 0)
		return 0;
	return *(void **)((char *)it.m_node + 8);
}
