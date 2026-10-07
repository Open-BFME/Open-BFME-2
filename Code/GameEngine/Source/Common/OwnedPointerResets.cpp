// cl: /MD
//
// Owning-pointer resets: 26-byte members that take the pointer at +0, null
// the slot, and if it was set run the pointee's destructor and free it through
// operator delete 0x0002FD60, the shape of the rowed ?clear@Rva00053D89@@QAEXXZ
// (Rva00053D89Clear.cpp). Each holder is named after its reset's address and
// each pointee after the destructor address the retail call proves. The
// 0x004E668E destructor is defined below from its own boundary; other names
// remain address-derived. Owner and pointee type identities are not recovered.
//
//   reset       pointee dtor  callers
//   0x000AF146  0x000AD71D    2
//   0x0023A039  0x00239D7A    3
//   0x0029B5E3  0x004E668E    4
//   0x0029B620  0x004E6A9B    3
//   0x002B430C  0x004FA2E2    5
//   0x002B9099  0x002B74DE    6
//   0x002D3894  0x0052710C    5
//   0x002D38D1  0x00527CCE    9
//   0x002D3931  0x00527FA2    5
//   0x0042C1DF  0x0057417E    4
//   0x0042D789  0x00578C43    3
//   0x0042D87D  0x0057BD01    3
//   0x004E6A1D  0x004E6935    10
//   0x004E7F29  0x004E7DC8    1 (dtor rowed)
//   0x00526F12  0x0052634F    1
//   0x00526F2C  0x005262BF    1
//   0x00527F88  0x00527E53    1
//   0x005287D0  0x005282BA    1
//   0x0052A76C  0x0052A470    1 (dtor rowed)
//   0x005786CD  0x005D32D4    3
//   0x00578724  0x005D3C2B    3
//   0x0057B9B6  0x005D4FFC    3
//   0x005CE21C  0x005E893E    6
//   0x005CF363  0x005CEFD3    1
//   0x005D0ABB  0x005D07E1    1
//   0x005D127C  0x005D1210    1
//   0x005D32AA  0x005D309D    1
//   0x005D4FA0  0x005D4EC6    1 (dtor rowed)
//   0x005E1E81  0x005E1D07    1
//   0x005E4B9D  0x005E4925    1
//   0x005E6253  0x005E5FFB    1
//   0x005E6D90  0x005E6D0D    1
//   0x005E7FC8  0x005E7D72    3
//   0x005E88EE  0x005E888A    1 (dtor rowed)
//   0x005E9E27  0x005E98A0    1
//   0x005EB430  0x005EB2E7    1
//   0x005EBC74  0x005EB8D6    1
//   0x005EC422  0x005EC09B    1
//   0x005EDFF5  0x005EDE64    1
//   0x005F13CC  0x005F1295    1
//   0x005F4096  0x005F3FFC    1
//   0x005F50B9  0x005F501E    5
//   0x005F55FA  0x005F54DA    1
//   0x005F64DB  0x005F6051    1
//   0x005F74A0  0x005F6A58    3 (dtor rowed)
//   0x005FAFB2  0x005FAD8D    1
//   0x005FBBA6  0x005FB615    1 (dtor rowed)
//   0x005FCB2D  0x005FCA8B    1
//   0x005FD95E  0x005FD628    1
//   0x005FF8F8  0x005FF5F6    1

void __cdecl operator delete(void *p);

class Rva000AD71D
{
public:
	~Rva000AD71D();
};

class Rva000AF146
{
public:
	Rva000AD71D *m_ptr;
	void clear();
};

void Rva000AF146::clear()
{
	Rva000AD71D *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva000AD71D::~Rva000AD71D();
		::operator delete(p);
	}
}

class Rva00239D7A
{
public:
	~Rva00239D7A();
};

class Rva0023A039
{
public:
	Rva00239D7A *m_ptr;
	void clear();
};

