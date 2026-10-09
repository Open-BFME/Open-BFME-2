// ??0Rva004E3184@@QAE@H@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DBFME_ASCII_DTOR_DECL /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Complete175B main and EH EXACT. All four providers with this shared layout
// passed18 dependent bytes and link_check --new-variants returned0.
// add_match --icf-owner accepted genuine6B GetSnapshotName and1B LoadPostProcess
// twins at their retail slot addresses; commit check_csv rejected both because
// gen-alias notes classified the named rows as placeholders. No gate was edited.
// Bank preserves the real four-slot table and compatible88B layout for repair.
#include <vector>
#include "ascii_string.h"
// WB128AFA0 names this 88B description SpawnArmy. Preserve the existing
// Rva004E3184 linkage owner while reconciling its providers. Native ctor
// 4E30D5 and copy/dtor/xfer independently establish these member offsets.
// Retail table861F28 contains exactly four pointers: deleting dtor4E3797;
// empty LoadPostProcessB3FD0; name getter4E30C6 ("SpawnArmy"); DoXfer4E3991.
// Text immediately follows the fourth pointer; the inventory's64B extent
// includes that text and does not imply further virtual slots.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "Coord2D.h"
namespace _STL { template<> vector<AsciiString>::~vector(); }
class Rva004E3184 : public Snapshot {
public:
 Rva004E3184(int);
 Rva004E3184(const Rva004E3184&);
 virtual ~Rva004E3184();
 virtual void LoadPostProcess() {}
 virtual const char *GetSnapshotName() const { return "SpawnArmy"; }
 virtual void DoXfer(Xfer&);
private:
 AsciiString m_04,m_08,m_0c,m_10,m_14,m_18,m_1c;
 struct Position : Coord2D { Position() { x=0.0f; y=0.0f; } } m_20;
 AsciiString m_28,m_2c,m_30,m_34;
 _STL::vector<AsciiString> m_vec38;
 float m_44;
 unsigned m_48,m_4c;
 AsciiString m_50;
 bool m_54,m_55;
};

namespace _STL { template<> vector<AsciiString>::~vector(); }
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct SpawnManagerDefaults { char pad[0xF0]; float interval; };
Rva004E3184::Rva004E3184(int context)
 :m_2c(AsciiString::TheEmptyString),m_48(1),m_4c(context),m_54(false),m_55(true)
{
 if(TheLivingWorldManager)m_44=reinterpret_cast<SpawnManagerDefaults*>(TheLivingWorldManager)->interval;
 else m_44=5.0f;
}
