// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoFBC@BfmeThingFBC@@QAE_NPAX@Z
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

struct BfmeThingFBC
{
	bool bfmeGoFBC(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfme8;
	BfmeObjFBC *m_bfmeObj;
	char m_bfme10;
	unsigned char m_bfmePad[3];
	void *m_bfme14;
};

bool BfmeThingFBC::bfmeGoFBC(void *a)
{
	return m_bfmeObj->bfmeCallFBC(m_bfme8, a, 0, m_bfme14) == m_bfme10;
}