// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// STLport red-black tree erase and clear bodies whose node value has a
// destructor, one pair per tree instantiation. These are the
// RvaTreeEraseClearFamily.cpp shapes plus a value destructor call on the
// node's +0x10 payload before free. The 53-byte erase walks left, recursing
// on the right subtree. The 41-byte clear erases from the root when the
// count is non-zero and resets the header links. Six trees share the value
// destructor 0x002046BB (pinned). Which trees they are is not recovered, so
// owners are named after their erase's address.

extern "C" void __cdecl free(void *block);

struct Rva002046BBValue
{
	~Rva002046BBValue();
	int m_00;
};

struct RvaTreeValueNode
{
	char m_pad[8];				// +0x00
	RvaTreeValueNode *m_left;	// +0x08
	RvaTreeValueNode *m_right;	// +0x0C
	Rva002046BBValue m_value;	// +0x10
};

struct RvaTreeValueHead
{
	char m_pad00[4];			// +0x00
	RvaTreeValueNode *m_root;	// +0x04
	RvaTreeValueHead *m_left;	// +0x08
	RvaTreeValueHead *m_right;	// +0x0C
};

#define RVA_TREE_VALUE_FAMILY( OWNER, ERASE, CLEAR )                       \
	class OWNER                                                           \
	{                                                                     \
	public:                                                               \
		void ERASE(RvaTreeValueNode *node);                               \
		void CLEAR();                                                     \
		RvaTreeValueHead *head() { return m_head; } /* +0 accessor for owner dtors */ \
	private:                                                              \
		RvaTreeValueHead *m_head;	/* +0x00 */                          \
		int m_count;				/* +0x04 */                          \
	};                                                                    \
	void OWNER::ERASE(RvaTreeValueNode *node)                             \
	{                                                                     \
		while (node)                                                      \
		{                                                                 \
			ERASE(node->m_right);                                         \
			RvaTreeValueNode *next = node->m_left;                        \
			node->m_value.~Rva002046BBValue();                            \
			free(node);                                                   \
			node = next;                                                  \
		}                                                                 \
	}                                                                     \
	void OWNER::CLEAR()                                                   \
	{                                                                     \
		if (m_count != 0)                                                 \
		{                                                                 \
			ERASE(m_head->m_root);                                        \
			m_head->m_left = m_head;                                      \
			m_head->m_root = 0;                                           \
			m_head->m_right = m_head;                                     \
			m_count = 0;                                                  \
		}                                                                 \
	}

// erase 0x00206593 (53B), clear 0x00206EC7 (41B)
RVA_TREE_VALUE_FAMILY( Rva00206593, rva00206593, rva00206EC7 )
// erase 0x002065C8, clear 0x00206EF0
RVA_TREE_VALUE_FAMILY( Rva002065C8, rva002065C8, rva00206EF0 )
// erase 0x002065FD, clear 0x00206F19
RVA_TREE_VALUE_FAMILY( Rva002065FD, rva002065FD, rva00206F19 )
// erase 0x00206632, clear 0x00206F42
RVA_TREE_VALUE_FAMILY( Rva00206632, rva00206632, rva00206F42 )
// erase 0x0020669C, clear 0x00206F94
RVA_TREE_VALUE_FAMILY( Rva0020669C, rva0020669C, rva00206F94 )
// erase 0x002066D1, clear 0x00206FBD
RVA_TREE_VALUE_FAMILY( Rva002066D1, rva002066D1, rva00206FBD )

