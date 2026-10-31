// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ?xfer@LivingWorldCampaign@@UAEXPAVXfer@@@Z @0x0052BAFE 42B: slot 3 xfer with IsLightCRC early-out plus Version1 plus int at +0x08 via Xfer slot 0x7c.
// Evidence: vtable 0x00868780 slot 3 of class of ??1LivingWorldCampaign rowed at 0x0052CFB1, IsLightCRC slot 0x10 plus Version1 row 0x000053EE plus int slot 0x7c per Rva00589079 precedent, layout +0x08 int from Rva0052CFB1Dtor. Xfer declaration copied verbatim from PoisonedBehaviorXfer.cpp.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"
#include "ascii_string.h"
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

// +0x1C and +0x20 hold objects released through virtual slot 0.
struct RvaItem0052CFB1 { virtual void *get(int x); };
struct Sub0052BAC1;
struct Rva0052CA2D {
 __forceinline Rva0052CA2D():storage(_STL::allocator<BfmeE16>()){}
 ~Rva0052CA2D();
 _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > storage;
};
struct Rva0052CA6C {
 __forceinline Rva0052CA6C():storage(_STL::allocator<BfmeE16>()){}
 ~Rva0052CA6C();
 _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > storage;
};
class Rva002E0A0A;
class LivingWorldCampaign : public Snapshot {
public:
 LivingWorldCampaign(const AsciiString &name);
 virtual ~LivingWorldCampaign();
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);
 void rva0052C0C8();
 static void ParseLivingWorldCampaignBlock(class INI *ini);
 void CreatePlayers(); int AdjustStartingPositionForScenario(int);
 void AddPlayer(const Rva002E0A0A &arg);
 AsciiString m_04; int m_08; Rva0052CA2D m_records; int m_currentIndex;
 Sub0052BAC1 *m_1C; RvaItem0052CFB1 *m_20; Rva0052CA6C players; AsciiString localName;
 AsciiString m_34; int m_38; int m_3c; int m_40; float m_44; float m_48;
 bool fromCampaign; bool m_4d; bool m_4e;
};

void LivingWorldCampaign::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_08;
}

// ?LivingWorldCampaign::loadPostProcess present-unmatched
void LivingWorldCampaign::loadPostProcess()
{
}
