// cl: /MD
// ?rva005297A0@Rva0052936C@@QAEXPBD@Z @0x005297A0 61B evidence: chain on 0x00529628 GetParam index atoi 0-5; array base +0x64 stride 0x14 count 6 like dtor 0x0052936C; clears via rowed 0x002BED91 plus 0x000AD6F4 plus null +0x10
struct Rva000AD6F4
{
	void *m_ptr;
	void clear();
};

struct Rva002BED91
{
	void *m_ptr;
	void clear();
};

struct Rva00528FE6
{
	void rva00529009();
	void *m_ptr;
};

struct Rva005297A0Elem
{
	Rva000AD6F4 m_a0;
	Rva000AD6F4 m_a4;
	Rva00528FE6 m_mid08;
	Rva002BED91 m_b;
	int m_c;
};

class Rva0052936C
{
public:
	void rva005297A0(const char *section);
	void rva005298E0(const char *section);
	void rva00529A21(const char *section);
private:
	char m_pad00[0x64];
	Rva005297A0Elem m_elems[6];
};

bool __cdecl Rva00529628Get(const char *section, int *out);

void Rva0052936C::rva005297A0(const char *section)
{
	int index;
	if (!Rva00529628Get(section, &index))
		return;
	Rva005297A0Elem &e = m_elems[index];
	e.m_b.clear();
	e.m_c = 0;
	e.m_a0.clear();
}

void Rva0052936C::rva005298E0(const char *section)
{
	int index;
	if (!Rva00529628Get(section, &index))
		return;
	Rva005297A0Elem &e = m_elems[index];
	e.m_b.clear();
	e.m_c = 0;
	e.m_a4.clear();
}

void Rva0052936C::rva00529A21(const char *section)
{
	int index;
	if (!Rva00529628Get(section, &index))
		return;
	Rva005297A0Elem &e = m_elems[index];
	e.m_b.clear();
	e.m_c = 0;
	e.m_mid08.rva00529009();
}