void Rva0023A039::clear()
{
	Rva00239D7A *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00239D7A::~Rva00239D7A();
		::operator delete(p);
	}
}

class Rva004E668E
{
public:
	~Rva004E668E();
};

// Target identity: the reset methods below and the scalar deleting destructor
// call 0x004E668E as this pointee's destructor. Its five-byte body tail-jumps
// without adjusting this to the rowed cleanup method at 0x004E63E2; preserve
// the pin's address-derived class name.
struct Rva004E63E2
{
	void rva004E63E2();
};

Rva004E668E::~Rva004E668E()
{
	((Rva004E63E2 *)this)->rva004E63E2();
}

class Rva0029B5E3
{
public:
	Rva004E668E *m_ptr;
	void clear();
};

void Rva0029B5E3::clear()
{
	Rva004E668E *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva004E668E::~Rva004E668E();
		::operator delete(p);
	}
}

class Rva004E6A9B
{
public:
	~Rva004E6A9B();
};

class Rva0029B620
{
public:
	Rva004E6A9B *m_ptr;
	void clear();
};

void Rva0029B620::clear()
{
	Rva004E6A9B *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva004E6A9B::~Rva004E6A9B();
		::operator delete(p);
	}
}

class Rva004FA2E2
{
public:
	~Rva004FA2E2();
};

class Rva002B430C
{
public:
	Rva004FA2E2 *m_ptr;
	void clear();
};

void Rva002B430C::clear()
{
	Rva004FA2E2 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva004FA2E2::~Rva004FA2E2();
		::operator delete(p);
	}
}

class Rva002B74DE
{
public:
	~Rva002B74DE();
};

class Rva002B9099
{
public:
	Rva002B74DE *m_ptr;
	void clear();
};

void Rva002B9099::clear()
{
	Rva002B74DE *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva002B74DE::~Rva002B74DE();
		::operator delete(p);
	}
}

class Rva0052710C
{
public:
	~Rva0052710C();
};

class Rva002D3894
{
public:
	Rva0052710C *m_ptr;
	void clear();
};

void Rva002D3894::clear()
{
	Rva0052710C *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva0052710C::~Rva0052710C();
		::operator delete(p);
	}
}

class Rva00527CCE
{
public:
	~Rva00527CCE();
};

class Rva002D38D1
{
public:
	Rva00527CCE *m_ptr;
	void clear();
};

void Rva002D38D1::clear()
{
	Rva00527CCE *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00527CCE::~Rva00527CCE();
		::operator delete(p);
	}
}

class Rva00527FA2
{
public:
	~Rva00527FA2();
};

class Rva002D3931
{
public:
	Rva00527FA2 *m_ptr;
	void clear();
};

void Rva002D3931::clear()
{
	Rva00527FA2 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00527FA2::~Rva00527FA2();
		::operator delete(p);
	}
}

class Rva0057417E
{
public:
	~Rva0057417E();
};

class Rva0042C1DF
{
public:
	Rva0057417E *m_ptr;
	void clear();
};

void Rva0042C1DF::clear()
{
	Rva0057417E *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva0057417E::~Rva0057417E();
		::operator delete(p);
	}
}

class Rva00578C43
{
public:
	~Rva00578C43();
};

class Rva0042D789
{
public:
	Rva00578C43 *m_ptr;
	void clear();
};

void Rva0042D789::clear()
{
	Rva00578C43 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00578C43::~Rva00578C43();
		::operator delete(p);
	}
}

class Rva0057BD01
{
public:
	~Rva0057BD01();
};

class Rva0042D87D
{
public:
	Rva0057BD01 *m_ptr;
	void clear();
};

void Rva0042D87D::clear()
{
	Rva0057BD01 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva0057BD01::~Rva0057BD01();
		::operator delete(p);
	}
}

class Rva004E6935
{
public:
	~Rva004E6935();
};

