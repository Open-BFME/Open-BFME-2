// ?rva00149A90@Rva00149A90Obj@@QAE_NPAV1@@Z
// partial score=0.6 date=2026-10-08
// cl: /MD
// ?rva00149A90@Rva00149A90Obj@@QAE_NPAV1@@Z @0x00149A90 280B: both objects need a
// node at +0xC4 whose sub-object has +0xB8 or +0x108 set; the +0xC8 links must agree
// on null-ness and the linked one must pass 0x0013F8D0; then the two vector
// queries via 0x00149280 compare component-wise and the float virtual 0x64 compare.
class Rva00149A90Vec
{
public:
	float x;
	float y;
	float z;
};

class Rva00149A90Sub
{
public:
	char m_pad0[0xB8];
	int m_B8;
	char m_padBC[0x108 - 0xBC];
	int m_108;
};

class Rva00149A90Node
{
public:
	char m_pad0[0x94];
	Rva00149A90Sub *m_94;
};

bool __stdcall Rva0013F8D0(void *p);

class Rva00149A90Obj
{
public:
	virtual void rva00149A90V00();
	virtual void rva00149A90V01();
	virtual void rva00149A90V02();
	virtual void rva00149A90V03();
	virtual void rva00149A90V04();
	virtual void rva00149A90V05();
	virtual void rva00149A90V06();
	virtual void rva00149A90V07();
	virtual void rva00149A90V08();
	virtual void rva00149A90V09();
	virtual void rva00149A90V10();
	virtual void rva00149A90V11();
	virtual void rva00149A90V12();
	virtual void rva00149A90V13();
	virtual void rva00149A90V14();
	virtual void rva00149A90V15();
	virtual void rva00149A90V16();
	virtual void rva00149A90V17();
	virtual void rva00149A90V18();
	virtual void rva00149A90V19();
	virtual void rva00149A90V20();
	virtual void rva00149A90V21();
	virtual void rva00149A90V22();
	virtual void rva00149A90V23();
	virtual void rva00149A90V24();
	virtual float rva00149A90Float();
	bool rva00149A90(Rva00149A90Obj *other);
	Rva00149A90Vec *rva00149280(Rva00149A90Vec &out);

private:
	char m_padVptr[0xC4 - 4];
	Rva00149A90Node *m_C4;
	Rva00149A90Obj *m_C8;
};

// ?rva00149A90@Rva00149A90Obj@@QAE_NPAV1@@Z @0x00149A90
bool Rva00149A90Obj::rva00149A90(Rva00149A90Obj *other)
{
	if (m_C4 == 0)
		return false;
	if (m_C4->m_94->m_B8 == 0 && m_C4->m_94->m_108 == 0)
		return false;
	if (other->m_C4 == 0)
		return false;
	if (other->m_C4->m_94->m_B8 == 0 && other->m_C4->m_94->m_108 == 0)
		return false;
	if ((m_C8 == 0) != (other->m_C8 == 0))
		return false;
	if (m_C8 != 0 && !Rva0013F8D0(other->m_C8))
		return false;
	Rva00149A90Vec tmpOther;
	Rva00149A90Vec *pOther = other->rva00149280(tmpOther);
	Rva00149A90Vec tmpThis;
	Rva00149A90Vec *pThis = rva00149280(tmpThis);
	if (pThis->x != pOther->x)
		return false;
	if (pThis->y != pOther->y)
		return false;
	if (pThis->z != pOther->z)
		return false;
	float fThis = rva00149A90Float();
	float fOther = other->rva00149A90Float();
	if (fThis != fOther)
		return false;
	return true;
}
