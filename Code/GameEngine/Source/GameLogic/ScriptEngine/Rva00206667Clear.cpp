// cl: /EHsc
// ?rva00206667@Rva00206667@@QAEXPAURva00206667Node@@@Z @0x00206667 53B thiscall recursive clear over child +0x0C with iteration over next +0x08 clearing value +0x10 via rowed StringBase clear 0x0048BA39 then free 0x00030830.
// Evidence: unlock lane every callee rowed; same 53B shape as 0x00206706; self-call plus caller 0x00206F79.
template <typename T>
class StringBase
{
public:
	void clear();
};

struct Rva00206667Node
{
	char m_pad[8];
	Rva00206667Node *m_next; // +0x08
	Rva00206667Node *m_child; // +0x0C
	StringBase<char> m_value; // +0x10
};

struct Rva00206667Head;

class Rva00206667
{
public:
	void rva00206667(Rva00206667Node *node);
	__declspec(noinline) void rva00206F6B();

private:
	Rva00206667Head *m_head; // +0x00
	int m_count; // +0x04
};

extern "C" void __cdecl free(void *block);

void Rva00206667::rva00206667(Rva00206667Node *node)
{
	if (!node)
		return;
	for (Rva00206667Node *cur = node; cur;) {
		rva00206667(cur->m_child);
		Rva00206667Node *next = cur->m_next;
		cur->m_value.clear();
		free(cur);
		cur = next;
	}
}

struct Rva00206667Head
{
	char m_pad[4];
	Rva00206667Node *m_first; // +0x04
	Rva00206667Head *m_link8; // +0x08
	Rva00206667Head *m_linkC; // +0x0C
};

void Rva00206667::rva00206F6B()
{
	if (m_count == 0)
		return;
	rva00206667(m_head->m_first);
	m_head->m_link8 = m_head;
	m_head->m_first = 0;
	m_head->m_linkC = m_head;
	m_count = 0;
}

// Native 0x002076E2..0x002076E7 passes the unchanged receiver to the
// recovered tree clear at 0x00206F6B. Original outer identity is unknown.
class Rva002076E2TreeClearForward { public: void cleanup(); };
void Rva002076E2TreeClearForward::cleanup()
{
 reinterpret_cast<Rva00206667 *>(this)->rva00206F6B();
}
