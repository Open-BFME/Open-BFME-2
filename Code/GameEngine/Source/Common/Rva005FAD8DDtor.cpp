// cl: /O1 /MD /EHsc
// ??1Rva005FAD8D@@QAE@XZ, retail 0x005FAD8D, 98 bytes.
// Non-virtual dtor (QAE) with derived vptr 0x00879ED4 then base vptr 0x00875284,
// erase via rowed 0x002B7250 through +4->+0x14->+8, conditional virtual calls
// on +0x10 slot4 and +0x0C slot9 when +0x14 != 0, implicit member dtor
// rowed 0x005F23B2 at +0x18, inline empty base for second vptr + EH state 1.
// Evidence: callees rowed 0x005F23B2 0x002B7250; callers 0x005FAF44 0x005FAFBE.
class CreateAHeroData
{
public:
	virtual void f0();
	virtual void f1();
	~CreateAHeroData() {}
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva005FAD8DOuter
{
	char m_pad[8];
	Rva002B7250 m_w08;
};

struct Rva005FAD8DMid
{
	char m_pad[0x14];
	Rva005FAD8DOuter *m_14;
};

class Rva005FAD8DV10
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
};

class Rva005FAD8DV0C
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
	virtual void t3();
	virtual void t4();
	virtual void t5();
	virtual void t6();
	virtual void t7();
	virtual void t8();
	virtual void t9();
};

class Rva005F23B2
{
public:
	~Rva005F23B2();
};

class Rva005FAD8D : public CreateAHeroData
{
public:
	~Rva005FAD8D();
private:
	Rva005FAD8DMid *m_04;
	int m_08;
	Rva005FAD8DV0C *m_0C;
	Rva005FAD8DV10 *m_10;
	int m_flag14;
	Rva005F23B2 m_18;
};

Rva005FAD8D::~Rva005FAD8D()
{
	Rva005FAD8DOuter *outer = m_04->m_14;
	outer->m_w08.rva002B7250((CreateAHeroData *)this);
	if (m_flag14 != 0) {
		m_10->s4();
		m_0C->t9();
	}
}