class Rva004E6A1D
{
public:
	Rva004E6935 *m_ptr;
	void clear();
};

void Rva004E6A1D::clear()
{
	Rva004E6935 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva004E6935::~Rva004E6935();
		::operator delete(p);
	}
}

class Rva004E7DC8
{
public:
	~Rva004E7DC8();
};

class Rva004E7F29
{
public:
	Rva004E7DC8 *m_ptr;
	void clear();
	void rva004E7F7E();
};

void Rva004E7F29::clear()
{
	Rva004E7DC8 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva004E7DC8::~Rva004E7DC8();
		::operator delete(p);
	}
}

// Target identity: retail's five-byte entry at 0x004E7F7E forwards the
// unchanged this pointer into the matched reset at 0x004E7F29. Keep the
// wrapper name address-derived.
void Rva004E7F29::rva004E7F7E()
{
	clear();
}

class Rva0052634F
{
public:
	~Rva0052634F();
};

class Rva00526F12
{
public:
	Rva0052634F *m_ptr;
	void clear();
};

void Rva00526F12::clear()
{
	Rva0052634F *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva0052634F::~Rva0052634F();
		::operator delete(p);
	}
}

class Rva005262BF
{
public:
	~Rva005262BF();
};

class Rva00526F2C
{
public:
	Rva005262BF *m_ptr;
	void clear();
};

void Rva00526F2C::clear()
{
	Rva005262BF *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005262BF::~Rva005262BF();
		::operator delete(p);
	}
}

class Rva00527E53
{
public:
	~Rva00527E53();
};

class Rva00527F88
{
public:
	Rva00527E53 *m_ptr;
	void clear();
};

void Rva00527F88::clear()
{
	Rva00527E53 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva00527E53::~Rva00527E53();
		::operator delete(p);
	}
}

class Rva005282BA
{
public:
	~Rva005282BA();
};

class Rva005287D0
{
public:
	Rva005282BA *m_ptr;
	void clear();
};

void Rva005287D0::clear()
{
	Rva005282BA *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005282BA::~Rva005282BA();
		::operator delete(p);
	}
}

class Rva0052A470
{
public:
	~Rva0052A470();
};

class Rva0052A76C
{
public:
	Rva0052A470 *m_ptr;
	void clear();
};

void Rva0052A76C::clear()
{
	Rva0052A470 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva0052A470::~Rva0052A470();
		::operator delete(p);
	}
}

class Rva005D32D4
{
public:
	~Rva005D32D4();
};

class Rva005786CD
{
public:
	Rva005D32D4 *m_ptr;
	void clear();
};

void Rva005786CD::clear()
{
	Rva005D32D4 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D32D4::~Rva005D32D4();
		::operator delete(p);
	}
}

class Rva005D3C2B
{
public:
	~Rva005D3C2B();
};

class Rva00578724
{
public:
	Rva005D3C2B *m_ptr;
	void clear();
};

void Rva00578724::clear()
{
	Rva005D3C2B *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D3C2B::~Rva005D3C2B();
		::operator delete(p);
	}
}

class Rva005D4FFC
{
public:
	~Rva005D4FFC();
};

class Rva0057B9B6
{
public:
	Rva005D4FFC *m_ptr;
	void clear();
};

void Rva0057B9B6::clear()
{
	Rva005D4FFC *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D4FFC::~Rva005D4FFC();
		::operator delete(p);
	}
}

class Rva005E893E
{
public:
	~Rva005E893E();
};

class Rva005CE21C
{
public:
	Rva005E893E *m_ptr;
	void clear();
};

void Rva005CE21C::clear()
{
	Rva005E893E *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E893E::~Rva005E893E();
		::operator delete(p);
	}
}

class Rva005CEFD3
{
public:
	~Rva005CEFD3();
};

class Rva005CF363
{
public:
	Rva005CEFD3 *m_ptr;
	void clear();
};

