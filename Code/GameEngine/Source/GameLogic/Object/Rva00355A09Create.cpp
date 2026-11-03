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
#include "../../../Include/GameLogic/AiOrdersManager.h"

class Rva003559B5Host
{
public:
	void rva00355A09(int mode, Rva0036E346 *holder, int val);
	void rva00355A5D(int mode, Rva0036E346 *holder, int val);
	void rva00355AB1(int mode, Rva0036E346 *holder);
};

void Rva003559B5Host::rva00355A09(int mode, Rva0036E346 *holder, int val)
{
	GarrisonObjectGroupOrder *garrisonObjectGroupOrder = new GarrisonObjectGroupOrder(holder, val);
	if (garrisonObjectGroupOrder)
		((AiOrdersManager *)this)->registerOrder(mode, (GroupOrder *)garrisonObjectGroupOrder);
}

void Rva003559B5Host::rva00355A5D(int mode, Rva0036E346 *holder, int val)
{
	ChangeStanceGroupOrder *changeStanceGroupOrder = new ChangeStanceGroupOrder(holder, val);
	if (changeStanceGroupOrder)
		((AiOrdersManager *)this)->registerOrder(mode, (GroupOrder *)changeStanceGroupOrder);
}

void Rva003559B5Host::rva00355AB1(int mode, Rva0036E346 *holder)
{
	SynchronizeGroupOrder *synchronizeGroupOrder = new SynchronizeGroupOrder(holder);
	if (synchronizeGroupOrder)
		((AiOrdersManager *)this)->registerOrder(mode, (GroupOrder *)synchronizeGroupOrder);
}
