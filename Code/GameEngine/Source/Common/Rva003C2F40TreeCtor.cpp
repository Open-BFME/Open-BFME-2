// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME: ??0Rva003C2F40Owner@@QAE@XZ at retail 0x003C2F40; the row was
// repointed off the ?d_003c2f40 dump name and the header marker never followed.
// The body is the EH-framed construction of the red-black header embedded at
// +0x0c.  Its vtable and the two preceding scalar members are established by
// the surrounding VNI construction path; this constructor only runs the tree
// member's initialization.

// stlport
#define _STLP_USE_STATIC_LIB 1
#include <memory>

struct Rva003C2F40Node
{
	char m_color;
	int *m_parent;
	Rva003C2F40Node *m_left;
	Rva003C2F40Node *m_right;
};
struct Rva003C2F40Tree
{
	Rva003C2F40Node *m_header;
	int m_count;

	Rva003C2F40Tree();
};

// ??0Rva003C2F40Tree@@QAE@XZ is called OUT OF LINE from the owner ctor -- its
// REL32 at 0x002BAE75 lands on 0x005011C1 -- so it must not be inlined here.
// The definition itself is not placed in this TU.

class Rva003C2F40Base
{
public:
	Rva003C2F40Base();
	virtual ~Rva003C2F40Base();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

// ??0Rva003C2F40Base@@QAE@XZ absent-from-retail (empty scaffold base, emits no code)
Rva003C2F40Base::Rva003C2F40Base()
{
}

class Rva003C2F40Owner : public Rva003C2F40Base
{
public:
	Rva003C2F40Owner();
	virtual ~Rva003C2F40Owner();
	Rva003C2F40Tree m_tree;
};
// ??0Rva003C2F40Owner@@QAE@XZ
Rva003C2F40Owner::Rva003C2F40Owner()
{
}