void Rva005CF363::clear()
{
	Rva005CEFD3 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005CEFD3::~Rva005CEFD3();
		::operator delete(p);
	}
}

class Rva005D07E1
{
public:
	~Rva005D07E1();
};

class Rva005D0ABB
{
public:
	Rva005D07E1 *m_ptr;
	void clear();
};

void Rva005D0ABB::clear()
{
	Rva005D07E1 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D07E1::~Rva005D07E1();
		::operator delete(p);
	}
}

class Rva005D1210
{
public:
	~Rva005D1210();
};

class Rva005D127C
{
public:
	Rva005D1210 *m_ptr;
	void clear();
};

void Rva005D127C::clear()
{
	Rva005D1210 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D1210::~Rva005D1210();
		::operator delete(p);
	}
}

class Rva005D309D
{
public:
	~Rva005D309D();
};

class Rva005D32AA
{
public:
	Rva005D309D *m_ptr;
	void clear();
};

void Rva005D32AA::clear()
{
	Rva005D309D *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D309D::~Rva005D309D();
		::operator delete(p);
	}
}

class Rva005D4EC6
{
public:
	~Rva005D4EC6();
};

class Rva005D4FA0
{
public:
	Rva005D4EC6 *m_ptr;
	void clear();
};

void Rva005D4FA0::clear()
{
	Rva005D4EC6 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005D4EC6::~Rva005D4EC6();
		::operator delete(p);
	}
}

class Rva005E1D07
{
public:
	~Rva005E1D07();
};

class Rva005E1E81
{
public:
	Rva005E1D07 *m_ptr;
	void clear();
};

void Rva005E1E81::clear()
{
	Rva005E1D07 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E1D07::~Rva005E1D07();
		::operator delete(p);
	}
}

class Rva005E4925
{
public:
	~Rva005E4925();
};

class Rva005E4B9D
{
public:
	Rva005E4925 *m_ptr;
	void clear();
};

void Rva005E4B9D::clear()
{
	Rva005E4925 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E4925::~Rva005E4925();
		::operator delete(p);
	}
}

class Rva005E5FFB
{
public:
	~Rva005E5FFB();
};

class Rva005E6253
{
public:
	Rva005E5FFB *m_ptr;
	void clear();
};

void Rva005E6253::clear()
{
	Rva005E5FFB *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E5FFB::~Rva005E5FFB();
		::operator delete(p);
	}
}

class Rva005E6D0D
{
public:
	~Rva005E6D0D();
};

class Rva005E6D90
{
public:
	Rva005E6D0D *m_ptr;
	void clear();
};

void Rva005E6D90::clear()
{
	Rva005E6D0D *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E6D0D::~Rva005E6D0D();
		::operator delete(p);
	}
}

class Rva005E7D72
{
public:
	~Rva005E7D72();
};

class Rva005E7FC8
{
public:
	Rva005E7D72 *m_ptr;
	void clear();
};

void Rva005E7FC8::clear()
{
	Rva005E7D72 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E7D72::~Rva005E7D72();
		::operator delete(p);
	}
}

class Rva005E888A
{
public:
	~Rva005E888A();
};

class Rva005E88EE
{
public:
	Rva005E888A *m_ptr;
	void clear();
};

void Rva005E88EE::clear()
{
	Rva005E888A *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E888A::~Rva005E888A();
		::operator delete(p);
	}
}

class Rva005E98A0
{
public:
	~Rva005E98A0();
};

class Rva005E9E27
{
public:
	Rva005E98A0 *m_ptr;
	void clear();
};

void Rva005E9E27::clear()
{
	Rva005E98A0 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E98A0::~Rva005E98A0();
		::operator delete(p);
	}
}

class Rva005EB2E7
{
public:
	~Rva005EB2E7();
};

class Rva005EB430
{
public:
	Rva005EB2E7 *m_ptr;
	void clear();
};

