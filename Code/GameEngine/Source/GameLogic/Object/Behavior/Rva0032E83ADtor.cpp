// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0032E83A@@QAE@XZ — RVA 0x0032E83A, 8B.
// Non-virtual dtor destroying a vector<DynamicPortalLink> member at +4
// via tail-jmp to the rowed vector dtor 0x0032E7A3 (alias dup_0032E7A3).
// Evidence: retail add ecx 4 plus jmp; callee notes name true vector dtor
// at 0x004613EB; callers at 0x0032E92F 0x0032EAA1.
#include <vector>

struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink();
};

class Rva0032E83A
{
public:
	~Rva0032E83A();
	char m_pad00[4];
	_STL::vector<DynamicPortalLink, _STL::allocator<DynamicPortalLink> > m_vec04;
};

Rva0032E83A::~Rva0032E83A()
{
}

void Rva0032E83ADelete(Rva0032E83A *p) { delete p; }

// ?rva0032EAA1@Rva0032EAA1@@QAEXPAX@Z — RVA 0x0032EAA1, 53B.
// Rb-tree _M_erase shape: recurse on right (+0xc), iterate left (+8),
// destroy Rva0032E83A value at +0x10 via the rowed dtor, free the node
// via the rowed _free at 0x00030830.
// Evidence: retail push [esi+0xc] plus self-call, mov edi [esi+8],
// lea ecx [esi+0x10] plus call 0x0032E83A, push esi plus call 0x00030830;
// caller at 0x0032EB5E passes the root and re-inits the header.
extern "C" void free(void *p);

struct Rva0032EAA1Node
{
	int m_color;
	Rva0032EAA1Node *m_parent;
	Rva0032EAA1Node *m_left;
	Rva0032EAA1Node *m_right;
	Rva0032E83A m_value;
};

class Rva0032EAA1
{
public:
	void rva0032EAA1(void *p);
	void rva0032EB5E();
	Rva0032EAA1Node *m_header;
	int m_count;
};

void Rva0032EAA1::rva0032EAA1(void *p)
{
	Rva0032EAA1Node *cur = (Rva0032EAA1Node *)p;
	while (cur != 0) {
		rva0032EAA1(cur->m_right);
		Rva0032EAA1Node *left = cur->m_left;
		cur->m_value.~Rva0032E83A();
		free(cur);
		cur = left;
	}
}

// ?rva0032EB5E@Rva0032EAA1@@QAEXXZ — RVA 0x0032EB5E, 41B.
// Clear: if count is zero return, else erase the root at header+4,
// then re-init header left/right to self, root to 0, count to 0.
// Evidence: retail cmp [esi+4] plus call 0x0032EAA1 with [eax+4],
// then mov [eax+8] eax, and [eax+4] 0, mov [eax+0xc] eax, and [esi+4] 0;
// same this as 0x0032EAA1, same TU and flags.
void Rva0032EAA1::rva0032EB5E()
{
	if (m_count == 0)
		return;
	rva0032EAA1(m_header->m_parent);
	m_header->m_left = m_header;
	m_header->m_parent = 0;
	m_header->m_right = m_header;
	m_count = 0;
}
