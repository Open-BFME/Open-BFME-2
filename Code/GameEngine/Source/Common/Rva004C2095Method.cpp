// cl: /MD
//
// ?rva004C2095@Rva004C2095@@QAE_NXZ @0x004C2095 37B
// Evidence: unlock lane, prev 0x004C2079 next ImmortalBody xfer 0x004C20BA,
// 2 callers (0x004C2130 0x004C2239 caller tests al), callees none direct
// only indirect virtual slot 0x7c, chain [ecx+8]+0x274+0x250 null-checked.
// Identity: honest-address thiscall method returning bool with no args.
class Rva004C2095Callee
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
};

struct Rva004C2095Inner
{
	char m_pad[0x250];
	Rva004C2095Callee *m_callee;
};

struct Rva004C2095Mid
{
	char m_pad[0x274];
	Rva004C2095Inner *m_inner;
};

class Rva004C2095
{
public:
	bool rva004C2095();

private:
	char m_pad[8];
	Rva004C2095Mid *m_mid;
};

bool Rva004C2095::rva004C2095()
{
	Rva004C2095Mid *mid = m_mid;
	if (!mid)
		return false;
	Rva004C2095Inner *inner = mid->m_inner;
	if (!inner)
		return false;
	Rva004C2095Callee *callee = inner->m_callee;
	if (!callee)
		return false;
	callee->v31();
	return false;
}