void Rva005EB430::clear()
{
	Rva005EB2E7 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005EB2E7::~Rva005EB2E7();
		::operator delete(p);
	}
}

class Rva005EB8D6
{
public:
	~Rva005EB8D6();
};

class Rva005EBC74
{
public:
	Rva005EB8D6 *m_ptr;
	void clear();
};

void Rva005EBC74::clear()
{
	Rva005EB8D6 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005EB8D6::~Rva005EB8D6();
		::operator delete(p);
	}
}

class Rva005EC09B
{
public:
	~Rva005EC09B();
};

class Rva005EC422
{
public:
	Rva005EC09B *m_ptr;
	void clear();
};

void Rva005EC422::clear()
{
	Rva005EC09B *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005EC09B::~Rva005EC09B();
		::operator delete(p);
	}
}

class Rva005EDE64
{
public:
	~Rva005EDE64();
};

class Rva005EDFF5
{
public:
	Rva005EDE64 *m_ptr;
	void clear();
};

void Rva005EDFF5::clear()
{
	Rva005EDE64 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005EDE64::~Rva005EDE64();
		::operator delete(p);
	}
}

class Rva005F3FFC
{
public:
	~Rva005F3FFC();
};

class Rva005F4096
{
public:
	Rva005F3FFC *m_ptr;
	void clear();
};

void Rva005F4096::clear()
{
	Rva005F3FFC *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F3FFC::~Rva005F3FFC();
		::operator delete(p);
	}
}

class Rva005F501E
{
public:
	~Rva005F501E();
};

class Rva005F50B9
{
public:
	Rva005F501E *m_ptr;
	void clear();
};

void Rva005F50B9::clear()
{
	Rva005F501E *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F501E::~Rva005F501E();
		::operator delete(p);
	}
}

class Rva005F54DA
{
public:
	~Rva005F54DA();
};

class Rva005F55FA
{
public:
	Rva005F54DA *m_ptr;
	void clear();
};

void Rva005F55FA::clear()
{
	Rva005F54DA *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F54DA::~Rva005F54DA();
		::operator delete(p);
	}
}

class Rva005F6051
{
public:
	~Rva005F6051();
};

class Rva005F64DB
{
public:
	Rva005F6051 *m_ptr;
	void clear();
};

void Rva005F64DB::clear()
{
	Rva005F6051 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F6051::~Rva005F6051();
		::operator delete(p);
	}
}

class Rva005F6A58
{
public:
	virtual ~Rva005F6A58();
};

class Rva005F74A0
{
public:
	Rva005F6A58 *m_ptr;
	void clear();
};

void Rva005F74A0::clear()
{
	Rva005F6A58 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F6A58::~Rva005F6A58();
		::operator delete(p);
	}
}

class Rva005FAD8D
{
public:
	~Rva005FAD8D();
};

class Rva005FAFB2
{
public:
	Rva005FAD8D *m_ptr;
	void clear();
};

void Rva005FAFB2::clear()
{
	Rva005FAD8D *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005FAD8D::~Rva005FAD8D();
		::operator delete(p);
	}
}

class Rva005FB615
{
public:
	~Rva005FB615();
};

class Rva005FBBA6
{
public:
	Rva005FB615 *m_ptr;
	void clear();
};

void Rva005FBBA6::clear()
{
	Rva005FB615 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005FB615::~Rva005FB615();
		::operator delete(p);
	}
}

class Rva005FCA8B
{
public:
	~Rva005FCA8B();
};

class Rva005FCB2D
{
public:
	Rva005FCA8B *m_ptr;
	void clear();
};

void Rva005FCB2D::clear()
{
	Rva005FCA8B *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005FCA8B::~Rva005FCA8B();
		::operator delete(p);
	}
}

class Rva005FD628
{
public:
	~Rva005FD628();
};

class Rva005FD95E
{
public:
	Rva005FD628 *m_ptr;
	void clear();
};

