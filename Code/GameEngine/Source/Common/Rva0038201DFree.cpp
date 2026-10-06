// cl: /MD /EHsc
// ?rva0038201D@Rva0038201D@@QAEXPAURva0038201DNode@@@Z 0x0038201D 45B
// Frees sibling-child tree: recurse child at +12, free self, step next at +8.
// Evidence: self-call plus _free at 0x30830; caller 0x003828B6 passes [eax+4].
extern "C" void __cdecl free(void* block);

struct Rva0038201DNode
{
	int m0;
	Rva0038201DNode* m_first;
	Rva0038201DNode* m_next;
	Rva0038201DNode* m_child;
};

class Rva0038201D
{
	Rva0038201DNode* m_head;
	int m_count;
public:
	void rva0038201D(Rva0038201DNode* n);
	void rva003828B6();
};

void Rva0038201D::rva0038201D(Rva0038201DNode* n)
{
	Rva0038201DNode* cur = n;
	if (!cur)
		return;
	do {
		rva0038201D(cur->m_child);
		Rva0038201DNode* next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0038201D::rva003828B6()
{
	if (m_count == 0)
		return;
	rva0038201D(m_head->m_first);
	m_head->m_next = m_head;
	m_head->m_first = 0;
	m_head->m_child = m_head;
	m_count = 0;
}

class Rva0038204A
{
	Rva0038201DNode* m_head;
	int m_count;
public:
	void rva0038204A(Rva0038201DNode* n);
	void rva003828DF();
};

void Rva0038204A::rva0038204A(Rva0038201DNode* n)
{
	Rva0038201DNode* cur = n;
	if (!cur)
		return;
	do {
		rva0038204A(cur->m_child);
		Rva0038201DNode* next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva0038204A::rva003828DF()
{
	if (m_count == 0)
		return;
	rva0038204A(m_head->m_first);
	m_head->m_next = m_head;
	m_head->m_first = 0;
	m_head->m_child = m_head;
	m_count = 0;
}

class Rva00382077
{
	Rva0038201DNode* m_head;
	int m_count;
public:
	void rva00382077(Rva0038201DNode* n);
	void rva00382908();
};

void Rva00382077::rva00382077(Rva0038201DNode* n)
{
	Rva0038201DNode* cur = n;
	if (!cur)
		return;
	do {
		rva00382077(cur->m_child);
		Rva0038201DNode* next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva00382077::rva00382908()
{
	if (m_count == 0)
		return;
	rva00382077(m_head->m_first);
	m_head->m_next = m_head;
	m_head->m_first = 0;
	m_head->m_child = m_head;
	m_count = 0;
}

class Rva003820A4
{
	Rva0038201DNode* m_head;
	int m_count;
public:
	void rva003820A4(Rva0038201DNode* n);
	void rva00382931();
};

void Rva003820A4::rva003820A4(Rva0038201DNode* n)
{
	Rva0038201DNode* cur = n;
	if (!cur)
		return;
	do {
		rva003820A4(cur->m_child);
		Rva0038201DNode* next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva003820A4::rva00382931()
{
	if (m_count == 0)
		return;
	rva003820A4(m_head->m_first);
	m_head->m_next = m_head;
	m_head->m_first = 0;
	m_head->m_child = m_head;
	m_count = 0;
}

class Rva003820D1
{
	Rva0038201DNode* m_head;
	int m_count;
public:
	void rva003820D1(Rva0038201DNode* n);
	void rva00382983();
};

void Rva003820D1::rva003820D1(Rva0038201DNode* n)
{
	Rva0038201DNode* cur = n;
	if (!cur)
		return;
	do {
		rva003820D1(cur->m_child);
		Rva0038201DNode* next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva003820D1::rva00382983()
{
	if (m_count == 0)
		return;
	rva003820D1(m_head->m_first);
	m_head->m_next = m_head;
	m_head->m_first = 0;
	m_head->m_child = m_head;
	m_count = 0;
}