// Three more trees with the same shapes over other value types, whose
// destructors are already pinned under these address names.
#define RVA_TREE_VALUE_FAMILY_T( VALUE, OWNER, ERASE, CLEAR )               \
	struct VALUE                                                          \
	{                                                                     \
		~VALUE();                                                         \
		int m_00;                                                         \
	};                                                                    \
	struct OWNER##Node                                                    \
	{                                                                     \
		char m_pad[8];                                                    \
		OWNER##Node *m_left;                                              \
		OWNER##Node *m_right;                                             \
		VALUE m_value;                                                    \
	};                                                                    \
	struct OWNER##Head                                                    \
	{                                                                     \
		char m_pad00[4];                                                  \
		OWNER##Node *m_root;                                              \
		OWNER##Head *m_left;                                              \
		OWNER##Head *m_right;                                             \
	};                                                                    \
	class OWNER                                                           \
	{                                                                     \
	public:                                                               \
		void ERASE(OWNER##Node *node);                                    \
		void CLEAR();                                                     \
	private:                                                              \
		OWNER##Head *m_head;                                              \
		int m_count;                                                      \
	};                                                                    \
	void OWNER::ERASE(OWNER##Node *node)                                  \
	{                                                                     \
		while (node)                                                      \
		{                                                                 \
			ERASE(node->m_right);                                         \
			OWNER##Node *next = node->m_left;                             \
			node->m_value.~VALUE();                                       \
			free(node);                                                   \
			node = next;                                                  \
		}                                                                 \
	}                                                                     \
	void OWNER::CLEAR()                                                   \
	{                                                                     \
		if (m_count != 0)                                                 \
		{                                                                 \
			ERASE(m_head->m_root);                                        \
			m_head->m_left = m_head;                                      \
			m_head->m_root = 0;                                           \
			m_head->m_right = m_head;                                     \
			m_count = 0;                                                  \
		}                                                                 \
	}

// erase 0x004D9B4B, clear 0x004D9FF2, value dtor 0x004D960C
RVA_TREE_VALUE_FAMILY_T( Rva004D960C, Rva004D9B4B, rva004D9B4B, rva004D9FF2 )
// erase 0x00501F2D, clear 0x0050247A, value dtor 0x005011B4
RVA_TREE_VALUE_FAMILY_T( Rva005011B4, Rva00501F2D, rva00501F2D, rva0050247A )
// erase 0x0060421C, clear 0x0060434B, value dtor 0x00603C57
RVA_TREE_VALUE_FAMILY_T( Rva00603C57, Rva0060421C, rva0060421C, rva0060434B )

// Map-base dtors (56B each, /GX frame): the six 5B novtable jmp stubs in
// Rva00207BDAMapDtors.cpp (0x00207BDA->0x002075F3, 0x00207BDF->0x00207630,
// 0x00207BE4->0x0020766D, 0x00207BE9->0x002076AA, 0x00207BF3->0x00207724,
// 0x00207BF8->0x00207761) target these bodies as their Map bases, so each
// body below is the owner dtor over the matching tree instantiation:
// CLEAR() on the +0 tree, then a null-guarded free of the head at +0.
// The __EH_prolog frame plus the single and/or [ebp-4] state pair is the
// /GX shape (same as rowed 0x001F077D: or-state--1). A no-member model was
// refuted: without an unwindable member MSVC emits no frame (22B flat).
// The frame therefore comes from the inline-dtor holder at +0 whose
// teardown (null-checked free) the compiler inlines; the +4 count slot is
// what CLEAR() reads. (An earlier delete-spelling was refuted: retail calls
// the 0x00030830 free, like ERASE and rowed 0x001F077D.)
struct RvaTreeHeadHolder
{
	RvaTreeValueHead *m_head;
	~RvaTreeHeadHolder()
	{
		if (m_head)
			free(m_head);
	}
};
class Rva002075F3
{
public:
	~Rva002075F3();
private:
	RvaTreeHeadHolder m_holder;	/* +0x00, layout-shared with the tree head */
	int m_count;				/* +0x04, the slot CLEAR() tests */
};
Rva002075F3::~Rva002075F3()
{
	reinterpret_cast<Rva00206593 *>(this)->rva00206EC7();
}
// Five siblings, byte-identical but for the CLEAR callee (decoded above):
// 0x00207630->0x00206EF0, 0x0020766D->0x00206F19, 0x002076AA->0x00206F42,
// 0x00207724->0x00206F94, 0x00207761->0x00206FBD.
class Rva00207630
{
public:
	~Rva00207630();
private:
	RvaTreeHeadHolder m_holder;
	int m_count;
};
Rva00207630::~Rva00207630()
{
	reinterpret_cast<Rva002065C8 *>(this)->rva00206EF0();
}
class Rva0020766D
{
public:
	~Rva0020766D();
private:
	RvaTreeHeadHolder m_holder;
	int m_count;
};
Rva0020766D::~Rva0020766D()
{
	reinterpret_cast<Rva002065FD *>(this)->rva00206F19();
}
class Rva002076AA
{
public:
	~Rva002076AA();
private:
	RvaTreeHeadHolder m_holder;
	int m_count;
};
Rva002076AA::~Rva002076AA()
{
	reinterpret_cast<Rva00206632 *>(this)->rva00206F42();
}
class Rva00207724
{
public:
	~Rva00207724();
private:
	RvaTreeHeadHolder m_holder;
	int m_count;
};
Rva00207724::~Rva00207724()
{
	reinterpret_cast<Rva0020669C *>(this)->rva00206F94();
}
class Rva00207761
{
public:
	~Rva00207761();
private:
	RvaTreeHeadHolder m_holder;
	int m_count;
};
Rva00207761::~Rva00207761()
{
	reinterpret_cast<Rva002066D1 *>(this)->rva00206FBD();
}
// ??1Rva005026B6@@QAE@XZ, retail 0x005026B6 56B.
// Map-base dtor over tree Rva00501F2D (CLEAR 0x0050247A), same 56B /GX shape
// as the six siblings above: CLEAR() on the +0 tree then null-guarded free
// of the head via RvaTreeHeadHolder. Evidence: 56B __EH_prolog frame with
// CLEAR callee 0x0050247A and free 0x00030830; callers at 0x00502952 and
// jmp stub at 0x00502926; neighbours share stlport map context.
class Rva005026B6
{
public:
	~Rva005026B6();
private:
	RvaTreeHeadHolder m_holder;	/* +0x00, layout-shared with the tree head */
	int m_count;				/* +0x04, the slot CLEAR() tests */
};
Rva005026B6::~Rva005026B6()
{
	reinterpret_cast<Rva00501F2D *>(this)->rva0050247A();
}
// ??1Rva0050298D@@QAE@XZ, retail 0x0050298D 56B.
// Map-base dtor over tree Rva00502787 (CLEAR 0x00502787), same 56B /GX shape
// as Rva005026B6 above: CLEAR() on the +0 tree then null-guarded free
// of the head via RvaTreeHeadHolder. Evidence: 56B __EH_prolog frame with
// CLEAR callee 0x00502787 and free 0x00030830; callers at 0x00502D2A and
// jmp stub at 0x00502CFE; neighbours share stlport map context.
struct Rva00502787
{
	void rva00502787();
};
class Rva0050298D
{
public:
	~Rva0050298D();
private:
	RvaTreeHeadHolder m_holder;	/* +0x00, layout-shared with the tree head */
	int m_count;				/* +0x04, the slot CLEAR() tests */
};
Rva0050298D::~Rva0050298D()
{
	reinterpret_cast<Rva00502787 *>(this)->rva00502787();
}

class Rva0020762B
{
public:
	void rva0020762B();
};

void Rva0020762B::rva0020762B()
{
	reinterpret_cast<Rva002065C8 *>(this)->rva00206EF0();
}

class Rva00207668
{
public:
	void rva00207668();
};

void Rva00207668::rva00207668()
{
	reinterpret_cast<Rva002065FD *>(this)->rva00206F19();
}

class Rva002076A5
{
public:
	void rva002076A5();
};

void Rva002076A5::rva002076A5()
{
	reinterpret_cast<Rva00206632 *>(this)->rva00206F42();
}

class Rva0020771F
{
public:
	void rva0020771F();
};

void Rva0020771F::rva0020771F()
{
	reinterpret_cast<Rva0020669C *>(this)->rva00206F94();
}

class Rva0020775C
{
public:
	void rva0020775C();
};

void Rva0020775C::rva0020775C()
{
	reinterpret_cast<Rva002066D1 *>(this)->rva00206FBD();
}

class Rva005026B1
{
public:
	void rva005026B1();
};

void Rva005026B1::rva005026B1()
{
	reinterpret_cast<Rva00501F2D *>(this)->rva0050247A();
}

class Rva00502926
{
public:
	void rva00502926();
};

void Rva00502926::rva00502926()
{
	reinterpret_cast<Rva005026B6 *>(this)->~Rva005026B6();
}
