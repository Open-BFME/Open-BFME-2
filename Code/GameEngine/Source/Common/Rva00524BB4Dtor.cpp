// cl: /MD /EHsc
// ??1Rva00524BB4@@UAE@XZ retail 0x00524BB4 75B
// Own vptr C67DFC; under EH state 1 the body empties the object through the
// rowed ?clear@Rva00524A4C 0x00524A4C; the ref holder at +0x34 is released
// through the rowed fastcall ReleaseTreeHintRef00217D4C 0x0007DEEF when set
// (state 0); then the rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ
// 0x001B4E74. Names address-derived.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

class Rva00524A4C
{
public:
	void clear();
};

class Rva00524BB4Ref
{
public:
	~Rva00524BB4Ref()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

class Rva00524BB4 : public SubsystemInterface
{
public:
	virtual ~Rva00524BB4();

private:
	unsigned char m_pad0C[0x34 - 0x0C];
	Rva00524BB4Ref m_ref; // +0x34
};

Rva00524BB4::~Rva00524BB4()
{
	((Rva00524A4C *)this)->clear();
}
