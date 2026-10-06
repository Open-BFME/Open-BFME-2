// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?allow@Rva002614BCFilter@@UAE_NPAVObject@@@Z (BFME1 donor ?bfmeGoFBC@BfmeThingFBC)
// retail 0x002614BC, 35 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv891.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// The donor's call target, retail 0x0035B2C3, already carries an
// address-derived pin from the AoE target picker 0x005EE816,
// ?rva0035B2C3@Rva0035B2C3@@QAE_NPAXHPBVCoord3D@@H@Z, describing the same
// (source, count, position, template) check. This body passes exactly that
// argument shape -- (this, 0, a, m_bfme14), the receiver at +0x08 and the
// position in ECX -- so the callee carries a second name for the one address:
// the donor's own. The body is otherwise unchanged from the donor, and the
// receiver is the member at +0x08 as retail loads it.
class BfmeObjFBC
{
public:
	char bfmeCallFBC(void *x, void *a, int z, void *y);
};

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// Partition filter vftable 0x00C1FE34 slot 1, built inline by script action
// 0x003BDE5D (Zero Hour's PartitionFilterValidCommandButtonTarget there).
class Rva002614BCFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *a);
	void *m_bfme8;
	BfmeObjFBC *m_bfmeObj;
	char m_bfme10;
	unsigned char m_bfmePad[3];
	void *m_bfme14;
};

bool Rva002614BCFilter::allow(Object *a)
{
	return m_bfmeObj->bfmeCallFBC(m_bfme8, a, 0, m_bfme14) == m_bfme10;
}