// cl: /O1 /MD
// Range-34 dump lane: 84B virtual chain at 0x005E7C56 (ret, plain).
// Runs six virtuals on the +0xC member (three int forwards from +0x10/0x14/
// 0x18, a 1/2 flag from +0x20, the outer for slot 4, then a bool slot 0
// check) and tails to pinned 0x005E789A on true. All identities unproven
// (address-derived).
class Rva005E7C56;

class Rva005E7C56Inner
{
public:
	virtual bool v00();
	virtual void v04(Rva005E7C56 *outer);
	virtual void v08();
	virtual void v0C(int v);
	virtual void v10();
	virtual void v14(int v);
	virtual void v18();
	virtual void v1C(int v);
	virtual void v20();
	virtual void v24(int v);
};

class Rva005E7C56
{
public:
	char m_pad[0x0C];
	Rva005E7C56Inner *m0C;
	int m10;
	int m14;
	int m18;
	char m_pad1C[4];
	unsigned char m20;
	void rva005E7C56();
	void tail005E789A();
};

void Rva005E7C56::rva005E7C56()
{
	Rva005E7C56Inner *inner = m0C;
	inner->v0C(m10);
	inner->v14(m14);
	inner->v1C(m18);
	inner->v24(m20 != 0 ? 2 : 1);
	inner->v04(this);
	if (!inner->v00())
		return;
	tail005E789A();
}
