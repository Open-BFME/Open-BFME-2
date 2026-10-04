// cl: /O1 /MD
// ?rva0042008F@Rva00420110@@QAE_NXZ, retail 0x0042008F, 60 bytes. Vslot 18
// of vtable 0x00C3BA28: if m_86 set or GameInfo slot 0x50 true then false;
// else bounds-check m_68 in [0,20) and tail-call virtual slot 0x38 with
// m_dword18[m_68]. Evidence: callers none; callees rowed GameInfo 0x00A02EEC
// slot 0x50 plus own slot 0x38; layout +0x18/+0x68/+0x86 matches init 0x0041FE86.

class GameInfo
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual bool s20() = 0;
};
extern GameInfo *TheGameInfo;

class Rva00420110
{
public:
	virtual ~Rva00420110();
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual bool v14(int x) = 0;
	bool rva0042008F();
private:
	char m_pad04[0x8];
	int m_0C;
	char m_pad10[0x8];
	int m_dword18[0x14];
	int m_68;
	int m_6C;
	unsigned char m_byte70[0x14];
	unsigned char m_84;
	unsigned char m_85;
	unsigned char m_86;
};

bool Rva00420110::rva0042008F()
{
	if (m_86 != 0)
		return false;
	if (TheGameInfo != 0 && TheGameInfo->s20() != false)
		return false;
	int idx = m_68;
	if (idx < 0 || (unsigned int)idx >= 0x14)
		return false;
	return v14(m_dword18[idx]);
}