void Rva005FD95E::clear()
{
	Rva005FD628 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005FD628::~Rva005FD628();
		::operator delete(p);
	}
}

class Rva005FF5F6
{
public:
	~Rva005FF5F6();
};

class Rva005FF8F8
{
public:
	Rva005FF5F6 *m_ptr;
	void clear();
};

void Rva005FF8F8::clear()
{
	Rva005FF5F6 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005FF5F6::~Rva005FF5F6();
		::operator delete(p);
	}
}

class Rva004E6A37
{
public:
	Rva004E6935 *m_ptr;
	~Rva004E6A37();
};

Rva004E6A37::~Rva004E6A37()
{
	Rva004E6935 *p = m_ptr;
	if (p)
	{
		p->Rva004E6935::~Rva004E6935();
		::operator delete(p);
	}
}

class Rva0023A053
{
public:
	Rva00239D7A *m_ptr;
	void reset(Rva00239D7A *p);
};

void Rva0023A053::reset(Rva00239D7A *p)
{
	if (p != m_ptr)
	{
		Rva00239D7A *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva00239D7A::~Rva00239D7A();
			::operator delete(old);
		}
	}
}

class Rva0057B993
{
public:
	Rva005D4FFC *m_ptr;
	void reset(Rva005D4FFC *p);
};

void Rva0057B993::reset(Rva005D4FFC *p)
{
	if (p != m_ptr)
	{
		Rva005D4FFC *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva005D4FFC::~Rva005D4FFC();
			::operator delete(old);
		}
	}
}

class Rva005CE236
{
public:
	Rva005E893E *m_ptr;
	void reset(Rva005E893E *p);
};

void Rva005CE236::reset(Rva005E893E *p)
{
	if (p != m_ptr)
	{
		Rva005E893E *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva005E893E::~Rva005E893E();
			::operator delete(old);
		}
	}
}

class Rva005D3731
{
public:
	~Rva005D3731();
};

class Rva00578701
{
public:
	Rva005D3731 *m_ptr;
	void reset(Rva005D3731 *p);
};

void Rva00578701::reset(Rva005D3731 *p)
{
	if (p != m_ptr)
	{
		Rva005D3731 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva005D3731::~Rva005D3731();
			::operator delete(old);
		}
	}
}

class Rva002B4326
{
public:
	Rva004FA2E2 *m_ptr;
	void reset(Rva004FA2E2 *p);
};

void Rva002B4326::reset(Rva004FA2E2 *p)
{
	if (p != m_ptr)
	{
		Rva004FA2E2 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva004FA2E2::~Rva004FA2E2();
			::operator delete(old);
		}
	}
}

class Rva002B4349
{
public:
	Rva004FA2E2 *m_ptr;
	~Rva002B4349();
};

Rva002B4349::~Rva002B4349()
{
	Rva004FA2E2 *p = m_ptr;
	if (p)
	{
		p->Rva004FA2E2::~Rva004FA2E2();
		::operator delete(p);
	}
}

class Rva002D38AE
{
public:
	Rva0052710C *m_ptr;
	void reset(Rva0052710C *p);
};

void Rva002D38AE::reset(Rva0052710C *p)
{
	if (p != m_ptr)
	{
		Rva0052710C *old = m_ptr;
		m_ptr = p;
		if (old)
		{
		old->Rva0052710C::~Rva0052710C();
		::operator delete(old);
		}
	}
}

class Rva005E7FE2
{
public:
	Rva005E7D72 *m_ptr;
	void reset(Rva005E7D72 *p);
};

void Rva005E7FE2::reset(Rva005E7D72 *p)
{
	if (p != m_ptr)
	{
		Rva005E7D72 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva005E7D72::~Rva005E7D72();
			::operator delete(old);
		}
	}
}

class Rva0042D85A
{
public:
	Rva0057BD01 *m_ptr;
	void reset(Rva0057BD01 *p);
};

