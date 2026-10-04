// cl: /O1 /DNDEBUG /MD /EHsc
//
// Five of Win32GameEngine's subsystem factories (vtable 0x00BC2530), each
// Zero Hour's inline `return NEW X;` shape: the global operator new of the
// object's size, then its constructor, under an EH frame that frees the block
// if the constructor throws. Rva00041DC9Create.cpp holds slot 33 the same way.
// Each product is named after its destructor, as the ledger already names it
// (the constructor stores the vtable the named scalar deleting destructor
// sits in); the constructors are pinned in reverse/symbols.csv. Which Zero
// Hour factory each slot is (createGameLogic and the rest) is not evidenced:
// the slot order differs from Zero Hour's and the products are unnamed,
// except that slot 34's product table carries Radar::loadPostProcess.
//
//   slot 29  0x00041D62  new 0x140   ctor 0x0004C43E  vtable 0x00BC4738  Rva004C743
//   slot 32  0x00041D97  new 0x28    ctor 0x0004CA01  vtable 0x00BC4858  Rva004CA13
//   slot 34  0x00041E30  new 0x1504  ctor 0x0004F8EA  vtable 0x00BC4E34  Rva004FA1F
//   slot 36  0x0005E959  new 0xC08   ctor 0x0005CF5F  vtable 0x00BC55B0  Rva0060FE2
//   slot 37  0x00041E6A  new 0x32C   ctor 0x000628EB  vtable 0x00BC57E0  Rva00628FD
//
// Slots 28 and 31 make a class derived from a two-vptr base (its primary
// table at +0, a Snapshot table at +0x0C, the constructor pinned) whose own
// constructor retail expands in place: the base constructor call and then the
// derived class's two table stores. /O1 keeps an inline constructor out of
// line here, so it is __forceinline. These derived classes are named after
// the destructors their scalar deleting destructors call.
//
//   slot 28  0x00041F81  new 0x2A8   base ctor 0x002470AE  vtables 0x00BC25E0/0x00BC25D0  dtor 0x0004208C
//   slot 31  0x00042091  new 0x28    base ctor 0x00256E19  vtables 0x00BC2640/0x00BC2630  dtor 0x00042100

class Rva004C743
{
public:
	Rva004C743();
private:
	char m_unmodelled[0x140];
};

class Rva004CA13
{
public:
	Rva004CA13();
private:
	char m_unmodelled[0x28];
};

class Rva004FA1F
{
public:
	Rva004FA1F();
private:
	char m_unmodelled[0x1504];
};

class Rva0060FE2
{
public:
	Rva0060FE2();
private:
	char m_unmodelled[0xC08];
};

class Rva00628FD
{
public:
	Rva00628FD();
private:
	char m_unmodelled[0x32C];
};

// The base's primary interface (vptr plus two words) and its Snapshot.
class Rva002470AEFirst
{
public:
	virtual ~Rva002470AEFirst();
private:
	char m_unmodelled_04[0x0C - 0x04];
};

class Rva002470AESnapshot
{
public:
	virtual void slot00();
};

class Rva002470AEBase : public Rva002470AEFirst, public Rva002470AESnapshot
{
public:
	Rva002470AEBase();
private:
	char m_unmodelled_10[0x2A8 - 0x10];
};

class Rva0004208C : public Rva002470AEBase
{
public:
	__forceinline Rva0004208C() {}
	virtual ~Rva0004208C();
};

class Rva00256E19Base : public Rva002470AEFirst, public Rva002470AESnapshot
{
public:
	Rva00256E19Base();
private:
	char m_unmodelled_10[0x28 - 0x10];
};

class Rva00042100 : public Rva00256E19Base
{
public:
	__forceinline Rva00042100() {}
	virtual ~Rva00042100();
};

class Win32GameEngine
{
public:
	virtual void *rva00041D62();
	virtual void *rva00041D97();
	virtual void *rva00041E30();
	virtual void *rva0005E959();
	virtual void *rva00041E6A();
	virtual void *rva00041F81();
	virtual void *rva00042091();
};

void *Win32GameEngine::rva00041D62()
{
	return new Rva004C743;
}

void *Win32GameEngine::rva00041D97()
{
	return new Rva004CA13;
}

void *Win32GameEngine::rva00041E30()
{
	return new Rva004FA1F;
}

void *Win32GameEngine::rva0005E959()
{
	return new Rva0060FE2;
}

void *Win32GameEngine::rva00041E6A()
{
	return new Rva00628FD;
}

void *Win32GameEngine::rva00041F81()
{
	return new Rva0004208C;
}

void *Win32GameEngine::rva00042091()
{
	return new Rva00042100;
}
