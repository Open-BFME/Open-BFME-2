// cl: /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner and no Ghidra entry, batch
// AP: each loads a member pointer (or takes a member's address) and
// tail-jumps to an unrowed Ghidra-listed function, pinned in
// reverse/symbols.csv under an address-derived name with the argument count
// its ret shows. Classes are address-derived and model only the member.

typedef int Int;

class Rva00078AE3
{
public:
	__declspec(noinline) Rva00078AE3& rva00078AE3(const Rva00078AE3 *other);
private:
	unsigned int bits00 : 3;
	unsigned int bits03 : 27;
	unsigned int bit30 : 1;
	unsigned int word04, word08, word0C;
};

// Native 00078AE3..00078B2B is a 72-byte self-guarded copy returning this.
// Retail separately merges bits 0..2, 3..29 and 30, preserving bit 31,
// then copies the three remaining dwords. Original class identity is unknown.
Rva00078AE3& Rva00078AE3::rva00078AE3(const Rva00078AE3 *other)
{
	if (other != this)
	{
		bits00 = other->bits00;
		bits03 = other->bits03;
		bit30 = other->bit30;
		word04 = other->word04;
		word08 = other->word08;
		word0C = other->word0C;
	}
	return *this;
}
class Rva00078ADB
{
public:
	void rva00078ADB(Int a0);
private:
	char m_pad00[0x1C];
	Rva00078AE3 m_1C;
};
void Rva00078ADB::rva00078ADB(Int a0)
{
	m_1C.rva00078AE3(reinterpret_cast<const Rva00078AE3*>(a0));
}

class Rva000B0F82
{
public:
	void rva000B0F82(Int a0, Int a1);
};
class Rva000B197C
{
public:
	void rva000B197C(Int a0, Int a1);
private:
	char m_pad00[0x0C];
	Rva000B0F82 *m_0C;
};
void Rva000B197C::rva000B197C(Int a0, Int a1)
{
	m_0C->rva000B0F82(a0, a1);
}

class Rva005254C5
{
public:
	void rva005254C5(Int a0);
};
class Rva005259B1
{
public:
	void rva005259B1(Int a0);
private:
	char m_pad00[0x08];
	Rva005254C5 m_08;
};
void Rva005259B1::rva005259B1(Int a0)
{
	m_08.rva005254C5(a0);
}

class Rva00527BA2
{
public:
	void rva00527BA2(Int a0, Int a1, Int a2);
};
class Rva00527B9A
{
public:
	void rva00527B9A(Int a0, Int a1, Int a2);
private:
	char m_pad00[0x04];
	Rva00527BA2 *m_04;
};
void Rva00527B9A::rva00527B9A(Int a0, Int a1, Int a2)
{
	m_04->rva00527BA2(a0, a1, a2);
}

class Rva005394F0
{
public:
	void rva005394F0(Int a0, Int a1);
};
class Rva00539611
{
public:
	void rva00539611(Int a0, Int a1);
private:
	char m_pad00[0x08];
	Rva005394F0 *m_08;
};
void Rva00539611::rva00539611(Int a0, Int a1)
{
	m_08->rva005394F0(a0, a1);
}

class Rva0053973F
{
public:
	void rva0053973F(Int a0);
};
class Rva005397D3
{
public:
	void rva005397D3(Int a0);
private:
	char m_pad00[0x08];
	Rva0053973F *m_08;
};
void Rva005397D3::rva005397D3(Int a0)
{
	m_08->rva0053973F(a0);
}

class Rva0056CA31
{
public:
	void rva0056CA31(Int a0);
};
class Rva0056D2BD
{
public:
	void rva0056D2BD(Int a0);
private:
	char m_pad00[0x08];
	Rva0056CA31 *m_08;
};
void Rva0056D2BD::rva0056D2BD(Int a0)
{
	m_08->rva0056CA31(a0);
}

class Rva0056CCE2
{
public:
	void rva0056CCE2(Int a0, Int a1);
};
class Rva0056D2C5
{
public:
	void rva0056D2C5(Int a0, Int a1);
private:
	char m_pad00[0x08];
	Rva0056CCE2 *m_08;
};
void Rva0056D2C5::rva0056D2C5(Int a0, Int a1)
{
	m_08->rva0056CCE2(a0, a1);
}

class Rva005757F9
{
public:
	void rva005757F9(Int a0);
};
class Rva00575DBA
{
public:
	void rva00575DBA(Int a0);
private:
	char m_pad00[0x08];
	Rva005757F9 *m_08;
};
void Rva00575DBA::rva00575DBA(Int a0)
{
	m_08->rva005757F9(a0);
}

class Rva0057590E
{
public:
	void rva0057590E(Int a0);
};
class Rva00575DC2
{
public:
	void rva00575DC2(Int a0);
private:
	char m_pad00[0x08];
	Rva0057590E *m_08;
};
void Rva00575DC2::rva00575DC2(Int a0)
{
	m_08->rva0057590E(a0);
}

class Rva005759A5
{
public:
	void rva005759A5(Int a0);
};
class Rva00575DCA
{
public:
	void rva00575DCA(Int a0);
private:
	char m_pad00[0x08];
	Rva005759A5 *m_08;
};
void Rva00575DCA::rva00575DCA(Int a0)
{
	m_08->rva005759A5(a0);
}

class Rva00575A3F
{
public:
	void rva00575A3F(Int a0);
};
class Rva00575DD2
{
public:
	void rva00575DD2(Int a0);
private:
	char m_pad00[0x08];
	Rva00575A3F *m_08;
};
void Rva00575DD2::rva00575DD2(Int a0)
{
	m_08->rva00575A3F(a0);
}

