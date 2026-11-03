// cl: /EHsc /Ireference/shims/moduledata

// ?clone@Rva003AF208@@QBEPAV1@XZ @0x003AF1D1 55B: vslot 2 (offset 0x8) of vtable 0x0081CF9C
// (class of ??0Rva003AF208@@QAE@ABV0@@Z in ParticleModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AEAA3 (push 0xAC) and 0x003AEF34
// (push 0xB4) and landed 0x003AF127 (push 0x40); here push 0x28 plus rowed copy
// Rva003AF208. Donor BFME1 DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp
// (clone via new plus copy).

class Rva003AF208
{
public:
	Rva003AF208(const Rva003AF208 &other);
	Rva003AF208 *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_pad1C[12]; // +0x1C..0x27: makes sizeof 0x28 for new
};

Rva003AF208 *Rva003AF208::clone() const
{
	return new Rva003AF208(*this);
}


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
#include "../../../../Include/GameClient/GameClientRandomVariable.h"
Xfer &xferRandomVariable(Xfer &, GameClientRandomVariable &);
class DefaultModuleHeadBase {
public:
 virtual ~DefaultModuleHeadBase();
 virtual void rva000B3FD0() = 0;
 virtual Rva003AF208 *clonePartial() const = 0;
 virtual void DoXfer(Xfer &) = 0;
private: unsigned int storage[4];
};
#include "../../../../Include/GameClient/EmissionVelocityInfo.h"
namespace FXParticleSystem {
class Rva003AA228Slice { public: virtual void unusedVirtual() = 0; };
class Rva003AA228 : public DefaultModuleHeadBase, public Rva003AA228Slice { public: virtual ~Rva003AA228(); };
template<int Category> class DefaultParticleModule;
template<> class DefaultParticleModule<4> : public Rva003AA228 { public: virtual ~DefaultParticleModule(); };
class SphericalEmissionVelocityInfo : public EmissionVelocityInfo { private: GameClientRandomVariable var; };
class SphericalEmissionVelocityModule : public DefaultParticleModule<4>, public SphericalEmissionVelocityInfo { public: virtual ~SphericalEmissionVelocityModule(); };
}
class Rva003ACBA3 : public FXParticleSystem::SphericalEmissionVelocityModule {
public: Rva003ACBA3(void *,void *); virtual ~Rva003ACBA3();
};
class Rva003ADA95Template;
class Rva003AD19BModule : public Rva003ACBA3 {
public:
 Rva003AD19BModule(void *owner,Rva003ADA95Template *module_template);
 virtual ~Rva003AD19BModule();
 virtual void rva000B3FD0() {}
 virtual Rva003AF208 *clonePartial() const;
 virtual void DoXfer(Xfer &);
 virtual void LoadPostProcess() {}
 virtual const char *GetSnapshotName() { return "EmissionVelocityInfo"; }
};
Rva003AD19BModule::Rva003AD19BModule(void *owner,Rva003ADA95Template *module_template) : Rva003ACBA3(owner,module_template) {}
Rva003AF208 *Rva003AD19BModule::clonePartial() const { return new Rva003AF208(*reinterpret_cast<const Rva003AF208 *>(this)); }
void Rva003AD19BModule::DoXfer(Xfer &stream) {
 stream.Version1();
 xferRandomVariable(stream,*reinterpret_cast<GameClientRandomVariable *>(reinterpret_cast<char *>(this)+0x1C));
}
typedef char ModuleSizeCheck[sizeof(Rva003AD19BModule)==0x28?1:-1];
