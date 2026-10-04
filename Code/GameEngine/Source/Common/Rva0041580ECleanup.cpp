// cl: /O1 /MD
// ?rva0041580E@Rva0041580E@@QAEXPAURva0041580ENode@@@Z @0x0041580E 53B chain via rowed ??1Rva0041579E.
// List cleanup recursing on +0xC with same this then destroying +0x10 via rowed
// Rva0041579E dtor and freeing the node, iterating via +8.
// Evidence: self-call at 0x00415820 with [esi+0xC], lea ecx [esi+0x10] call
// rowed 0x004156FC, push esi call rowed _free 0x00030830, loop via [esi+8];
// callers at 0x00415820 (self) 0x00415894; unblocks 0x00415886.
extern "C" void __cdecl free(void *block);

class Rva0041579E
{
public:
	~Rva0041579E();
};

struct Rva0041580ENode
{
	unsigned char m_colour00;
	char m_pad01[3];
	Rva0041580ENode *m_parent04;
	Rva0041580ENode *m_next08;
	Rva0041580ENode *m_child0C;
	Rva0041579E m_item10;
};

struct Rva0041580EHead
{
	int _00;
	Rva0041580ENode *m_first04;
	Rva0041580EHead *m_next08;
	Rva0041580EHead *m_child0C;
};

struct Rva0041580E
{
	Rva0041580EHead *m_head00;
	int m_flag04;
	void rva0041580E(Rva0041580ENode *node);
	void rva00415886();
	Rva0041580E *rva004159E2(const Rva0041580E &other);
	__forceinline Rva0041580ENode *&rootRef() { return m_head00->m_first04; }
	Rva0041580ENode *rva00415937(Rva0041580ENode *source,Rva0041580ENode *parent);
	Rva0041580ENode *rva00415868(const Rva0041580ENode *source);
};

// ?rva00415886@Rva0041580E@@QAEXXZ @0x00415886 41B chain via rowed 0x0041580E.
// Resets list head to empty after cleanup. Evidence: ECX passthrough to rowed
// 0x0041580E at 0x00415894, callers at 0x004159BF 0x004159EE.
void Rva0041580E::rva0041580E(Rva0041580ENode *node)
{
	Rva0041580ENode *cur = node;
	while (cur != 0)
	{
		rva0041580E(cur->m_child0C);
		Rva0041580ENode *next = cur->m_next08;
		cur->m_item10.~Rva0041579E();
		free(cur);
		cur = next;
	}
}

void Rva0041580E::rva00415886()
{
	if (m_flag04 != 0)
	{
		rva0041580E(m_head00->m_first04);
		m_head00->m_next08 = m_head00;
		m_head00->m_first04 = 0;
		m_head00->m_child0C = m_head00;
		m_flag04 = 0;
	}
}

// Target reference repair: STLport 4.5.3 _tree.h _M_create_node semantic guide.
// Native 0x415843/37 requests exactly 0x1E0 raw bytes from rowed byte allocator
// 0x307F0, then calls rowed _Construct<Rva0041579E> at 0x4157E1 on +0x10.
// ECX is never read; ret 4. A stdcall ABI view avoids asserting member identity.
// The allocated block's complete original node/value layout is not claimed.
class Rva0041579E;
namespace _STL {
template<class T> class allocator;
template<> class allocator<char> {
public:
    static char *allocate(unsigned int bytes,const void *hint);
};
template<class T,class U> void _Construct(T *destination,const U &source);
}
char *__stdcall Rva00415843Create(const Rva0041579E &source)
{
    char *storage=_STL::allocator<char>::allocate(0x1E0,0);
    _STL::_Construct<Rva0041579E,Rva0041579E>((Rva0041579E *)(storage+0x10),source);
    return storage;
}

// STLport 4.5.3 _M_clone_node guides this header copy. Native 0x415868/30
// calls the verified create helper with source+0x10, copies its colour byte,
// and clears left/right links. Recursive tree copy forwards its ECX receiver.
// This address-named method records that call protocol; original membership,
// key/value identity and complete node layout are not asserted.
Rva0041580ENode *Rva0041580E::rva00415868(const Rva0041580ENode *source)
{
    Rva0041580ENode *node=(Rva0041580ENode *)Rva00415843Create(source->m_item10);
    node->m_colour00=source->m_colour00;
    node->m_next08=0;
    node->m_child0C=0;
    return node;
}

// STLport 4.5.3 _tree.c _M_copy: clone right subtrees recursively and the
// left spine iteratively. Native 0x415937/115 has no local unwind frame.
Rva0041580ENode *Rva0041580E::rva00415937(Rva0041580ENode *source,Rva0041580ENode *parent)
{
    Rva0041580ENode *top=rva00415868(source);
    top->m_parent04=parent;
    if(source->m_child0C) top->m_child0C=rva00415937(source->m_child0C,top);
    parent=top;
    source=source->m_next08;
    while(source) {
        Rva0041580ENode *node=rva00415868(source);
        parent->m_next08=node;
        node->m_parent04=parent;
        if(source->m_child0C) node->m_child0C=rva00415937(source->m_child0C,node);
        parent=node;
        source=source->m_next08;
    }
    return top;
}

// STLport 4.5.3 _Rb_tree assignment guide. Both header views preserve the
// witnessed common 16-byte prefix; casts below do not assert inheritance.
Rva0041580E *Rva0041580E::rva004159E2(const Rva0041580E &other)
{
    if (this!=&other) {
        rva00415886();
        m_flag04=0;
        if(other.m_head00->m_first04==0) {
            m_head00->m_first04=0;
            m_head00->m_next08=m_head00;
            m_head00->m_child0C=m_head00;
        } else {
            rootRef()=rva00415937(other.m_head00->m_first04,(Rva0041580ENode *)m_head00);
            Rva0041580ENode *cur=m_head00->m_first04;
            while(cur->m_next08) cur=cur->m_next08;
            m_head00->m_next08=(Rva0041580EHead *)cur;
            cur=m_head00->m_first04;
            while(cur->m_child0C) cur=cur->m_child0C;
            m_head00->m_child0C=(Rva0041580EHead *)cur;
            m_flag04=other.m_flag04;
        }
    }
    return this;
}
