// ?rva00319028@Rva00319028@@QAEPAXPAXHH@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva00319028@Rva00319028@@QAEPAXPAXHH@Z, retail 0x00319028, 125 bytes.
// Evidence: leaf packet disasm with rowed gets 0x40CB2C/0x40CC0E plus pinned 0x40CBD7
// plus rowed rva0037DC52/rva0037DCA5 and +0x5c4 compare; caller 0x002BBEED.
class Rva0040CC0EIndexedField
{
public:
	int get(int index) const;
};

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
};

struct Rva00319028VecHead
{
	char *m_begin;
	char *m_end;
};

class Rva0040CBD7Vec
{
public:
	void rva0040CBD7(void **out, int key);
};

class Rva0037DCA5
{
public:
	void *rva0037DC52();
	int rva0037DCA5();
};

class Rva00319028
{
public:
	void *rva00319028(void *out, int a2, int a3);
private:
	char m_pad[0x78];
	Rva0040CBD7Vec *m_78;
};

// ?rva00319028@Rva00319028@@QAEPAXPAXHH@Z present-unmatched
void *Rva00319028::rva00319028(void *out, int a2, int a3)
{
	Rva00319028VecHead *vh = (Rva00319028VecHead *)((char *)m_78 + 0x40);
	int n = (int)(vh->m_end - vh->m_begin) >> 3;
	for (int i = n - 1; i >= 0; --i)
	{
		void *tmpl = ((Rva0037DCA5 *)(int)((Rva0040CB2CIndexedField *)m_78)->get(i))->rva0037DC52();
		if (*(int *)((char *)tmpl + 0x5c4) != a2)
			continue;
		int cost = ((Rva0037DCA5 *)(int)((Rva0040CB2CIndexedField *)m_78)->get(i))->rva0037DCA5();
		if (cost > a3)
			continue;
		int key = ((Rva0040CC0EIndexedField *)m_78)->get(i);
		m_78->rva0040CBD7((void **)out, key);
		return out;
	}
	Rva0040CBD7Vec *v = m_78;
	int key0 = ((Rva0040CC0EIndexedField *)v)->get(0);
	v->rva0040CBD7((void **)out, key0);
	return out;
}
