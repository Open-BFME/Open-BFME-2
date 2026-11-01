// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
// ??0ChangeStanceGroupOrder@@QAE@PAVRva0036E346@@H@Z @0x00546AD0 31B evidence: stores vtable 0x0086A36C; base holder ctor rowed 0x00548A25; int at +0x18 from second arg; caller 0x00355A86 news int-sized; sibling default at 0x00546AEF in ChangeStanceGroupOrderCtor.cpp.
// Holder overload of ChangeStanceGroupOrder (naming via vtable).
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0036E346;
class Xfer;
enum ObjectID;

// The direct base GroupOrder (ctor 0x005488C5, called only by the six group
// orders) is 0x18 bytes: vptr 0xC6A520, vector-built member at +4 via
// 0x211E58, zeros at +0x10/+0x14. Do NOT declare an explicit vptr member on
// the base: the hidden vptr sits at +0 and a declared one shifts every slot.
// Its table is Snapshot's: loadPostProcess in slot 1, the class-name getter
// in slot 2 and xfer (0x00548AC2) in slot 3 (GroupOrderDerivedDtors.cpp).
class GroupOrder : public Snapshot
{
public:
	GroupOrder();
	GroupOrder(Rva0036E346 *holder);
	GroupOrder(const GroupOrder &other);
	virtual ~GroupOrder();

	virtual void xfer(Xfer *xfer);

protected:
	unsigned char m_pad04[0x14];
};

// Table 0x0086A36C: slot 3 xfer 0x00546B91, slot 4 rva00546BED 0x00546BED.
class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder();
	ChangeStanceGroupOrder(Rva0036E346 *holder, int stance);
	ChangeStanceGroupOrder(const ChangeStanceGroupOrder &other);
	virtual ~ChangeStanceGroupOrder();

	virtual void xfer(Xfer *xfer);
	virtual void rva00546BED(ObjectID id);

private:
	int m_stance;		// +0x18
};

// The retail table at RVA 0x0086A36C: 14 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GChangeStanceGroupOrder@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?getClassName@ChangeStanceGroupOrder@@UAEPBDXZ")();
void __identifier("?xfer@ChangeStanceGroupOrder@@UAEXPAVXfer@@@Z")();
void __identifier("?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?get_allocator@?$_List_base@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@QBE?AV?$allocator@PAVSuperweaponInfo@@@2@XZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?Get_File_Handle@FileClass@@UAEPAXXZ")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?getClassKey@ChangeStanceGroupOrder@@UAE?AW4NameKeyType@@XZ")();
void __identifier("?rva00546B34@ChangeStanceGroupOrder@@UAEPAV1@XZ")();
}
extern const void *const g_0086A36C[14] = {
	(const void *)&__identifier("??_GChangeStanceGroupOrder@@UAEPAXI@Z"), // slot 0 0x00546B75
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?getClassName@ChangeStanceGroupOrder@@UAEPBDXZ"), // slot 2 0x00546BC7
	(const void *)&__identifier("?xfer@ChangeStanceGroupOrder@@UAEXPAVXfer@@@Z"), // slot 3 0x00546B91
	(const void *)&__identifier("?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z"), // slot 4 0x00546BED
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 5 0x005CB9FA
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 6 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 7 0x0047A69C
	(const void *)&__identifier("?get_allocator@?$_List_base@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@QBE?AV?$allocator@PAVSuperweaponInfo@@@2@XZ"), // slot 8 0x0021983A
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 9 0x005CB9FF
	(const void *)&__identifier("?Get_File_Handle@FileClass@@UAEPAXXZ"), // slot 10 0x0036CC7A
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 11 0x0050B5F1
	(const void *)&__identifier("?getClassKey@ChangeStanceGroupOrder@@UAE?AW4NameKeyType@@XZ"), // slot 12 0x00546B6B
	(const void *)&__identifier("?rva00546B34@ChangeStanceGroupOrder@@UAEPAV1@XZ"), // slot 13 0x00546B34
};

ChangeStanceGroupOrder::ChangeStanceGroupOrder(Rva0036E346 *holder, int stance)
	: GroupOrder(holder)
{
	m_stance = stance;
}
