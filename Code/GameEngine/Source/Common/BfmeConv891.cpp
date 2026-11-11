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
// LINK: the check 0x0035B2C3 is rowed as bool Rva0035B2C3::rva0035B2C3(void*, int, Coord3D const*, int) (Rva0035B2C3Audio.cpp);
// the old char-returning call shape stays through a member-pointer cast.
struct Coord3D;
#include "../../Include/GameLogic/Rva0035B2C3.h"
typedef char (Rva0035B2C3::*Rva0035B2C3CharShape)(void *, void *, int, void *);

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
#include "../../Include/GameLogic/PartitionFilter.h"

// Partition filter vftable 0x00C1FE34 slot 1, built inline by script action
// 0x003BDE5D (Zero Hour's PartitionFilterValidCommandButtonTarget there).
class Rva002614BCFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *a);
	void *m_bfme8;
	Rva0035B2C3 *m_bfmeObj;
	char m_bfme10;
	unsigned char m_bfmePad[3];
	void *m_bfme14;
};

bool Rva002614BCFilter::allow(Object *object)
{
	return (m_bfmeObj->*reinterpret_cast<Rva0035B2C3CharShape>(&Rva0035B2C3::rva0035B2C3))(m_bfme8, object, 0, m_bfme14) == m_bfme10;
}