void Rva0042D85A::reset(Rva0057BD01 *p)
{
	if (p != m_ptr)
	{
		Rva0057BD01 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva0057BD01::~Rva0057BD01();
			::operator delete(old);
		}
	}
}

class Rva000AF160
{
public:
	Rva000AD71D *m_ptr;
	void reset(Rva000AD71D *p);
};

void Rva000AF160::reset(Rva000AD71D *p)
{
	if (p != m_ptr)
	{
		Rva000AD71D *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva000AD71D::~Rva000AD71D();
			::operator delete(old);
		}
	}
}

class Rva005F1295
{
public:
	~Rva005F1295();
};

class Rva005F13CC
{
public:
	Rva005F1295 *m_ptr;
	void clear();
};

void Rva005F13CC::clear()
{
	Rva005F1295 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005F1295::~Rva005F1295();
		::operator delete(p);
	}
}

class Rva0042D766
{
public:
	Rva00578C43 *m_ptr;
	void reset(Rva00578C43 *p);
};

void Rva0042D766::reset(Rva00578C43 *p)
{
	if (p != m_ptr)
	{
		Rva00578C43 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva00578C43::~Rva00578C43();
			::operator delete(old);
		}
	}
}

class Rva002D38EB
{
public:
	Rva00527CCE *m_ptr;
	void reset(Rva00527CCE *p);
};

void Rva002D38EB::reset(Rva00527CCE *p)
{
	if (p != m_ptr)
	{
		Rva00527CCE *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva00527CCE::~Rva00527CCE();
			::operator delete(old);
		}
	}
}

class Rva002D390E
{
public:
	Rva00527FA2 *m_ptr;
	void reset(Rva00527FA2 *p);
};

void Rva002D390E::reset(Rva00527FA2 *p)
{
	if (p != m_ptr)
	{
		Rva00527FA2 *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva00527FA2::~Rva00527FA2();
			::operator delete(old);
		}
	}
}

class Rva002B90B3
{
public:
	Rva002B74DE *m_ptr;
	void reset(Rva002B74DE *p);
};

void Rva002B90B3::reset(Rva002B74DE *p)
{
	if (p != m_ptr)
	{
		Rva002B74DE *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva002B74DE::~Rva002B74DE();
			::operator delete(old);
		}
	}
}

class Rva0029B5FD
{
public:
	Rva004E668E *m_ptr;
	void reset(Rva004E668E *p);
};

void Rva0029B5FD::reset(Rva004E668E *p)
{
	if (p != m_ptr)
	{
		Rva004E668E *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva004E668E::~Rva004E668E();
			::operator delete(old);
		}
	}
}

// ?reset@Rva0042C1BC@@QAEXPAVRva0057417E@@@Z @0x0042C1BC 35B evidence: leaf reset same pointee as clear 0x0042C1DF via 2 callers in 0x0042C342; callees rowed plus pin 0x0057417E
class Rva0042C1BC
{
public:
	Rva0057417E *m_ptr;
	void reset(Rva0057417E *p);
};

void Rva0042C1BC::reset(Rva0057417E *p)
{
	if (p != m_ptr)
	{
		Rva0057417E *old = m_ptr;
		m_ptr = p;
		if (old)
		{
			old->Rva0057417E::~Rva0057417E();
			::operator delete(old);
		}
	}
}

class Rva00526F80
{
public:
	void rva00526F80();
};

void Rva00526F80::rva00526F80()
{
	((Rva00526F2C *)this)->clear();
}

Rva00527FA2::~Rva00527FA2()
{
	((Rva00527F88 *)this)->clear();
}

class Rva005288B8
{
public:
	void rva005288B8();
};

void Rva005288B8::rva005288B8()
{
	((Rva005287D0 *)this)->clear();
}

Rva005D4FFC::~Rva005D4FFC()
{
	((Rva005D4FA0 *)this)->clear();
}


