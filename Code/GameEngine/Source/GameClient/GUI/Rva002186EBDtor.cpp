// cl: /O1 /MD /EHsc
// ??1Rva002186EB@@UAE@XZ retail 0x00218744 67B
// Compiler-generated dtor (no own vptr store): the rowed member dtor
// ??1Rva002177CD@@QAE@XZ 0x00217C2E on +0xC under EH state 1, then the
// holder at +8 released through the rowed fastcall
// ReleaseTreeHintRef00217D4C 0x0007DEEF when set (state 0), then the inline
// base dtor restores vtable BC6F20 (Rva0007DF07). Called by the rowed ??_G
// 0x00218728 (vtable 0x00BE5B10). Names address-derived.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva002177CD
{
public:
	~Rva002177CD();

private:
	unsigned char m_pad[0x18];
};

class Rva002186EBRef
{
public:
	~Rva002186EBRef()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

class Rva0007DF07
{
public:
	Rva0007DF07();
	virtual ~Rva0007DF07() {}
};

class Rva002186EB : public Rva0007DF07
{
public:
	Rva002186EB(int tag);

private:
	int m_04;
	Rva002186EBRef m_08; // +0x08
	Rva002177CD m_0C; // +0x0C
};

// The implicit virtual dtor is emitted with the vtable this helper ctor needs.
// ?<Rva002186EB::Rva002186EB> absent-from-retail
Rva002186EB::Rva002186EB(int)
{
}
