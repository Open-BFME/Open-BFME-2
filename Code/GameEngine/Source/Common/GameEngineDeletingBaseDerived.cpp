// cl: /O1 /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// Opaque derived constructors and destructors. The destructors tail-call the
// verified SubsystemInterface destructor at 0x001B4E74. Its vtable and name
// member at +0x08 establish the base identity; derived owner names remain
// unknown. Use the existing native header, including its full base layout and
// virtual interface.

typedef bool Bool;
#include "spline_service.h"

class Rva00221027 : public SubsystemInterface
{
public:
	virtual ~Rva00221027();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
};

Rva00221027::~Rva00221027()
{
}

Rva0022B3F6Subsystem::Rva0022B3F6Subsystem()
{
}

Rva0022B3F6Subsystem::~Rva0022B3F6Subsystem()
{
}

class Rva0025DB46 : public SubsystemInterface
{
public:
	Rva0025DB46();
	virtual ~Rva0025DB46();
};

Rva0025DB46::Rva0025DB46()
{
}

Rva0025DB46::~Rva0025DB46()
{
}

class Rva0026201C : public SubsystemInterface
{
public:
	Rva0026201C();
	virtual ~Rva0026201C();

private:
	int m_0C;
	int m_10;
};

// ??0Rva0026201C@@QAE@XZ retail 0x00262002 26B: base ctor 0x001B4E63, +0x0C
// and +0x10 cleared, own vptr 0x00BF9010.
Rva0026201C::Rva0026201C()
{
	m_0C = 0;
	m_10 = 0;
}

Rva0026201C::~Rva0026201C()
{
}

class Rva002D22CA : public SubsystemInterface
{
public:
	virtual ~Rva002D22CA();
};

Rva002D22CA::~Rva002D22CA()
{
}

class Rva002E55D8 : public SubsystemInterface
{
public:
	Rva002E55D8();
	virtual ~Rva002E55D8();
	// Retail table 0x00C04E90: 8 __purecall entries follow SubsystemInterface's 14 slots.
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
};

// ??0Rva002E55D8@@QAE@XZ retail 0x002E55FF 18B: base ctor 0x001B4E63 then own
// vptr 0x00804E90.
Rva002E55D8::Rva002E55D8()
{
}

Rva002E55D8::~Rva002E55D8()
{
}

class Rva003BA6A9 : public SubsystemInterface
{
public:
	virtual ~Rva003BA6A9();
	// Retail table 0x00C1FD98: 4 __purecall entries follow SubsystemInterface's 14 slots.
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
};

Rva003BA6A9::~Rva003BA6A9()
{
}

class Rva003E3BD4 : public SubsystemInterface
{
public:
	Rva003E3BD4();
	virtual ~Rva003E3BD4();
	// Retail table 0x00C35AE0: 4 __purecall entries follow SubsystemInterface's 14 slots.
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
};

Rva003E3BD4::Rva003E3BD4()
{
}

Rva003E3BD4::~Rva003E3BD4()
{
}

struct BfmeNarrowRecord0041A5D2;
struct BfmeNarrowRecord0041A617;
struct BfmePod16;

// Retail table 0x00C3AD08: SubsystemInterface's fourteen slots, then the
// queue interface's eight pure slots (14-21), as GameResultsQueueStartup_
// Unresolved.cpp declares them. The destructor is inline, as in Zero Hour:
// GameResultsQueue's destructor 0x0041A644 inlines it, and the deleting
// destructor 0x00419CDF calls this unit's out-of-line copy 0x00419CD4.
class GameResultsInterface : public SubsystemInterface
{
public:
	GameResultsInterface();
	virtual ~GameResultsInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual bool areThreadsRunning() = 0;
	virtual void addRequest(const BfmeNarrowRecord0041A5D2 &request) = 0;
	virtual bool getRequest(BfmeNarrowRecord0041A5D2 &request) = 0;
	virtual void addResponse(const BfmePod16 &response) = 0;
	virtual bool getResponse(BfmeNarrowRecord0041A617 &response) = 0;
	virtual bool areGameResultsBeingSent() = 0;
};

GameResultsInterface::GameResultsInterface()
{
}

class ActionManager : public SubsystemInterface
{
public:
	ActionManager();
	virtual ~ActionManager();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
};

// ??0Rva0041B8C7@@QAE@XZ retail 0x0041B8B5 18B: base ctor 0x001B4E63 then own
// vptr 0x00C3AE60 (caller 0x0022FA81).
ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

class Rva0041FE0E : public SubsystemInterface
{
public:
	virtual ~Rva0041FE0E();
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class Rva0044954D : public SubsystemInterface
{
public:
	Rva0044954D();
	virtual ~Rva0044954D();
	// Retail table 0x00C3E588: 47 __purecall entries follow SubsystemInterface's 14 slots.
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
};

Rva0044954D::Rva0044954D()
{
}

Rva0044954D::~Rva0044954D()
{
}

// ??1Rva0041FE0E is a header inline elsewhere: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva0041FE0EDtor@@YAXPAVRva0041FE0E@@@Z present-unmatched
void bfmeEmitRva0041FE0EDtor(Rva0041FE0E *subsystem)
{
	subsystem->Rva0041FE0E::~Rva0041FE0E();
}
#pragma inline_depth()
