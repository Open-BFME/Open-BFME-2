// cl: /MD
//
// ?rva0006E567@Rva0006E567@@QAEXPAVRva0006E567Obj@@H@Z, retail 0x0006E567, 57 bytes.
// __thiscall indexed refcounted-pointer assign: bounds-checks idx+1 against
// dword at +0x160, AddRefs the new pointer (inc +4 if non-null), Releases
// the old slot at +0x150+idx*4 (dec +4, virtual delete via slot 0 if zero),
// then stores. Callers pass varying this; single caller at 0x00046C2F.
// Evidence: AddRef/Release shape, array/count layout, no other callees.
// Honest address names pending real class pin.

class Rva0006E567Obj
{
public:
	virtual void Delete();
	int m_ref;
};

class Rva0006E567
{
public:
	void rva0006E567(Rva0006E567Obj *v, int idx);

private:
	char m_pad0[0x150];
	Rva0006E567Obj *m_arr[4];
	int m_count;
};

void Rva0006E567::rva0006E567(Rva0006E567Obj *v, int idx)
{
	if (m_count < idx + 1)
		return;
	if (v)
		++v->m_ref;
	Rva0006E567Obj *old = m_arr[idx];
	if (old) {
		if (--old->m_ref == 0)
			old->Delete();
	}
	m_arr[idx] = v;
}
