// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
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
