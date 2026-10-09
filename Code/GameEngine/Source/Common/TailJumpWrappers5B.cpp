// cl: /DNDEBUG /MD
//
// Five-byte wrappers whose whole retail body is one unadjusted `jmp` to an
// already-rowed body. Each name is the pin its matched callers link against
// (reverse/symbols.csv notes give the call sites); the targets are declared,
// not defined, so every jump resolves to the target's own row.
//
// Destructors: a slot-0 scalar deleting destructor calls each one, and the
// body is the base destructor's tail jump with no vptr store, so the derived
// class is novtable over the base it jumps to (the HordeGarrisonContainDtor /
// UVBufferClassDtor shape). Owner identities are not recovered.
//
//   dtor        base dtor   deleting dtor  vtable#slot
//   0x006D6340  0x006DE350  0x006CD620/0x006D71B0 (unwind 0x007A8030, 0x007AA290)
//   0x00574BA0  0x005746D2  0x00574B84     0x00C6E3CC#0
//   0x005EA85A  0x005FC1E4  0x005EA83E     0x00C781DC#0
//   0x005CC677  0x005E21EB  0x005CC65B     0x00C74E8C#0
//   0x00574338  0x005CB8D4  0x00574693     0x00C6E39C#0
//   0x005D13BD  0x005EE05E  0x005D13A1     0x00C755C0#0
//   0x005CC656  0x005E1FBC  0x005CC63A     0x00C74E70#0
//
// Methods: the same jump with the receiver and arguments passed through.
//
//   wrapper     target      caller
//   0x002710E7  0x0030AA80  0x0004C86B Drawable::setPosition -> Thing's
//   0x005C6CC7  0x005C6C89  0x00577E43
//   0x00596074  0x0025C010  0x004DF95D
//   0x0035AA3E  0x0035A1D8  GameLogic::init 0x00243EE7
//   0x0057E6D8  0x0057E6C1  0x0043DCD0
//   0x003FACE4  0x003FAC3F  0x00213AB6
//   0x004FCA0C  0x004FC9CE  0x0052BAE9
//
// Drawable deriving from Thing at offset 0 is carried from the Zero Hour
// donor (GameClient/Drawable.h); the unadjusted jump agrees with it.

class Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

class __declspec(novtable) BfmeAptValue006DCD20 : public Rva006DE350
{
public:
	virtual ~BfmeAptValue006DCD20();
};

BfmeAptValue006DCD20::~BfmeAptValue006DCD20()
{
}

class Rva005746AF
{
public:
	virtual ~Rva005746AF();
};

class __declspec(novtable) Rva005747DA : public Rva005746AF
{
public:
	virtual ~Rva005747DA();
};

Rva005747DA::~Rva005747DA()
{
}

class Rva005FC1E4
{
public:
	virtual ~Rva005FC1E4();
};

class __declspec(novtable) Rva005EA85A : public Rva005FC1E4
{
public:
	virtual ~Rva005EA85A();
};

Rva005EA85A::~Rva005EA85A()
{
}

class Rva005E21EB
{
public:
	virtual ~Rva005E21EB();
};

class __declspec(novtable) Rva005CC677 : public Rva005E21EB
{
public:
	virtual ~Rva005CC677();
};

Rva005CC677::~Rva005CC677()
{
}

class Rva005CB8D4
{
public:
	virtual ~Rva005CB8D4();
};

class __declspec(novtable) Rva00574338 : public Rva005CB8D4
{
public:
	virtual ~Rva00574338();
};

Rva00574338::~Rva00574338()
{
}

class Rva005EE05E
{
public:
	virtual ~Rva005EE05E();
};

class __declspec(novtable) Rva005D13BD : public Rva005EE05E
{
public:
	virtual ~Rva005D13BD();
};

Rva005D13BD::~Rva005D13BD()
{
}

class Rva005E1FBC
{
public:
	virtual ~Rva005E1FBC();
};

class __declspec(novtable) Rva005CC656 : public Rva005E1FBC
{
public:
	virtual ~Rva005CC656();
};

Rva005CC656::~Rva005CC656()
{
}

struct Coord3D;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Drawable : public Thing
{
public:
	void setPosition(const Coord3D *pos);
};

void Drawable::setPosition(const Coord3D *pos)
{
	Thing::setPosition(pos);
}

class Rva005C6C7B
{
public:
	void reset();
};

class Rva005C6CC7Call
{
public:
	void rva005C6CC7();
};

void Rva005C6CC7Call::rva005C6CC7()
{
	((Rva005C6C7B *)this)->reset();
}

class Rva0025C010
{
public:
	void rva0025C010();
};

class Rva00596074
{
public:
	void rva00596074();
};

void Rva00596074::rva00596074()
{
	((Rva0025C010 *)this)->rva0025C010();
}

class Rva0035A1D8
{
public:
	void rva0035A1D8();
};

class Rva00359E13
{
public:
	void rva0035AA3E();
};

void Rva00359E13::rva0035AA3E()
{
	((Rva0035A1D8 *)this)->rva0035A1D8();
}

class AptMpGameRules
{
public:
	void rva0057E6C1();
};

class Rva0057EE5C
{
public:
	void rva0057E6D8();
};

void Rva0057EE5C::rva0057E6D8()
{
	((AptMpGameRules *)this)->rva0057E6C1();
}

class Rva003FAC3F
{
public:
	void rva003FAC3F();
};

class Rva003FAC83
{
public:
	void rva003FACE4();
};

void Rva003FAC83::rva003FACE4()
{
	((Rva003FAC3F *)this)->rva003FAC3F();
}

class Rva0059E2FD;

class Rva004FC9CE
{
public:
	void *rva004FC9CE(const Rva0059E2FD &key);
};

class Rva0020E89C;
struct Res004FCA0C;

class Sub0052BAC1
{
public:
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *key);
};

Res004FCA0C *Sub0052BAC1::Rva004FCA0C(Rva0020E89C *key)
{
	return (Res004FCA0C *)((Rva004FC9CE *)this)->rva004FC9CE(*(const Rva0059E2FD *)key);
}
