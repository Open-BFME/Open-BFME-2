// ?rva0027937B@Rva0027937BHost@@QAEHPAURva0027937BArg@@@Z
// partial score=0.8 date=2026-10-05
// cl: /O1 /MD
struct Rva0027937BArg
{
	unsigned char m_pad[0];
};
class Rva0027937BInner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual int v20();
};
struct Rva0027937BMid
{
	unsigned char m_pad[0x254];
	Rva0027937BInner *m_254;
};
class Rva0027824DHost
{
public:
	void rva0027824D(int v, Rva0027937BArg *a);
};
class Rva0027937BHost : public Rva0027824DHost
{
public:
	int rva0027937B(Rva0027937BArg *a);
private:
	unsigned char m_pad2[0xFC];
	Rva0027937BMid *m_FC;
};
// ?rva0027937B@Rva0027937BHost@@QAEHPAURva0027937BArg@@@Z
int Rva0027937BHost::rva0027937B(Rva0027937BArg *a)
{
	int v = 0;
	Rva0027937BMid *m = m_FC;
	if (m != 0)
		v = m->m_254->v20();
	rva0027824D(v, a);
	return (int)a;
}