class Rva00576D0D
{
public:
	void rva00576D0D();
};
class Rva00576DCD
{
public:
	void rva00576DCD();
private:
	char m_pad00[0x08];
	Rva00576D0D *m_08;
};
void Rva00576DCD::rva00576DCD()
{
	m_08->rva00576D0D();
}

class Rva0057718D
{
public:
	void rva0057718D();
};
class Rva005772FA
{
public:
	void rva005772FA();
private:
	char m_pad00[0x08];
	Rva0057718D *m_08;
};
void Rva005772FA::rva005772FA()
{
	m_08->rva0057718D();
}

class Rva005D46E3
{
public:
	void rva005D46E3(Int a0);
};
class Rva0057A362
{
public:
	void rva0057A362(Int a0);
private:
	char m_pad00[0x08];
	Rva005D46E3 m_08;
};
void Rva0057A362::rva0057A362(Int a0)
{
	m_08.rva005D46E3(a0);
}

class Rva005D3F8D
{
public:
	void rva005D3F8D();
};
class Rva0057A36A
{
public:
	void rva0057A36A();
private:
	char m_pad00[0x08];
	Rva005D3F8D m_08;
};
void Rva0057A36A::rva0057A36A()
{
	m_08.rva005D3F8D();
}

class Rva005D3F93
{
public:
	void rva005D3F93(Int a0);
};
class Rva0057A372
{
public:
	void rva0057A372(Int a0);
private:
	char m_pad00[0x08];
	Rva005D3F93 m_08;
};
void Rva0057A372::rva0057A372(Int a0)
{
	m_08.rva005D3F93(a0);
}

class Rva005D4E37
{
public:
	void rva005D4E37(Int a0, Int a1, Int a2);
};
class Rva0057AA3D
{
public:
	void rva0057AA3D(Int a0, Int a1, Int a2);
private:
	char m_pad00[0x08];
	Rva005D4E37 m_08;
};
void Rva0057AA3D::rva0057AA3D(Int a0, Int a1, Int a2)
{
	m_08.rva005D4E37(a0, a1, a2);
}

class Rva0059B428
{
public:
	void rva0059B428(Int a0, Int a1, Int a2);
};
class Rva0059B420
{
public:
	void rva0059B420(Int a0, Int a1, Int a2);
private:
	char m_pad00[0x04];
	Rva0059B428 *m_04;
};
void Rva0059B420::rva0059B420(Int a0, Int a1, Int a2)
{
	m_04->rva0059B428(a0, a1, a2);
}

class Rva005C33DD
{
public:
	void rva005C33DD();
};
class Rva005C3586
{
public:
	void rva005C3586();
private:
	char m_pad00[0x08];
	Rva005C33DD *m_08;
};
void Rva005C3586::rva005C3586()
{
	m_08->rva005C33DD();
}

class Rva005C3427
{
public:
	void rva005C3427();
};
class Rva005C358E
{
public:
	void rva005C358E();
private:
	char m_pad00[0x08];
	Rva005C3427 *m_08;
};
void Rva005C358E::rva005C358E()
{
	m_08->rva005C3427();
}

class Rva005C3453
{
public:
	void rva005C3453();
};
class Rva005C3596
{
public:
	void rva005C3596();
private:
	char m_pad00[0x08];
	Rva005C3453 *m_08;
};
void Rva005C3596::rva005C3596()
{
	m_08->rva005C3453();
}

class Rva005C349D
{
public:
	void rva005C349D();
};
class Rva005C359E
{
public:
	void rva005C359E();
private:
	char m_pad00[0x08];
	Rva005C349D *m_08;
};
void Rva005C359E::rva005C359E()
{
	m_08->rva005C349D();
}

class Rva005CB9D1
{
public:
	void rva005CB9D1(Int a0);
};
class Rva005CBAE6
{
public:
	void rva005CBAE6(Int a0);
private:
	char m_pad00[0x04];
	Rva005CB9D1 m_04;
};
void Rva005CBAE6::rva005CBAE6(Int a0)
{
	m_04.rva005CB9D1(a0);
}

class Rva005CEA1C
{
public:
	void rva005CEA1C();
};
class Rva005CEA35
{
public:
	void rva005CEA35();
private:
	char m_pad00[0x08];
	Rva005CEA1C *m_08;
};
void Rva005CEA35::rva005CEA35()
{
	m_08->rva005CEA1C();
}

class Rva00574192
{
public:
	void rva00574192();
};
class Rva005CF8DB
{
public:
	void rva005CF8DB();
private:
	char m_pad00[0x08];
	Rva00574192 m_08;
};
void Rva005CF8DB::rva005CF8DB()
{
	m_08.rva00574192();
}

class Rva005F3F9A
{
public:
	void rva005F3F9A();
};
class Rva005F3FF4
{
public:
	void rva005F3FF4();
private:
	char m_pad00[0x08];
	Rva005F3F9A *m_08;
};
void Rva005F3FF4::rva005F3FF4()
{
	m_08->rva005F3F9A();
}

class Rva005F40B0
{
public:
	void rva005F40B0();
};
class Rva005F41AF
{
public:
	void rva005F41AF();
private:
	char m_pad00[0x08];
	Rva005F40B0 *m_08;
};
void Rva005F41AF::rva005F41AF()
{
	m_08->rva005F40B0();
}
