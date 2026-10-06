// cl: /DNDEBUG /MD
//
// ?rva002913EB@Rva002913EB@@QAEXXZ -- retail 0x002913EB, 41 bytes.
// Tree clear: if count at +4 is zero return, else free root at [header+4]
// via rowed Rva0028F662::rva0028F662 at 0x0028F662 with owner in ecx,
// then reset header left to self and parent to 0 and right to self,
// and count to 0. Matches STL _Rb_tree clear shape.
// Evidence: callers at 0x002923BC and 0x00299309 plus dtor at 0x002923A7
// which frees the header after this call, callee row in
// Code/GameEngine/Source/Common/System/Rva0028F662TreeFree.cpp.

struct Rva0028F662Node;
class Rva0028F662
{
public:
	void rva0028F662(Rva0028F662Node *node);
};

struct Rva002913EBNode
{
	int m_color;
	Rva002913EBNode *m_parent;
	Rva002913EBNode *m_left;
	Rva002913EBNode *m_right;
};

class Rva002913EB
{
public:
	void rva002913EB();
private:
	Rva002913EBNode *m_header;
	int m_count;
};

void Rva002913EB::rva002913EB()
{
	if (m_count == 0)
		return;
	Rva002913EBNode *root = m_header->m_parent;
	((Rva0028F662 *)this)->rva0028F662((Rva0028F662Node *)root);
	m_header->m_left = m_header;
	m_header->m_parent = 0;
	m_header->m_right = m_header;
	m_count = 0;
}
