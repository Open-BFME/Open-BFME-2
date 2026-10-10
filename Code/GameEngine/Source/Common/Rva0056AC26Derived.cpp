// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling Rva0056AC26::~
// Rva0056AC26 at 0x0056AC26 (pinned opaque MI base dtor: SEH, vptrs at
// +0x00/+0x08; identity unproven). Each class below derives (in order) from
// the opaque base and its own empty polymorphic base, giving vptrs at
// +0x00/+0x08. The empty base's first virtual is its destructor: retail
// slot 0 of each second vftable is an 8B this-8 thunk to the class's ??_G.
// It is novtable and inline, so the derived destructor still stores both
// vptrs and tail-calls the base destructor.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva0056AC26
{
public:
	virtual ~Rva0056AC26();
	virtual bool ac26Slot1();	// slot 1 (overridden by Rva0056ACFF below)

private:
	char m_pad04[4];
};

class __declspec(novtable) Rva0056AC82_B1
{
public:
	virtual ~Rva0056AC82_B1() {}
};

class Rva0056AC82 : public Rva0056AC26, public Rva0056AC82_B1
{
public:
	virtual ~Rva0056AC82();
};

Rva0056AC82::~Rva0056AC82()
{
}

class __declspec(novtable) Rva0056ACC5_B1
{
public:
	virtual ~Rva0056ACC5_B1() {}
};

class Rva0056ACC5 : public Rva0056AC26, public Rva0056ACC5_B1
{
public:
	virtual ~Rva0056ACC5();
};

Rva0056ACC5::~Rva0056ACC5()
{
}

class __declspec(novtable) Rva0056ACDF_B1
{
public:
	virtual ~Rva0056ACDF_B1() {}
};

class Rva0056ACDF : public Rva0056AC26, public Rva0056ACDF_B1
{
public:
	virtual ~Rva0056ACDF();
};

Rva0056ACDF::~Rva0056ACDF()
{
}

struct Rva002B4BC9Arg;

class __declspec(novtable) Rva0056ACFF_B1
{
public:
	virtual ~Rva0056ACFF_B1() {}
	virtual bool b1Slot1(Rva002B4BC9Arg *arg) = 0;	// slot 1
};

class Rva0056ACFF : public Rva0056AC26, public Rva0056ACFF_B1
{
public:
	virtual ~Rva0056ACFF();
	virtual bool ac26Slot1();
	virtual bool b1Slot1(Rva002B4BC9Arg *arg);
};

Rva0056ACFF::~Rva0056ACFF()
{
}

class __declspec(novtable) Rva0056AE4A_B1
{
public:
	virtual ~Rva0056AE4A_B1() {}
};

class Rva0056AE4A : public Rva0056AC26, public Rva0056AE4A_B1
{
public:
	virtual ~Rva0056AE4A();
};

Rva0056AE4A::~Rva0056AE4A()
{
}

// Slot 1 of each of Rva0056ACFF's two tables forwards to a rowed query on
// the living-world logic singleton (ecx = TheLivingWorldLogic, then a tail
// jump): 0x0056ABC0 in the Rva0056AC26 table (0x0086D19C) to 0x002B32CE,
// 0x0056ABCB in the Rva0056ACFF_B1 table (0x0086D160) to 0x002B4BC9 with
// its one argument. Names are address-neutral slot placeholders.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002B32CE
{
public:
	bool rva002B32CE();
};

class Rva002B4BC9
{
public:
	bool rva002B4BC9(Rva002B4BC9Arg *arg);
};

bool Rva0056ACFF::ac26Slot1()
{
	return ((Rva002B32CE *)TheLivingWorldLogic)->rva002B32CE();
}

bool Rva0056ACFF::b1Slot1(Rva002B4BC9Arg *arg)
{
	return ((Rva002B4BC9 *)TheLivingWorldLogic)->rva002B4BC9(arg);
}
