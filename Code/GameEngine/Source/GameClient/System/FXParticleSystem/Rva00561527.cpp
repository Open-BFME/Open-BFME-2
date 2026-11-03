// cl: /DNDEBUG /MD /EHsc /Ob2
// ?rva00561527@Rva00561527@@UAEXPAVXfer@@@Z @0x00561527 28B evidence: Version1 0x000053EE then Lightning xfer 0x005614D9 on base at +0x18; caller jmp 0x003ABBC6.
// Honest-address wrapper (naming rule).
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

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

namespace FXParticleSystem
{

class LightningDrawModuleInfoBase
{
public:
	virtual ~LightningDrawModuleInfoBase();
};

class LightningDrawModuleInfo : public LightningDrawModuleInfoBase
{
public:
	LightningDrawModuleInfo();
	virtual ~LightningDrawModuleInfo();
protected:
	virtual void xfer(Xfer *xfer);

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	float m_28;
	bool m_2c;
};

}

class Pad018
{
public:
	virtual ~Pad018();
private:
	char m_pad[0x18 - 4];
};

class Rva00561527 : public Pad018, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	virtual void rva00561527(Xfer *xfer);
};

void Rva00561527::rva00561527(Xfer *xfer)
{
	xfer->Version1();
	FXParticleSystem::LightningDrawModuleInfo::xfer(xfer);
}

// The native constructor installs these primary and +0x18 tables.
// Shared slots retain their existing row owners.
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("?rva000B3FD0@Rva003AD273@@UAEXXZ")();
void __identifier("?clone@Rva005EBCC0Object@@QBEPAV1@XZ")();
void __identifier("?rva00561527@Rva00561527@@UAEXPAVXfer@@@Z")();
void __identifier("?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
void __identifier("??_ERva003AD273@@WBI@AEPAXI@Z")();
void __identifier("?Rva003ABBBDGet@@YAHXZ")();
void __identifier("?rva00561527@Rva00561527@@WBI@AEXPAVXfer@@@Z")();

extern const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot0@@@")[11] = {
    (const void *)&__identifier("??_GRva003AD273@@UAEPAXI@Z"),
    (const void *)&__identifier("?rva000B3FD0@Rva003AD273@@UAEXXZ"),
    (const void *)&__identifier("?clone@Rva005EBCC0Object@@QBEPAV1@XZ"),
    (const void *)&__identifier("?rva00561527@Rva00561527@@UAEXPAVXfer@@@Z"),
    (const void *)&__identifier("?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"),
    (const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"),
    (const void *)&__identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ"),
    (const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"),
    (const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"),
    (const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"),
    (const void *)&__identifier("?Rva004647D1Get@@YAMXZ")
};

extern const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@")[4] = {
    (const void *)&__identifier("??_ERva003AD273@@WBI@AEPAXI@Z"),
    (const void *)&__identifier("?rva000B3FD0@Rva003AD273@@UAEXXZ"),
    (const void *)&__identifier("?Rva003ABBBDGet@@YAHXZ"),
    (const void *)&__identifier("?rva00561527@Rva00561527@@WBI@AEXPAVXfer@@@Z")
};
}
