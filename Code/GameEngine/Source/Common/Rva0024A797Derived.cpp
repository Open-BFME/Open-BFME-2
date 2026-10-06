// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva0024A797::~
// Rva0024A797 at 0x0024A797 (pinned opaque MI base: three vptrs tail-jumping
// the 0x49B47C fold; identity unproven). Each class below derives (in order)
// from the opaque base, a shared empty polymorphic base, and its own empty
// polymorphic base, giving vptrs at +0x00/+0x0C/+0x10; the empty bases have
// implicit trivial destructors, so the derived destructor stores all three
// vptrs and tail-calls the base destructor. The +0x0C secondary is shared
// across the family (0xBEFF90). Owner identities are unproven (opaque Rva
// names). One ledger row per destructor, landed one commit at a time.

class Rva0024A797
{
public:
	virtual ~Rva0024A797();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva00253E19_B2
{
public:
	virtual void f2();
};

class Rva00253E19 : public Rva0024A797, public MiBase1, public Rva00253E19_B2
{
public:
	virtual ~Rva00253E19();
};

Rva00253E19::~Rva00253E19()
{
}

class Rva00253EF5_B2
{
public:
	virtual void f2();
};

class Rva00253EF5 : public Rva0024A797, public MiBase1, public Rva00253EF5_B2
{
public:
	virtual ~Rva00253EF5();
};

Rva00253EF5::~Rva00253EF5()
{
}

class Rva0033EEC9_B2
{
public:
	virtual void f2();
};

class Rva0033EEC9 : public Rva0024A797, public MiBase1, public Rva0033EEC9_B2
{
public:
	virtual ~Rva0033EEC9();
};

Rva0033EEC9::~Rva0033EEC9()
{
}

class Rva00373CB1_B2
{
public:
	virtual void f2();
};

class Rva00373CB1 : public Rva0024A797, public MiBase1, public Rva00373CB1_B2
{
public:
	virtual ~Rva00373CB1();
};

Rva00373CB1::~Rva00373CB1()
{
}

class Rva003A4322_B2
{
public:
	virtual void f2();
};

class Rva003A4322 : public Rva0024A797, public MiBase1, public Rva003A4322_B2
{
public:
	virtual ~Rva003A4322();
};

Rva003A4322::~Rva003A4322()
{
}

class Rva003A49D1_B2
{
public:
	virtual void f2();
};

class Rva003A49D1 : public Rva0024A797, public MiBase1, public Rva003A49D1_B2
{
public:
	virtual ~Rva003A49D1();
};

Rva003A49D1::~Rva003A49D1()
{
}

class Rva003A4CAE_B2
{
public:
	virtual void f2();
};

class Rva003A4CAE : public Rva0024A797, public MiBase1, public Rva003A4CAE_B2
{
public:
	virtual ~Rva003A4CAE();
};

Rva003A4CAE::~Rva003A4CAE()
{
}

class Rva004561A2_B2
{
public:
	virtual void f2();
};

class Rva004561A2 : public Rva0024A797, public MiBase1, public Rva004561A2_B2
{
public:
	virtual ~Rva004561A2();
};

Rva004561A2::~Rva004561A2()
{
}

class Rva00458AAE_B2
{
public:
	virtual void f2();
};

class Rva00458AAE : public Rva0024A797, public MiBase1, public Rva00458AAE_B2
{
public:
	virtual ~Rva00458AAE();
};

Rva00458AAE::~Rva00458AAE()
{
}

class Rva00459154_B2
{
public:
	virtual void f2();
};

class Rva00459154 : public Rva0024A797, public MiBase1, public Rva00459154_B2
{
public:
	virtual ~Rva00459154();
};

Rva00459154::~Rva00459154()
{
}

class Rva0045ADC1_B2
{
public:
	virtual void f2();
};

class Rva0045ADC1 : public Rva0024A797, public MiBase1, public Rva0045ADC1_B2
{
public:
	virtual ~Rva0045ADC1();
};

Rva0045ADC1::~Rva0045ADC1()
{
}

class Rva0045B134_B2
{
public:
	virtual void f2();
};

class Rva0045B134 : public Rva0024A797, public MiBase1, public Rva0045B134_B2
{
public:
	virtual ~Rva0045B134();
};

Rva0045B134::~Rva0045B134()
{
}

class Rva0047F92D_B2
{
public:
	virtual void f2();
};

class Rva0047F92D : public Rva0024A797, public MiBase1, public Rva0047F92D_B2
{
public:
	virtual ~Rva0047F92D();
};

Rva0047F92D::~Rva0047F92D()
{
}

class Rva00486E18_B2
{
public:
	virtual void f2();
};

class Rva00486E18 : public Rva0024A797, public MiBase1, public Rva00486E18_B2
{
public:
	virtual ~Rva00486E18();
};

Rva00486E18::~Rva00486E18()
{
}

class Rva00488338_B2
{
public:
	virtual void f2();
};

class Rva00488338 : public Rva0024A797, public MiBase1, public Rva00488338_B2
{
public:
	virtual ~Rva00488338();
};

Rva00488338::~Rva00488338()
{
}

class Rva0048B671_B2
{
public:
	virtual void f2();
};

class Rva0048B671 : public Rva0024A797, public MiBase1, public Rva0048B671_B2
{
public:
	virtual ~Rva0048B671();
};

Rva0048B671::~Rva0048B671()
{
}

class Rva0048D742_B2
{
public:
	virtual void f2();
};

class Rva0048D742 : public Rva0024A797, public MiBase1, public Rva0048D742_B2
{
public:
	virtual ~Rva0048D742();
};

Rva0048D742::~Rva0048D742()
{
}

class Rva0048FBBA_B2
{
public:
	virtual void f2();
};

class Rva0048FBBA : public Rva0024A797, public MiBase1, public Rva0048FBBA_B2
{
public:
	virtual ~Rva0048FBBA();
};

Rva0048FBBA::~Rva0048FBBA()
{
}

class Rva0049188D_B2
{
public:
	virtual void f2();
};

class Rva0049188D : public Rva0024A797, public MiBase1, public Rva0049188D_B2
{
public:
	virtual ~Rva0049188D();
};

Rva0049188D::~Rva0049188D()
{
}

class Rva00491DD3_B2
{
public:
	virtual void f2();
};

class Rva00491DD3 : public Rva0024A797, public MiBase1, public Rva00491DD3_B2
{
public:
	virtual ~Rva00491DD3();
};

Rva00491DD3::~Rva00491DD3()
{
}

class Rva0049506E_B2
{
public:
	virtual void f2();
};

class Rva0049506E : public Rva0024A797, public MiBase1, public Rva0049506E_B2
{
public:
	virtual ~Rva0049506E();
};

Rva0049506E::~Rva0049506E()
{
}

class Rva00495916_B2
{
public:
	virtual void f2();
};

class Rva00495916 : public Rva0024A797, public MiBase1, public Rva00495916_B2
{
public:
	virtual ~Rva00495916();
};

Rva00495916::~Rva00495916()
{
}

class Rva0049669A_B2
{
public:
	virtual void f2();
};

class Rva0049669A : public Rva0024A797, public MiBase1, public Rva0049669A_B2
{
public:
	virtual ~Rva0049669A();
};

Rva0049669A::~Rva0049669A()
{
}

class Rva004969FF_B2
{
public:
	virtual void f2();
};

class Rva004969FF : public Rva0024A797, public MiBase1, public Rva004969FF_B2
{
public:
	virtual ~Rva004969FF();
};

Rva004969FF::~Rva004969FF()
{
}

class Rva00499F45_B2
{
public:
	virtual void f2();
};

class Rva00499F45 : public Rva0024A797, public MiBase1, public Rva00499F45_B2
{
public:
	virtual ~Rva00499F45();
};

Rva00499F45::~Rva00499F45()
{
}

class Rva0049A1AB_B2
{
public:
	virtual void f2();
};

class Rva0049A1AB : public Rva0024A797, public MiBase1, public Rva0049A1AB_B2
{
public:
	virtual ~Rva0049A1AB();
};

Rva0049A1AB::~Rva0049A1AB()
{
}

class Rva0049B2A2_B2
{
public:
	virtual void f2();
};

class Rva0049B2A2 : public Rva0024A797, public MiBase1, public Rva0049B2A2_B2
{
public:
	virtual ~Rva0049B2A2();
};

Rva0049B2A2::~Rva0049B2A2()
{
}

class Rva0049FE7B_B2
{
public:
	virtual void f2();
};

class Rva0049FE7B : public Rva0024A797, public MiBase1, public Rva0049FE7B_B2
{
public:
	virtual ~Rva0049FE7B();
};

Rva0049FE7B::~Rva0049FE7B()
{
}

class Rva004A0C0E_B2
{
public:
	virtual void f2();
};

class Rva004A0C0E : public Rva0024A797, public MiBase1, public Rva004A0C0E_B2
{
public:
	virtual ~Rva004A0C0E();
};

Rva004A0C0E::~Rva004A0C0E()
{
}

class Rva004A2BD1_B2
{
public:
	virtual void f2();
};

class Rva004A2BD1 : public Rva0024A797, public MiBase1, public Rva004A2BD1_B2
{
public:
	virtual ~Rva004A2BD1();
};

Rva004A2BD1::~Rva004A2BD1()
{
}

class Rva004A3F8B_B2
{
public:
	virtual void f2();
};

class Rva004A3F8B : public Rva0024A797, public MiBase1, public Rva004A3F8B_B2
{
public:
	virtual ~Rva004A3F8B();
};

Rva004A3F8B::~Rva004A3F8B()
{
}

class Rva004AE78E_B2
{
public:
	virtual void f2();
};

class Rva004AE78E : public Rva0024A797, public MiBase1, public Rva004AE78E_B2
{
public:
	virtual ~Rva004AE78E();
};

Rva004AE78E::~Rva004AE78E()
{
}

class Rva004B237B_B2
{
public:
	virtual void f2();
};

class Rva004B237B : public Rva0024A797, public MiBase1, public Rva004B237B_B2
{
public:
	virtual ~Rva004B237B();
};

Rva004B237B::~Rva004B237B()
{
}

class Rva004B89C4_B2
{
public:
	virtual void f2();
};

class Rva004B89C4 : public Rva0024A797, public MiBase1, public Rva004B89C4_B2
{
public:
	virtual ~Rva004B89C4();
};

Rva004B89C4::~Rva004B89C4()
{
}

class Rva004CC63A_B2
{
public:
	virtual void f2();
};

class Rva004CC63A : public Rva0024A797, public MiBase1, public Rva004CC63A_B2
{
public:
	virtual ~Rva004CC63A();
};

Rva004CC63A::~Rva004CC63A()
{
}

class Rva004DF7C2_B2
{
public:
	virtual void f2();
};

class Rva004DF7C2 : public Rva0024A797, public MiBase1, public Rva004DF7C2_B2
{
public:
	virtual ~Rva004DF7C2();
};

Rva004DF7C2::~Rva004DF7C2()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva0033EEC9_B2@@UAEXXZ=?update@ProjectileStreamUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00486E18_B2@@UAEXXZ=?Rva004A6563Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?f2@Rva00488338_B2@@UAEXXZ=?update@DeletionUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049FE7B_B2@@UAEXXZ=?update@ProneUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004A0C0E_B2@@UAEXXZ=?update@RadarUpdate@@UAE?AW4UpdateSleepTime@@XZ")
