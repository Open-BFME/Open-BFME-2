// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c- /Ireference/shims/moduledata
// Same complete native0x84-byte owner view asRva003ABD81Ctor.cpp.
// Its own5B teardown folds to3ACB6F, jumping toRva0055F9B4 base3ABC0B.
// Local novtable codegen suppresses vptr writes absent in the native empty
// destructor; it changes no subobject size or method/field contract.
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
#include "../../../../Include/Common/BfmeXfer.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
class Rva003AC9AFModule;
#include "../../../../Include/Common/RvaSmartPtr12.h"

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

class DefaultModuleHeadBase
{
public:
	DefaultModuleHeadBase(const RvaSmartPtr12 &smart, int i);
	virtual ~DefaultModuleHeadBase();
 virtual void rva000B3FD0() = 0;
 virtual void *clone() const = 0;
 virtual void DoXfer(Xfer &) = 0;

	RvaSmartPtr12 m_smart;
	int m_int10;
};

class Rva003AEEB3 : public DefaultModuleHeadBase, public DefaultModuleSecondBase,
	public DefaultModuleThirdBase
{
public:
	Rva003AEEB3(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva003AEEB3();
};

class Rva0055F98A : public Rva003AEEB3
{
public:
	Rva0055F98A(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055F98A();
};

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

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
namespace FXParticleSystem { class DefaultUpdateModuleInfo { public: virtual void xfer(Xfer *); }; }

class Rva0055F9B4 : public Rva0055F98A, public Rva003ABD81SnapshotView
{
public:
	Rva0055F9B4(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F9B4();
};

class __declspec(novtable) Rva003ABD81 : public Rva0055F9B4
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

Rva003ABD81::~Rva003ABD81() {}

typedef char Rva003ABD81SizeCheck[sizeof(Rva003ABD81)==0x84?1:-1];
