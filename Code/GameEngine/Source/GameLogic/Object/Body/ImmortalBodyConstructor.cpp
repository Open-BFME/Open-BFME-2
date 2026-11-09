// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

class Thing;
class ModuleData;
class DamageInfo;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

template<typename T>
inline const T& max(const T& a, const T& b)
{
	if (a > b)
		return a;
	return b;
}

// LINK helper for internalChangeHealth below (see note there).
static __forceinline const Real &bfme_max_real(const Real &a, const Real &b)
{
	if (a > b)
		return a;
	return b;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
#include "../../../../Include/GameLogic/Module/BodyModule.h"
// ActiveBody derives from BodyModule (constructor 0x004BF6A1 calls 0x004BD7FD), whose
// getBody and vslot12 fill behavior-interface slot 0 and primary slot 12.
#include "../../../../Include/GameLogic/Module/BodyModuleClass.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody : public BodyModule
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ActiveBody();

	virtual void slot0();

protected:
	virtual void xfer( Xfer *xfer );

public:
	virtual Real getHealth() const;
	virtual void slot3();
	virtual void slot4();
	virtual void internalChangeHealth( Real delta, DamageInfo *damageInfo );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h
class ImmortalBody : public ActiveBody
{
public:
	ImmortalBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ImmortalBody();

	virtual void internalChangeHealth( Real delta, DamageInfo *damageInfo );

protected:
	virtual void xfer( Xfer *xfer );
public:
	// retail slot 4: the rowed ?getModuleNameKey@ImmortalBody@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

ImmortalBody::ImmortalBody( Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData )
{
}

// ??1ImmortalBody@@UAE@XZ present-unmatched
ImmortalBody::~ImmortalBody()
{
}

// Open-BFME Zero Hour ImmortalBody::xfer (ImmortalBody.cpp:84-95) versions the
// transfer then extends ActiveBody::xfer; retail calls Xfer::Version1 and the
// 551-byte ActiveBody base body at 0x004BF1E8.
void ImmortalBody::xfer( Xfer *xfer )
{
	xfer->Version1();
	ActiveBody::xfer( xfer );
}

// BFME 2 passes the DamageInfo along: ImmortalBody's vftable slot at
// 0x00C5B520 holds this body where RespawnBody's slot at 0x00C5B970 holds its
// override that reads DamageInfo fields from the second argument (both are
// followed by 0x004BF186), and it calls through to ActiveBody's version at
// 0x004BF005 (ret 8).
void ImmortalBody::internalChangeHealth( Real delta, DamageInfo *damageInfo )
{
	// LINK: file-static ref-returning max with the identical template body;
	// the TU-local max<float> instantiation is not retail's copy (home:
	// updateMinMax.cpp @0x579D) and the live call emits the loser COMDAT,
	// while this internal-linkage helper inlines the same x87 and emits
	// nothing. No flags touched.
	Real floorVal = -getHealth() + 1.0f;
	delta = bfme_max_real(delta, floorVal);
	ActiveBody::internalChangeHealth( delta, damageInfo );
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot0@ActiveBody@@UAEXXZ=?Rva004C0898Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?getHealth@ActiveBody@@UBEMXZ=?getModuleNameKey@ImmortalBody@@UBE?AW4NameKeyType@@XZ")
#pragma comment(linker, "/alternatename:?slot3@ActiveBody@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot4@ActiveBody@@UAEXXZ=??1Coord2D@@QAE@XZ")
