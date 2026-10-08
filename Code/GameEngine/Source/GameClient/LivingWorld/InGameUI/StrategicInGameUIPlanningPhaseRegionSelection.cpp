// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlanningPhaseRegionSelection::Impl (WorldBuilder
// StrategicInGameUIPlanningPhaseRegionSelection.cpp). Target facts for
// OnRegionChangingOwnership 0x005CE9CA (virtual; pointer at 0x00875248;
// ret 0xC): unless the new owner (third argument) is already +0x0C, the
// object read through +0x10 (rowed getter 0x0042D6FD) gets its vslot 4.
// Argument and member types are viewed by offset.
class Rva0042D6FDPtrChaseField
{
public:
	int get() const;
};

struct Rva005CE9CAListener
{
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
};

namespace StrategicInGameUI
{
class PlanningPhaseRegionSelection
{
public:
	class Impl;
};
}

class StrategicInGameUI::PlanningPhaseRegionSelection::Impl
{
public:
	virtual void OnRegionChangingOwnership(void *region, int oldOwner, int newOwner);

private:
	char m_pad04[0x0C - 0x04];
	int m_owner; // +0x0C
	Rva0042D6FDPtrChaseField *m_10; // +0x10
};

void StrategicInGameUI::PlanningPhaseRegionSelection::Impl::OnRegionChangingOwnership(void *region, int oldOwner, int newOwner)
{
	if (newOwner == m_owner)
		return;
	Rva005CE9CAListener *listener = (Rva005CE9CAListener *)m_10->get();
	if (listener)
		listener->vslot4();
}
