// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva005C8CA0@Rva005C8C73@@QAEPAXPBX@Z @0x005C8CA0 58B.
// STLport float-keyed tree lower_bound, between the rowed Rva005C8C73 erase
// (0x005C8C73) and clear (0x005C8CDA) in RvaTreeEraseClearFamily.cpp. Callers
// 0x005C8D07 and 0x005C8DDF. Header +0x04 root, node +0x08 left / +0x0C right
// / +0x10 float key. The res local is initialized before the head/cur locals
// on purpose: that order is what makes MSVC /O1 rotate the loop to the shared
// bottom test (initial jmp) instead of emitting a duplicate entry test.
struct RvaTreeFamilyNode
{
	char m_pad[8]; // +0x00..0x07
	RvaTreeFamilyNode *m_next; // +0x08
	RvaTreeFamilyNode *m_child; // +0x0C
};

struct RvaTreeFamilyHead
{
	char m_pad00[4]; // +0x00
	RvaTreeFamilyNode *m_first; // +0x04
	RvaTreeFamilyHead *m_next; // +0x08
	RvaTreeFamilyHead *m_child; // +0x0C
};

class Rva005C8C73
{
public:
	void *rva005C8CA0(const void *key);
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

struct Rva005C8CA0Node
{
	char m_pad[8];
	Rva005C8CA0Node *m_left; // +0x08
	Rva005C8CA0Node *m_right; // +0x0C
	float m_key; // +0x10
};

void *Rva005C8C73::rva005C8CA0(const void *key)
{
	Rva005C8CA0Node *res = (Rva005C8CA0Node *)m_00Head;
	RvaTreeFamilyHead *head = (RvaTreeFamilyHead *)m_00Head;
	Rva005C8CA0Node *cur = (Rva005C8CA0Node *)head->m_first;
	const float *kf = (const float *)key;
	while (cur)
	{
		if (!(cur->m_key < *kf)) { res = cur; cur = cur->m_left; }
		else cur = cur->m_right;
	}
	if (res == (Rva005C8CA0Node *)head || res->m_key > *kf) res = (Rva005C8CA0Node *)head;
	return res;
}
