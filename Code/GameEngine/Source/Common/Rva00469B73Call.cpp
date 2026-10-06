// cl: /MD
// ?rva00469B73@Rva00469B73@@QAEXPAX@Z 0x00469B73 44B evidence: this+8 +0x274 null-guarded then slot 0x58 with arg and 0 plus slot 0xC on ptr at +0x250 callers 0x46D12C 0x470962
class DispatchTarget
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22(void *arg, int val);
};
struct MidBlock
{
	char m_pad[0x250];
	DispatchTarget *m_250;
};
struct HolderObj
{
	char m_pad[0x274];
	MidBlock *m_274;
};
class Rva00469B73
{
public:
	void rva00469B73(void *arg);
private:
	char m_pad[8];
	HolderObj *m_08;
};
void Rva00469B73::rva00469B73(void *arg)
{
	HolderObj *obj = m_08;
	MidBlock *mid = obj->m_274;
	if (mid == 0)
		return;
	DispatchTarget **slot = &mid->m_250;
	(*slot)->s22(arg, 0);
	(*slot)->s03();
}
