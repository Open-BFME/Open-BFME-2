// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0LaserFXNugget@@QAE@XZ 32B @0x1E04DE: no-arg ctor called by
// LaserFXNugget::parse (0x001E1519) for the Laser FXList keyword; class name
// from BFME1. Member names and offsets from the retail FieldParse table
// 0x00BDCFD8 (LaserName@0x148 LaserBackwards@0x14C) and the BFME1 donor.
// Base 0x001DFEAA is the shared FXNugget-family base (Rva001DFEAABase.h).
//
// Target facts: the constructor stores table 0x00BDD7B8 after the base
// constructor returns. That table has five slots: the deleting destructor
// 0x001E1152 (shared with CursorParticleSystemFXNugget, whose destructor
// 0x001E116E releases the four-byte string at +0x148 before the base
// destructor), doFXPos 0x001E04FE and doFXObj 0x001E05F9 (rowed in
// EvaEventFXNugget.cpp), slot 3 = the shared `ret 8` 0x0050B238, and the
// base's 0x001DFF5D. LaserName at +0x148 is therefore a string owner; the
// constructor's `and dword [esi+0x148], 0` is its empty-string construction.

#include "ascii_string.h"
#include "../../Include/GameClient/Rva001DFEAABase.h"

class LaserFXNugget : public Rva001DFEAABase
{
public:
	LaserFXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;
	virtual void slot03(AssetList &, int) const {}
private:
	AsciiString m_laserName; // +0x148
	bool m_laserBackwards; // +0x14C
};

// ??0LaserFXNugget@@QAE@XZ
LaserFXNugget::LaserFXNugget()
{
	m_laserBackwards = false;
}
