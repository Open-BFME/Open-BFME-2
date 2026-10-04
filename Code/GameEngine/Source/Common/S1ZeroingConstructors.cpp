// Nine __thiscall constructors that zero a fixed set of members (trimmed to
// the placed Rva007E3A20 body; the other eight are declared-only here).

class Rva00351BC0
{
public:
	Rva00351BC0();
};

class Rva00351BD0
{
public:
	Rva00351BD0();
};

class Rva003A4300
{
public:
	Rva003A4300();
};

class Rva003BEA20
{
public:
	Rva003BEA20();
};

class Rva003F6A60
{
public:
	Rva003F6A60();
};

class Rva00339C20
{
public:
	Rva00339C20();
};

class Rva00739DE0
{
public:
	Rva00739DE0();
};

class Rva003366B0
{
public:
	Rva003366B0();
};

// Three byte members, two adjacent at 0 and 1 and one far out at 0x105.
class Rva007E3A20
{
public:
	Rva007E3A20();
	unsigned char m_a;
	unsigned char m_b;
	char m_gap[ 0x103 ];
	unsigned char m_c;
};

// ??0Rva007E3A20@@QAE@XZ
Rva007E3A20::Rva007E3A20()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

// Additional raw zero-store operation from the whole BFME1 donor
// game/GameEngine/Source/Common/S1ZeroingConstructors.cpp, revision
// 5cc75ddda6455c338a5068307e587a793f96d6b3, blob
// b187205c78b391e963d12db299c952caf0cfa20f; no header dependencies.
// Discovery /O1 /Ob1 and /O2 /Ob1 /GX- /GS both place this body;
// the unchanged home settings preserve every existing body.
// Target entry 0x000724A0/14 follows the preceding RET. Its actual entry
// pointer is pushed at 0x000726D3 to the rowed EH vector constructor
// iterator 0x00629512, with element count1 and stride0x14. The body clears
// raw words at +8/+0xC/+0x10 and returns the incoming receiver address.
// This minimum ABI view preserves the operation without asserting an
// original class name, field meaning, full class definition or lifetime.
class Rva000724A0ZeroView
{
public:
	Rva000724A0ZeroView *rva000724A0();
private:
	unsigned char head[8];
	unsigned int a, b, c;
};

// ?rva000724A0@Rva000724A0ZeroView@@QAEPAV1@XZ
Rva000724A0ZeroView *Rva000724A0ZeroView::rva000724A0()
{
	a = 0;
	b = 0;
	c = 0;
	return this;
}
