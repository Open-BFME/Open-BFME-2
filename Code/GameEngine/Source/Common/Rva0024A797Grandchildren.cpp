// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva0024A797::~
// Rva0024A797 at 0x0024A797 (pinned opaque MI base dtor: 3 vptrs tail-jump
// the 0x49B47C fold; identity unproven). The middle is modelled here with
// its full three-vptr shape (root plus two secondaries) plus 12 bytes of
// opaque data so the layout reaches +0x20: every body below adds at least
// one further base at +0x20, which is the evidence for the middle size.
// Each class below derives (in order) from the middle and its own empty
// polymorphic bases and overrides every vptr before tail-calling the base
// destructor; the middle itself is only declared here (defined nowhere --
// it resolves via the pin), because a same-TU definition would capture the
// call locally instead of at the ledger address. Vtable values are DIR32
// auto-patches. Owner identities are unproven (opaque Rva names). One ledger
// row per destructor, landed one commit at a time.

class Rva0024A797_Root
{
public:
	virtual ~Rva0024A797_Root();

private:
	char m_pad04[8];
};

class Rva0024A797_Mid
{
public:
	virtual void f1();
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0024A797 : public Rva0024A797_Root, public Rva0024A797_Mid, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class Rva00452D52_E1
{
public:
	virtual void fe();
};

class Rva00452D52 : public Rva0024A797, public Rva00452D52_E1
{
public:
	virtual ~Rva00452D52();
};

Rva00452D52::~Rva00452D52()
{
}

class Rva00455050_E1
{
public:
	virtual void fe();
};

class Rva00455050 : public Rva0024A797, public Rva00455050_E1
{
public:
	virtual ~Rva00455050();
};

Rva00455050::~Rva00455050()
{
}

class Rva00458402_E1
{
public:
	virtual void fe();
};

class Rva00458402 : public Rva0024A797, public Rva00458402_E1
{
public:
	virtual ~Rva00458402();
};

Rva00458402::~Rva00458402()
{
}

class Rva00459553_E1
{
public:
	virtual void fe();
};

class Rva00459553 : public Rva0024A797, public Rva00459553_E1
{
public:
	virtual ~Rva00459553();
};

Rva00459553::~Rva00459553()
{
}

class Rva0047FE25_E1
{
public:
	virtual void fe();
};

class Rva0047FE25 : public Rva0024A797, public Rva0047FE25_E1
{
public:
	virtual ~Rva0047FE25();
};

Rva0047FE25::~Rva0047FE25()
{
}

class Rva0048180C_E1
{
public:
	virtual void fe();
};

class Rva0048180C : public Rva0024A797, public Rva0048180C_E1
{
public:
	virtual ~Rva0048180C();
};

Rva0048180C::~Rva0048180C()
{
}

class Rva004839D3_E1
{
public:
	virtual void fe();
};

class Rva004839D3 : public Rva0024A797, public Rva004839D3_E1
{
public:
	virtual ~Rva004839D3();
};

Rva004839D3::~Rva004839D3()
{
}

class Rva00487F3A_E1
{
public:
	virtual void fe();
};

class Rva00487F3A : public Rva0024A797, public Rva00487F3A_E1
{
public:
	virtual ~Rva00487F3A();
};

Rva00487F3A::~Rva00487F3A()
{
}

class Rva0048FFB4_E1
{
public:
	virtual void fe();
};

class Rva0048FFB4 : public Rva0024A797, public Rva0048FFB4_E1
{
public:
	virtual ~Rva0048FFB4();
};

Rva0048FFB4::~Rva0048FFB4()
{
}

class Rva00499934_E1
{
public:
	virtual void fe();
};

class Rva00499934 : public Rva0024A797, public Rva00499934_E1
{
public:
	virtual ~Rva00499934();
};

Rva00499934::~Rva00499934()
{
}

class Rva0049BFB7_E1
{
public:
	virtual void fe();
};

class Rva0049BFB7 : public Rva0024A797, public Rva0049BFB7_E1
{
public:
	virtual ~Rva0049BFB7();
};

Rva0049BFB7::~Rva0049BFB7()
{
}

class Rva004A1855_E1
{
public:
	virtual void fe();
};

class Rva004A1855 : public Rva0024A797, public Rva004A1855_E1
{
public:
	virtual ~Rva004A1855();
};

Rva004A1855::~Rva004A1855()
{
}

class Rva004A4214_E1
{
public:
	virtual void fe();
};

class Rva004A4214 : public Rva0024A797, public Rva004A4214_E1
{
public:
	virtual ~Rva004A4214();
};

Rva004A4214::~Rva004A4214()
{
}

class Rva004A4C19_E1
{
public:
	virtual void fe();
};

class Rva004A4C19 : public Rva0024A797, public Rva004A4C19_E1
{
public:
	virtual ~Rva004A4C19();
};

Rva004A4C19::~Rva004A4C19()
{
}

class Rva004A54A8_E1
{
public:
	virtual void fe();
};

class Rva004A54A8 : public Rva0024A797, public Rva004A54A8_E1
{
public:
	virtual ~Rva004A54A8();
};

Rva004A54A8::~Rva004A54A8()
{
}

class Rva004A653D_E1
{
public:
	virtual void fe();
};

class Rva004A653D : public Rva0024A797, public Rva004A653D_E1
{
public:
	virtual ~Rva004A653D();
};

Rva004A653D::~Rva004A653D()
{
}

class Rva004A8091_E1
{
public:
	virtual void fe();
};

class Rva004A8091 : public Rva0024A797, public Rva004A8091_E1
{
public:
	virtual ~Rva004A8091();
};

Rva004A8091::~Rva004A8091()
{
}

class Rva004B8732_E1
{
public:
	virtual void fe();
};

class Rva004B8732 : public Rva0024A797, public Rva004B8732_E1
{
public:
	virtual ~Rva004B8732();
};

Rva004B8732::~Rva004B8732()
{
}

class Rva0045D39E_E1
{
public:
	virtual void fe();
};

class Rva0045D39E_E2
{
public:
	virtual void ff();
};

class Rva0045D39E : public Rva0024A797, public Rva0045D39E_E1, public Rva0045D39E_E2
{
public:
	virtual ~Rva0045D39E();
};

Rva0045D39E::~Rva0045D39E()
{
}

class Rva004AB246_E1
{
public:
	virtual void fe();
};

class Rva004AB246_E2
{
public:
	virtual void ff();
};

class Rva004AB246 : public Rva0024A797, public Rva004AB246_E1, public Rva004AB246_E2
{
public:
	virtual ~Rva004AB246();
};

Rva004AB246::~Rva004AB246()
{
}

class Rva0045232D_E1
{
public:
	virtual void fe();

private:
	int m_data04;
};

class Rva0045232D_E2
{
public:
	virtual void ff();
};

class Rva0045232D : public Rva0024A797, public Rva0045232D_E1, public Rva0045232D_E2
{
public:
	virtual ~Rva0045232D();
};

Rva0045232D::~Rva0045232D()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0024A797_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?fe@Rva00458402_E1@@UAEXXZ=?setPositions@BridgeScaffoldBehavior@@UAEXPBUCoord3D@@00@Z")
#pragma comment(linker, "/alternatename:?fe@Rva00487F3A_E1@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?fe@Rva0048FFB4_E1@@UAEXXZ=?get@Rva001DAF7DByteField@@QBEEXZ")
#pragma comment(linker, "/alternatename:?fe@Rva0049BFB7_E1@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?fe@Rva004A1855_E1@@UAEXXZ=?getKey@?$CategoryModuleClass@$0A@@FXParticleSystem@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?fe@Rva004A653D_E1@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?fe@Rva004B8732_E1@@UAEXXZ=?rva004B8851@Rva004B8732@@UBE?AVAsciiString@@XZ")
#pragma comment(linker, "/alternatename:?ff@Rva0045232D_E2@@UAEXXZ=?onDamage@AutoHealBehavior@@UAEXPAVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?fe@Rva0045232D_E1@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?fe@Rva004AB246_E1@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
