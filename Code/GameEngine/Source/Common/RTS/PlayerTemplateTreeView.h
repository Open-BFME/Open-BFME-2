// TU-scoped tree view shared by the existing erase/clear, assignment and
// destructor owners. The matched bodies establish the pointer at +0 and count
// at +4. Keep the destructor donor's header handle: it supplies retail's EH
// cleanup when clear throws. This does not establish an original class name.
#ifndef BFME_PLAYER_TEMPLATE_TREE_VIEW_H
#define BFME_PLAYER_TEMPLATE_TREE_VIEW_H

// Retail treats the game allocator's free as throwing in these destructors: they
// keep the unwind state store before it. A declaration in its own namespace carries
// throw(...) under /EHsc and leaves the unit's other calls to free as they are.
namespace PlayerTemplateTree { extern "C" void __cdecl free(void *block) throw(...); }

struct Rva001FD42BNode
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD42BNode *m_parent;
	Rva001FD42BNode *m_left;
	Rva001FD42BNode *m_right;
	unsigned char m_value[8];
};

struct Rva001FD42BHeaderHandle
{
	~Rva001FD42BHeaderHandle()
	{
		if (m_header)
			PlayerTemplateTree::free(m_header);
	}
	Rva001FD42BNode *m_header;
};

struct Rva001FD42B
{
	void rva001FD42B(Rva001FD42BNode *x);
	void rva001FD630();
	Rva001FD42B *rva001FD8DF(const Rva001FD42B &other);
	~Rva001FD42B();
	Rva001FD42BHeaderHandle m_handle;
	unsigned int m_count;
};

struct Rva001FD458Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD458Node *m_parent;
	Rva001FD458Node *m_left;
	Rva001FD458Node *m_right;
	unsigned char m_value[8];
};

struct Rva001FD458HeaderHandle
{
	~Rva001FD458HeaderHandle()
	{
		if (m_header)
			PlayerTemplateTree::free(m_header);
	}
	Rva001FD458Node *m_header;
};

struct Rva001FD458
{
	void rva001FD458(Rva001FD458Node *x);
	void rva001FD659();
	Rva001FD458 *rva001FD952(const Rva001FD458 &other);
	~Rva001FD458();
	Rva001FD458HeaderHandle m_handle;
	unsigned int m_count;
};

#endif
