// cl: /O1 /MD /EHsc
// ??1Rva0056AD19@@UAE@XZ retail 0x0056AD19 88B
// Own vptrs C6D1EC (+0) and C6D1B0 (+8, inside the first base); the member at
// +0x14 is emptied in the body through the rowed ?clear@Rva002BED91
// 0x002BED91 (EH state 1), then its inline dtor releases the ref through the rowed
// fastcall ReleaseTreeHintRef00217D4C 0x0007DEEF when set (state 0); then the
// rowed MI base dtor ??1Rva0056AC26@@UAE@XZ 0x0056AC26. Caller: rowed ??_G
// 0x0056B0A3 (vtable 0x00C6D1EC). Names address-derived.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva002BED91
{
public:
	~Rva002BED91()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}
	void clear();

private:
	TargetRef00217D4C *m_ref;
};

class Rva0056AC26A
{
public:
	virtual ~Rva0056AC26A();

private:
	int m_04;
};

class Rva0056AC26B
{
public:
	virtual ~Rva0056AC26B();

private:
	int m_04;
	int m_08;
};

class Rva0056AC26 : public Rva0056AC26A, public Rva0056AC26B
{
public:
	virtual ~Rva0056AC26();
};

class Rva0056AD19 : public Rva0056AC26
{
public:
	virtual ~Rva0056AD19();

private:
	Rva002BED91 m_14; // +0x14
};

Rva0056AD19::~Rva0056AD19()
{
	m_14.clear();
}

