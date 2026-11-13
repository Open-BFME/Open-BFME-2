// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /Ireference/shims/moduledata
// Native3ACB6F is the complete5B destructor reached by this owner's
// deleting body3AD3F7. Empty novtable teardown tails to the already-rowed
// Rva0055F197 base destructor3ABC0B. Keep the complete same-size interface
// and field view as Rva003ABD20Ctor.cpp; novtable is the local destructor
// codegen fact (no native vptr stores), not a different owner or layout.
// ??0Rva003ABD20@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x003ABD20, 49 bytes.
// Empty derived of the rowed ??0Rva0055F197@@QAE@ABVRvaSmartPtr12@@H@Z at
// 0x0055F197: forwards (smart, x) then re-stamps the four vftables
// (+0 0x00C1C578, +0x14 0x00C1C574, +0x18 s_slot3E4first, +0x1C 0x00C1CE54).
// Same empty-body shape as the DefaultModuleDerivedSmartCtors trio via rowed
// base 0x0055BEE9; all vtable dwords are DIR32 sites. Caller at 0x003ACFDA.

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
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
class Rva003ACF68Object;
#include "../../../../Include/Common/RvaSmartPtr12.h"

class DefaultModuleSecondBase
{
public:
	virtual Rva003ACF68Object *rva003ACF68(unsigned int);
};

class DefaultModuleThirdBase
{
public:
	virtual const void *classView() const = 0;
};

#include "../../../../Include/GameClient/DefaultModuleHeadBase.h"

#include "../../../../Include/GameClient/Rva003AEEB3.h"

#include "../../../../Include/Common/Rva0055BF21.h"

#include "../../../../Include/GameClient/DefaultPhysicsModuleInfo.h"
namespace FXParticleSystem
{
}

class Rva0055F197 : public Rva0055BF21, public FXParticleSystem::DefaultPhysicsModuleInfo
{
public:
	Rva0055F197(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F197();
private:
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	unsigned char m_3c;
	unsigned char m_3d;
};

class __declspec(novtable) Rva003ABD20 : public Rva0055F197
{
public:
	__declspec(noinline) Rva003ABD20(const RvaSmartPtr12 &smart, int x);
	// Empty: retail's vtable 0x0081C578 slot 0 0x003AD3F7 calls 0x003ACB6F, one
	// jump to the base dtor 0x003ABC0B (Rva0055F197's, see Rva003ABC0BDtor.cpp).
	virtual ~Rva003ABD20();
 virtual void rva000B3FD0() {}
 virtual void LoadPostProcess() {}
 virtual const char *GetSnapshotName() { return "DefaultModule<CAT_PHYSICS>"; }
 virtual void DoXfer(Xfer &);
};

Rva003ABD20::~Rva003ABD20() {}
