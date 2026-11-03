// cl: /DNDEBUG /MD /EHs-c- /Ireference/shims/moduledata
// ??0Rva003ABD81@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x003ABD81, 49 bytes.
// Empty derived of the rowed ??0Rva0055F9B4@@QAE@ABVRvaSmartPtr12@@H@Z at
// 0x0055F9B4: forwards (smart, x) then re-stamps the four vftables
// (+0 0x00C1C5BC, +0x14 0x00C1C5B8, +0x18 s_slot3E4first, +0x1C 0x00C1CE88).
// Same empty-body shape as sibling 0x003ABD20 via rowed base 0x0055F197;
// all vtable dwords are DIR32 sites. Caller at 0x003AD010.

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
#include "../../Include/Common/BfmeXfer.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
class Rva003AC9AFModule;
#include "../../Include/Common/RvaSmartPtr12.h"

class DefaultModuleSecondBase
{
public:
	virtual Rva003AC9AFModule *rva003AC9AF(unsigned int);
};

class DefaultModuleThirdBase
{
public:
	virtual const void *classView() const = 0;
};

#include "../../Include/GameClient/Rva003AEEB3.h"


class Rva0055F98A : public Rva003AEEB3
{
public:
	Rva0055F98A(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055F98A();
};

#include "../../Include/GameClient/GameClientRandomVariable.h"

// Canonical four-slot Snapshot plus the native104B info payload. The legacy
// DefaultUpdateModuleInfo xfer pointer surface is a separate qualified-call
// view below; inheriting it here would add a nonretail fifth virtual slot.
class __declspec(novtable) Rva003ABD81SnapshotView : public Snapshot
{
public:
	Rva003ABD81SnapshotView();
	virtual ~Rva003ABD81SnapshotView();
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	int m_extra;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
};
namespace FXParticleSystem { class DefaultUpdateModuleInfo { public: virtual void DoXfer(Xfer &); }; }

class Rva0055F9B4 : public Rva0055F98A, public Rva003ABD81SnapshotView
{
public:
	Rva0055F9B4(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F9B4();
};

// Native constructor3ABD81 writes C1C5BC primary andC1CE88 at+1C.
// Primary prefix=[3AD3F7,B3FD0,purecall,55F710]; Snapshot contains
// [3ABDC0,B3FD0,3ABDB2,3ABDB8]. Existingcopy3AEC5E confirms both.
class Rva003ABD81 : public Rva0055F9B4
{
public:
	__declspec(noinline) Rva003ABD81(const RvaSmartPtr12 &smart, int x);
	// Empty: retail's vtable 0x0081C5BC slot 0 0x003AD3F7 calls 0x003ACB6F, one
	// jump to the base dtor 0x003ABC0B (rowed as ??1Rva0055F9B4).
	virtual ~Rva003ABD81();
 virtual void rva000B3FD0() {}
 virtual void LoadPostProcess() {}
 virtual const char *GetSnapshotName() { return "DefaultModule<CAT_UPDATE>"; }
 virtual void DoXfer(Xfer &);
};

Rva003ABD81::Rva003ABD81(const RvaSmartPtr12 &smart, int x)
	: Rva0055F9B4(smart, x)
{
}

void Rva003ABD81::DoXfer(Xfer &stream) {
 stream.Version1();
 reinterpret_cast<FXParticleSystem::DefaultUpdateModuleInfo *>((char *)this+0x1C)->FXParticleSystem::DefaultUpdateModuleInfo::DoXfer(stream);
}

typedef char Rva003ABD81SizeCheck[sizeof(Rva003ABD81)==0x84?1:-1];
