// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00355A09@Rva003559B5Host@@QAEXHPAVRva0036E346@@H@Z @0x00355A09 84B: creates GarrisonObjectGroupOrder(0x28) via rowed ctor 0x00546C26 then Attach via pin 0x003558A3.
// Evidence: retail push 0x28 call new 0x2FDA0 then push [ebp+0x10] [ebp+0xC] call ctor then push eax [ebp+8] call Attach; ret 0xC.
// ?rva00355A5D@Rva003559B5Host@@QAEXHPAVRva0036E346@@H@Z @0x00355A5D 84B: creates ChangeStanceGroupOrder(0x1C) via rowed ctor 0x00546AD0 then Attach via pin 0x003558A3.
// Evidence: same shape as 0x00355A09 with size 0x1C and ctor 0x00546AD0; ret 0xC.

class Rva0036E346;
struct Rva003559B5Val;

class GarrisonObjectGroupOrder
{
public:
	GarrisonObjectGroupOrder(Rva0036E346 *holder, int val);
private:
	char m_pad[0x28];
};

class ChangeStanceGroupOrder
{
public:
	ChangeStanceGroupOrder(Rva0036E346 *holder, int val);
private:
	char m_pad[0x1C];
};

class SynchronizeGroupOrder
{
public:
	SynchronizeGroupOrder(Rva0036E346 *holder);
private:
	char m_pad[0x28];
};

// The attach callee at 0x003558A3 is the rowed AiOrdersManager::registerOrder
// (AiOrdersManager.cpp); this host is that manager.
class GroupOrder;
class AiOrdersManager
{
public:
	void registerOrder(int mode, GroupOrder *order);
};

class Rva003559B5Host
{
public:
	void rva00355A09(int a, Rva0036E346 *b, int c);
	void rva00355A5D(int a, Rva0036E346 *b, int c);
	void rva00355AB1(int a, Rva0036E346 *b);
};

void Rva003559B5Host::rva00355A09(int a, Rva0036E346 *b, int c)
{
	GarrisonObjectGroupOrder *p = new GarrisonObjectGroupOrder(b, c);
	if (p)
		((AiOrdersManager *)this)->registerOrder(a, (GroupOrder *)p);
}

void Rva003559B5Host::rva00355A5D(int a, Rva0036E346 *b, int c)
{
	ChangeStanceGroupOrder *p = new ChangeStanceGroupOrder(b, c);
	if (p)
		((AiOrdersManager *)this)->registerOrder(a, (GroupOrder *)p);
}

void Rva003559B5Host::rva00355AB1(int a, Rva0036E346 *b)
{
	SynchronizeGroupOrder *p = new SynchronizeGroupOrder(b);
	if (p)
		((AiOrdersManager *)this)->registerOrder(a, (GroupOrder *)p);
}
