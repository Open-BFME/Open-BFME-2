// cl: /DNDEBUG /MD
// Six chained default ctors: each zeroes its leading ints via member
// initializers, then implicitly constructs the trailing member (whose
// default ctor it tail-calls after the stores, returning this):
// 22B trio (two leading ints, member at +8):
//   0x001FA5A5 -> rowed Rva001F9060::Rva001F9060,
//   0x001FBA45 -> 0x001FA5A5, 0x001FBF37 -> 0x001FBA45 (this unit's rows);
// 18B trio (one leading int, member at +4):
//   0x001FB8A9 -> 0x001FA5A5, 0x001FBBE4 -> 0x001FBA45,
//   0x003B44DC -> 0x003B417E (opaque pin).
// The member types are minimal redeclarations carrying only the offset the
// codegen needs; the ctor calls resolve through the rowed and pinned names.
// Names are address-derived. One ledger row per ctor.

class Rva001F9060
{
public:
	Rva001F9060();
};

class Rva003B417E
{
public:
	Rva003B417E();
};

class Rva001FA5A5
{
public:
	Rva001FA5A5();

private:
	int m_00;
	int m_04;
	Rva001F9060 m_sub;
};

class Rva001FBA45
{
public:
	Rva001FBA45();

private:
	int m_00;
	int m_04;
	Rva001FA5A5 m_sub;
};

class Rva001FBF37
{
public:
	Rva001FBF37();

private:
	int m_00;
	int m_04;
	Rva001FBA45 m_sub;
};

class Rva001FB8A9
{
public:
	Rva001FB8A9();

private:
	int m_00;
	Rva001FA5A5 m_sub;
};

class Rva001FBBE4
{
public:
	Rva001FBBE4();

private:
	int m_00;
	Rva001FBA45 m_sub;
};

class Rva003B44DC
{
public:
	Rva003B44DC();

private:
	int m_00;
	Rva003B417E m_sub;
};

// The Rva001FA5A5, Rva001FBA45, Rva001FB8A9 and Rva001FBBE4 ctors are rows of
// GameLogic/Object/Rva001FA5A5Ctor.cpp; this unit only declares them.


Rva003B44DC::Rva003B44DC()
	: m_00(0)
{
}
