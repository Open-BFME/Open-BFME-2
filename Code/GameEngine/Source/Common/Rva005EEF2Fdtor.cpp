// cl: /O1 /EHsc /MD
//
// ??1Rva005EEF2F@@MAE@XZ @ 0x005EEF2F (99B).
// Dtor with two vptrs (+0/+4), unregister via +0x30 slot 0, members
// +0x20/+0x14 through rowed 0x005242D7/0x0052413E. Evidence: vtable stores
// 0x008787D4/0x008787D0 then 0x007FBC9C/0x007C6F20; virtual on +0x30 with
// this pushed; caller 0x005EF165 is the ??_G; neighbours share /O1.

class Rva0052413E
{
	char m_pad[12];
public:
	~Rva0052413E();
};

class Rva005242D7
{
	char m_pad[12];
public:
	~Rva005242D7();
};

class Rva005EEF2F;

class Rva005EEF2FLink
{
public:
	virtual void release(void *owner);
};

class Rva005EEF2FBase0
{
public:
	virtual ~Rva005EEF2FBase0();
};

class Rva005EEF2FBase4
{
public:
	virtual ~Rva005EEF2FBase4();
};

class Rva005EEF2F : public Rva005EEF2FBase0, public Rva005EEF2FBase4
{
public:
	char m_pad08[0x14 - 0x08];
	Rva0052413E m_14;
	Rva005242D7 m_20;
	char m_pad2C[0x30 - 0x2C];
	Rva005EEF2FLink *m_30;
protected:
	virtual ~Rva005EEF2F();
};

// ?Rva005EEF2FBase0dtor present-unmatched
Rva005EEF2FBase0::~Rva005EEF2FBase0()
{
}

// ?Rva005EEF2FBase4dtor present-unmatched
Rva005EEF2FBase4::~Rva005EEF2FBase4()
{
}

Rva005EEF2F::~Rva005EEF2F()
{
	if (m_30)
		m_30->release(this);
}
