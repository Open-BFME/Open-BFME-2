// cl: /MD /EHsc /DNDEBUG
//
// ?rva000B3649@Rva000B3649@@QAE_NHPAURva000B3649Out@@@Z @0x000B3649 133B:
// guarded virtual fetch. Resolves an int through slot 50 of the +0x44
// provider (null provider or null result yields false), fills a stack
// 0x30-byte record through slot 51 (which returns the record address),
// copies it to the caller and returns true. Honest address-derived
// names; boundary verified (frame at 0xB3649, ret 8 at end).

struct Rva000B3649Out
{
	float f00;
	int m04[11];
};

class Rva000B3649Src
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual int vslot050(int v);
	virtual Rva000B3649Out *vslot051(Rva000B3649Out *out, int v);
};

class Rva000B3649
{
public:
	bool rva000B3649(int v, Rva000B3649Out *out);

private:
	char m_pad00[0x44];
	Rva000B3649Src *m_44;
};

// ?rva000B3649@Rva000B3649@@QAE_NHPAURva000B3649Out@@@Z
bool Rva000B3649::rva000B3649(int v, Rva000B3649Out *out)
{
	if (!m_44)
		return false;
	int t = m_44->vslot050(v);
	if (!t)
		return false;
	Rva000B3649Out tmp;
	Rva000B3649Out *p = m_44->vslot051(&tmp, t);
	out->f00 = p->f00;
	out->m04[0] = p->m04[0];
	out->m04[1] = p->m04[1];
	out->m04[2] = p->m04[2];
	out->m04[3] = p->m04[3];
	out->m04[4] = p->m04[4];
	out->m04[5] = p->m04[5];
	out->m04[6] = p->m04[6];
	out->m04[7] = p->m04[7];
	out->m04[8] = p->m04[8];
	out->m04[9] = p->m04[9];
	out->m04[10] = p->m04[10];
	return true;
}
