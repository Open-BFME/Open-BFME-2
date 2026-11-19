// cl: /DNDEBUG /MD /EHsc
// ??1Rva0022C0CDSubsystem@@UAE@XZ @0x002E0427 81B dtor over two hash members and SubsystemInterface
// Vtable 0x00BE7628 slot 0 (deleting dtor 0x0022DA4A calls here); members at +0x10
// (Rva0022CC67 dtor 0x0022CF13) and +0x24 (Rva0022366C dtor 0x0022366C) with base
// 0x001B4E74; global TheLivingWorldBuildingTemplateStore cleared. Evidence: chain packet callees all rowed.

// TheLivingWorldBuildingTemplateStore (.data 0x009FF09C): the store this dtor
// clears; its own INI block parser 0x002E048C (next in retail) and the living
// world consumers read it. Defined here, with the store implementation.
class Rva0022C0CDSubsystem;
Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore = 0;

class Rva0022CC67
{
public:
	~Rva0022CC67();
private:
	char m_pad[0x14];
};

class Rva0022366C
{
public:
	~Rva0022366C();
private:
	char m_pad[0x14];
};

// Native normal teardown reaches the hash backend at22CF13, while the
// member unwind reaches its separate5B forwarder at22D101. This empty
// lifetime view keeps both witnessed entries: inline teardown of its base
// and the emitted wrapper destructor. The inheritance is a structural
// representation of the unadjusted receiver, not an original class claim.
class Rva0022D101Member : public Rva0022CC67
{
public:
	~Rva0022D101Member() {}
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva0022C0CDSubsystem : public SubsystemInterface
{
public:
	virtual ~Rva0022C0CDSubsystem();
private:
	int m_0C;
	Rva0022D101Member m_10;
	Rva0022366C m_24;
};

Rva0022C0CDSubsystem::~Rva0022C0CDSubsystem()
{
	TheLivingWorldBuildingTemplateStore = 0;
}

// GameEngine::init's Rva0022C0CDSubsystem (ctor 0x0022DA03) stores the same
// vtable 0x00BE7628, whose slot 0 0x0022DA4A calls this destructor.

// Native778668: complete11B member+10 destructor unwind. Whole81B parent
// and native EH graph prove ownership. Actual5B callee22D101 forwards to
// owned57B hash cleanup22CF13; original wrapper identity remains uncertain.
