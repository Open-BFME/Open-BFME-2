// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ?rva002BBBE7@Rva002BBBE7@@QAEXPAUNode002BBBE7@@@Z @0x002BBBE7 53B.
// Recursive list clear: recurse child at +0xC, destroy Rva002B923F at
// +0x10 via rowed dtor, free node, iterate next at +8.
// Evidence: chain lane; callees rowed 0x002B923F plus _free 0x00030830;
// self-recursive call; caller at 0x002BC3AB; unblocks 0x002BC39D.
extern "C" void __cdecl free(void *block);

class Rva002B923F
{
public:
	~Rva002B923F();
private:
	char m_pad[0x18];
};

struct Node002BBBE7 {
	char m_pad00[8];
	Node002BBBE7 *m_next08;
	Node002BBBE7 *m_child0C;
	Rva002B923F m_obj10;
};

class Rva002BBBE7
{
public:
	void rva002BBBE7(Node002BBBE7 *n);
};

void Rva002BBBE7::rva002BBBE7(Node002BBBE7 *n)
{
	if (n == 0)
		return;
	for (Node002BBBE7 *cur = n; cur != 0;) {
		rva002BBBE7(cur->m_child0C);
		Node002BBBE7 *next = cur->m_next08;
		cur->m_obj10.~Rva002B923F();
		free(cur);
		cur = next;
	}
}
