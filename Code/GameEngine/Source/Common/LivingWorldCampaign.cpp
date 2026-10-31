// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
//
// ??0LivingWorldCampaign@@QAE@ABVAsciiString@@@Z, retail 0x0052cf0f, 156 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
//
// Evidence: vtable 0x00868780 at +0 (same as dtor 0x0052CFB1 own unit), StringBase copy 0x000365F0 from param, vector_base 0x00211E58 twice, immutable floats2.0/1.0 atC686F4/C686F8, ints 0xb4 0x1d4c 0x9c4, caller 0x0052D0CD in 0x0052D04E.
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
LivingWorldCampaign::LivingWorldCampaign(const AsciiString &asciiString)
	: Snapshot()
	, m_04(asciiString)
	, m_08(0)
	, m_records()
	, m_currentIndex(0)
	, m_1C(0)
	, m_20(0)
	, players()
	, localName()
	, m_34()
	, m_38(0xb4)
	, m_3c(0x1d4c)
	, m_40(0x9c4)
	, m_44(2.0f)
	, m_48(1.0f)
	, fromCampaign(false)
	, m_4d(false)
	, m_4e(false)
{
}
