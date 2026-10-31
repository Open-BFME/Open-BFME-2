// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??1LivingWorldCampaign@@UAE@XZ @0x0052CFB1 157B: dtor with AsciiStrings vectors and twin deletes via get plus Snapshot base BBB554.
// Evidence: vtable 0x00868780 at +0, releaseBuffer +0x04 +0x30 +0x34, vectors +0x0C +0x24 rowed, deletes +0x1C +0x20 via virtual get, base 0xBBB554, caller 0x0052D305, neighbours ConstIntGetters4 RvaVectorDtorFamily.
#include "ascii_string.h"
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Xfer;
#include <new>
// +0x1C and +0x20 hold objects released through virtual slot 0.
struct RvaItem0052CFB1 { virtual void *get(int x); };
struct Res004FCA0C;
class Rva0020E89C;
struct Sub0052BAC1 : public RvaItem0052CFB1
{
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *found);
};
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
LivingWorldCampaign::~LivingWorldCampaign()
{
	delete (m_1C ? m_1C->get(0) : 0);
	delete (m_20 ? m_20->get(0) : 0);
}
