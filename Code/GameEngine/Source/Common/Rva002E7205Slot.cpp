// cl: /O1 /DNDEBUG /MD
//
// ?SetBridgeStateRepaired@Pathfinder@@QAEXH_N@Z @0x002E7205 62B: shl/lea pair
// (thiscall, void(int,bool)). Indexes a 64-byte slot at this+0x60 by the int
// arg (shl 6, lea); returns when rowed 0x0036666B on the slot is false, or
// when pinned 0x0036736E on the slot with (flag==0) is false; otherwise
// invokes rowed 0x00531481 on the +0x460 sub-object. Honest
// address-derived names; slot/owner identities unproven beyond the call
// shapes (both bool callees share the slot this).

class Rva0036666B
{
public:
	bool rva0036666B();
	bool rva0036736E(bool flag);
private:
	char m_pad00[0x34];
	int m_a34;
	int m_b38;
};

struct Rva002E7205Slot
{
	Rva0036666B view;
	char m_pad3C[0x40 - 0x3C];
};

class PathfindZoneManager
{
public:
	void rva00531481();
};

class Pathfinder
{
public:
	void SetBridgeStateRepaired(int idx, bool flag);
private:
	char m_pad00[0x60];
	Rva002E7205Slot m_slots[1]; // +0x60, 64-byte stride
	char m_padA0[0x460 - 0xA0];
	PathfindZoneManager m_s460; // +0x460
};

// ?SetBridgeStateRepaired@Pathfinder@@QAEXH_N@Z
void Pathfinder::SetBridgeStateRepaired(int idx, bool flag)
{
	Rva002E7205Slot *slot = &m_slots[idx];
	if (!slot->view.rva0036666B())
		return;
	if (!slot->view.rva0036736E(flag == 0))
		return;
	m_s460.rva00531481();
}
