// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// ??0Rva003ABA83@@QAE@PAX0@Z @0x003ABA83 42B
// Unlock lane: ctor calling rowed T1Base 0x0055C903 with same (a,b) then
// vtable g_00C1C334 plus address of 0x00C1C780 at +0x14 and g_ data at
// +0x18 as immediates. Evidence: three mov-dword immediates; base ctor rowed;
// ??_7Rva003F498ACallback@@6B@ extern C; neighbours /O1 /EHsc; ret 8 frameless.
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
// The retail table at RVA 0x0081C334: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
extern const void *const g_00C1C334[11] = {
	(const void *)&__identifier("??_GRva003AD273@@UAEPAXI@Z"), // slot 0 0x003AD257
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z"), // slot 3 0x00560AE1
	(const void *)&__identifier("?doParticles@?$DefaultModule@$05@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"), // slot 4 0x0055C478
	(const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"), // slot 5 0x00560ABA
	(const void *)&__identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ"), // slot 6 0x004BD9CB
	(const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"), // slot 7 0x0055C44F
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 8 0x000910FB
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 9 0x000910FB
	(const void *)&__identifier("?Rva004647D1Get@@YAMXZ"), // slot 10 0x004647D1
};
extern "C" const void *const __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE43F@@6B@")[];
class T1Base_005F3750
{
public:
	T1Base_005F3750(void *a, void *b);
	virtual ~T1Base_005F3750();
private:
	char m_pad[0x14 - 4];
};
class Rva003ABA83 : public T1Base_005F3750
{
public:
	Rva003ABA83(void *a, void *b);
private:
	void *m_14;
	void *m_18;
};
Rva003ABA83::Rva003ABA83(void *a, void *b) : T1Base_005F3750(a, b)
{
	*(void **)this = (void *)g_00C1C334;
	m_14 = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	m_18 = (void *)__identifier("??_7Rva003AE43F@@6B@");
}

struct EmitVtableTag;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
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
class Rva003AE43F {
public: Rva003AE43F(const Rva003AE43F &);
private: char m_storage[0x1C];
};

class __declspec(novtable) Rva003AD273Base0
{
public:
	virtual ~Rva003AD273Base0();
    virtual void rva000B3FD0() = 0;
    virtual Rva003AE43F *rva003AE408() const = 0;
    virtual void DoXfer(Xfer &) = 0;
private:
	char m_unmodelled_04[0x18 - 0x04];
};

// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) in its vtable is target evidence for it.
class __declspec(novtable) Rva003AD273Base18 : public Snapshot
{
public:
    virtual ~Rva003AD273Base18();
};
class Rva003AD273 : public Rva003AD273Base0, public Rva003AD273Base18
{
public:
	Rva003AD273(EmitVtableTag *);
public:
	virtual ~Rva003AD273();
    virtual Rva003AE43F *rva003AE408() const;
    virtual void rva000B3FD0() {}
    virtual void LoadPostProcess() {}
    virtual const char *GetSnapshotName() { return "DefaultDraw<CAT_DRAW>"; }
    virtual void DoXfer(Xfer &);
};

typedef char Rva003AD273PrimarySize[sizeof(Rva003AD273Base0) == 0x18 ? 1 : -1];
typedef char Rva003AD273SnapshotSize[sizeof(Rva003AD273Base18) == 4 ? 1 : -1];
typedef char Rva003AD273CompleteSize[sizeof(Rva003AD273) == 0x1C ? 1 : -1];

// ?<Rva003AD273::Rva003AD273> absent-from-retail
Rva003AD273::Rva003AD273(EmitVtableTag *)
{
}

// Native C1C324 secondary table belongs to this established +0x18 view:
// slot 0 is rowed deleting-dtor adjustor 3ABABB, slot 3 is 3ABAB3.
// C1CC28 primary slot 3 is the shared 560AE1 transfer body. Its two
// Version1 calls are exactly the body already owned by ObjectModule::xfer.
// Primary C1CC28 starts [3AD257, B3FD0, 3AE408, 560AE1]; secondary
// C1C324 is [3ABABB, B3FD0, 3ABAAD, 3ABAB3]. The two empty hooks have
// distinct names so the secondary hook needs no unnecessary this-adjustor.
// Clone 3AE408 allocates 0x1C and calls the existing copy owner 3AE43F;
// its complete body and EH graph match that owner, not only a call shape.
// Canonical Snapshot supplies the secondary slot contract and FX Xfer& ABI.
// Both emitted table prefixes are exact, while the rest of the primary
// interface and the original containing class name remain unrecovered.
Rva003AE43F *Rva003AD273::rva003AE408() const
{
    return new Rva003AE43F(*reinterpret_cast<const Rva003AE43F *>(this));
}

void Rva003AD273::DoXfer(Xfer &stream)
{
    stream.Version1();
    stream.Version1();
}

