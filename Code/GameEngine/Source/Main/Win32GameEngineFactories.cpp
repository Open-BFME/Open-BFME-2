// cl: /DNDEBUG /MD /EHsc
//
// Five of Win32GameEngine's subsystem factories (vtable 0x00BC2530), each
// Zero Hour's inline `return NEW X;` shape: the global operator new of the
// object's size, then its constructor, under an EH frame that frees the block
// if the constructor throws. Rva00041DC9Create.cpp holds slot 33 the same way.
// Each product is named after its destructor, as the ledger already names it
// (the constructor stores the vtable the named scalar deleting destructor
// sits in); the constructors are pinned in reverse/symbols.csv. Slot 28 is
// createGameLogic: its product derives from GameLogic (ZH: NEW W3DGameLogic)
// and BFME 1's Win32GameEngine::createGameLogic is the same body. Which Zero
// Hour factory each other slot is is not evidenced: the slot order differs
// from Zero Hour's and the products are unnamed, except that slot 34's
// product table carries Radar::loadPostProcess.
//
//   slot 29  0x00041D62  new 0x140   ctor 0x0004C43E  vtable 0x00BC4738  Rva004C743
//   slot 32  0x00041D97  new 0x28    ctor 0x0004CA01  vtable 0x00BC4858  W3DThingFactory
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
//
// The derived vtables this TU emits also carry those classes' scalar
// deleting destructors (0x00042070, 0x000420E4: slot 0 of 0x00BC25E0 and
// 0x00BC2640) and, because the Snapshot base at +0x0C has a virtual
// destructor, the this-adjusting thunks in slot 0 of the secondary tables
// (0x00042068, 0x000420DC: sub ecx, 0xC then jump). The thunks name the
// vector deleting destructor, which the linker resolves to the scalar one
// (weak external), so no pin is needed. The
// destructors themselves (0x0004208C, 0x00042100) are lone tail jumps to
// their bases' destructors, defined in GapBodiesGE31.cpp. Slot 28's product
// is W3DGameLogic (ZH NEW W3DGameLogic; its slot 14 builds a 0x1924-byte
// terrain logic, ctor 0x00062A7E, as W3DGameLogic::createTerrainLogic does);
// slot 31's is W3DModuleFactory (slot 1 of its table is the rowed
// W3DModuleFactory::init 0x000652CA).

class Rva004C743
{
public:
	Rva004C743();
private:
	char m_unmodelled[0x140];
};

class W3DThingFactory
{
public:
	W3DThingFactory();
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

class MilesAudioManager
{
public:
	MilesAudioManager();
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
	virtual ~Rva002470AESnapshot();
};

// The product's base is GameLogic: its constructor is the rowed 0x002470AE.
// class-gate: allow GameLogic construction view: the shared header models no constructor and not the two-vptr 0x2A8-byte layout W3DGameLogic's inlined construction needs
class GameLogic : public Rva002470AEFirst, public Rva002470AESnapshot
{
public:
	GameLogic();
	virtual ~GameLogic();
private:
	char m_unmodelled_10[0x2A8 - 0x10];
};

class W3DTerrainLogic
{
public:
	W3DTerrainLogic();
private:
	char m_unmodelled[0x1924];
};

// Slot 14 of its vtable 0x00BC25E0 (0x00041FCF) is another factory of the
// same shape: new 0x1924 bytes and the constructor 0x00062A7E (pinned).
class W3DGameLogic : public GameLogic
{
public:
	__forceinline W3DGameLogic() {}
	virtual ~W3DGameLogic();
	void *rva00041FCF();
};

void *W3DGameLogic::rva00041FCF()
{
	return new W3DTerrainLogic;
}

class Rva00256E96 : public Rva002470AEFirst, public Rva002470AESnapshot
{
public:
	Rva00256E96();
	virtual ~Rva00256E96();
private:
	char m_unmodelled_10[0x28 - 0x10];
};

class W3DModuleFactory : public Rva00256E96
{
public:
	__forceinline W3DModuleFactory() {}
	virtual ~W3DModuleFactory();
};

class Win32GameEngine
{
public:
	virtual void *rva00041D62();
	virtual void *createThingFactory();
	virtual void *rva00041E30();
	virtual void *rva0005E959();
	virtual void *rva00041E6A();
	virtual void *createGameLogic();
	virtual void *createModuleFactory();
};

void *Win32GameEngine::rva00041D62()
{
	return new Rva004C743;
}

void *Win32GameEngine::createThingFactory()
{
	return new W3DThingFactory;
}

void *Win32GameEngine::rva00041E30()
{
	return new Rva004FA1F;
}

void *Win32GameEngine::rva0005E959()
{
	return new MilesAudioManager;
}

void *Win32GameEngine::rva00041E6A()
{
	return new Rva00628FD;
}

void *Win32GameEngine::createGameLogic()
{
	return new W3DGameLogic;
}

void *Win32GameEngine::createModuleFactory()
{
	return new W3DModuleFactory;
}
