// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1AptConnectionScreen@@UAE@XZ, retail 0x005DB681..0x005DB6DA (89 bytes,
// EH); pinned until now as the opaque ??1Rva005DB681@@UAE@XZ. The online
// connection grid's destructor (class of AptConnectionScreenConstructor.cpp:
// the Apt window half and the 4-byte listener at +0x58): it restores the
// vftables 0x00C76798 / 0x00C7678C, unregisters the listener from the list
// at +0x2C of the object at 0x00E063F8 (rowed 0x002B7250), puts the listener
// base's own vftable back and runs the Apt window half's destructor.
#include "ascii_string.h"

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	FunctorWrapperHead *m_ptr;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;
class AptOverButtonHandler;

class AptCommandMap;
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
private:
	char m_pad[12];
};

class __declspec(novtable) Rva005248D0
{
public:
	Rva005248D0();
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
private:
	char m_pad[0x58 - 0x10];
};


// Native vftable 0x008711BC: slots 0 and 1 are the shared empty three-argument
// body 0x000D1407 (ret 0Ch), slot 2 the deleting destructor 0x0059EB41.
class Rva0059EB41
{
public:
	virtual void slot00(void *, void *, void *) {}
	virtual void slot01(void *, void *, void *) {}
	virtual ~Rva0059EB41() {}
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva002BA8F1Listener
{
public:
	virtual ~Rva002BA8F1Listener();
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

class Rva005A6D47
{
public:
	virtual ~Rva005A6D47();
	unsigned char m_pad04[0x28 - 4];
	unsigned char m_28; // +0x28
	unsigned char m_pad29[0x2C - 0x29];
	Rva005A0B4CList m_listeners; // +0x2C
};

struct NAT;
extern NAT *TheNAT;

class PortNegotiationSchema;
struct Elem005DB98E;

class AptConnectionScreen : public Rva005248D0, public Rva0059EB41
{
public:
	AptConnectionScreen(void *level);
	virtual ~AptConnectionScreen();
	void RedrawGrid(const char *unused);
	void OnRetryConnections(const char *unused);
	void rva005DB630();

	// Rowed 0x005DB3B3 refreshes one player's name and number.
	void UpdateSlotName(int player);
	void UpdateGrid(PortNegotiationSchema *schema, int row, int column);
	static int GetPingImageEnum(Elem005DB98E *ping);

private:
	void *m_level; // +0x5C
};

AptConnectionScreen::~AptConnectionScreen()
{
	if (TheNAT)
		((Rva002B7250 *)&((Rva005A6D47 *)TheNAT)->m_listeners)->rva002B7250((CreateAHeroData *)static_cast<Rva0059EB41 *>(this));
}
