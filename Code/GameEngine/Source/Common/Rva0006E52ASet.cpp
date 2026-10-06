// cl: /MD
//
// ?rva0006E52A@Rva0006E52A@@QAEXPAVRva0006E52AObj@@H@Z, retail 0x0006E52A,
// 61 bytes. __thiscall indexed refcounted-pointer assign with growing
// count: if dword at +0x160 < idx+1, stores idx+1 there; AddRefs new
// (inc +4), Releases old slot at +0x130+idx*4 (dec +4, virtual delete via
// slot 0 if zero), then stores. Sibling of 0x0006E567 (57B, array at
// +0x150 without grow). Single caller at 0x00046C1F. Honest names.

class Rva0006E52AObj
{
public:
	virtual void Delete();
	int m_ref;
};

class Rva0006E52A
{
public:
	void rva0006E52A(Rva0006E52AObj *v, int idx);

private:
	char m_pad0[0x130];
	Rva0006E52AObj *m_arr[12];
	int m_count;
};

void Rva0006E52A::rva0006E52A(Rva0006E52AObj *v, int idx)
{
	if (m_count < idx + 1)
		m_count = idx + 1;
	if (v)
		++v->m_ref;
	Rva0006E52AObj *old = m_arr[idx];
	if (old) {
		if (--old->m_ref == 0)
			old->Delete();
	}
	m_arr[idx] = v;
}
