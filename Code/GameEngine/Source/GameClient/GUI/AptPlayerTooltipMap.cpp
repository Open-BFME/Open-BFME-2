// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfmealloc
// stlport

// Native224D80..224DFF127B returns the local lazy owning holder's pointer.
// WB B8FC20 has the same static guard, allocation, constructor and slot08 call;
// named AptPlayer constructor B8F880 calls it at AptPlayer.cpp251. The callee
// constructor names AptButtonTooltipMap. Its original accessor spelling is unknown.
// Native allocation proves32B; the constructor declaration is an opaque ABI view.
// A real local static generates retail guard, atexit cleanup and EH state; no
// hand-coded guard global or callback pin is needed. All providers are owned.
class Object { public: virtual void *destroy(int); virtual void slot04(); virtual void slot08(); };
class Rva00575674 {public: void rva00575674(Object*); Object *ptr;};
class Rva000AD6F4 {public: void clear();};
class Rva00224CDC {public: Rva00224CDC(); char data[0x20];};
class AptTooltipHolder {
public:
 Object *ptr;
 // ?AptTooltipHolder::AptTooltipHolder present-unmatched
 AptTooltipHolder():ptr(0){}
 // ?AptTooltipHolder::~AptTooltipHolder present-unmatched
 ~AptTooltipHolder(){ ((Rva000AD6F4*)this)->clear(); }
};
Rva00224CDC *rva00224D80() {
 static AptTooltipHolder holder;
 if(!holder.ptr) {
  ((Rva00575674*)&holder)->rva00575674((Object*)new Rva00224CDC);
  holder.ptr->slot08();
 }
 return (Rva00224CDC*)holder.ptr;
}

// ??0AptPlayer@@QAE@XZ retail 0x00224E10 (320B). WB B8F880 names the
// AptPlayer constructor (AptPlayer.cpp:251); vtable 0x00BE6E80 is the one the
// rowed destructor 0x00224A90 reinstalls. Target facts: base
// SubsystemInterface 0x001B4E63; ten twenty-byte tables at +0x0C..+0xB8 built
// through hash_map ctor 0x00224C76 except the twelve-byte tree at +0x84
// (0x000D3A71); fourteen 0x28-byte level slots at +0xCC (element ctor 0x00224C95,
// dtor 0x00224252); the empty vector header at +0x2FC (0x00211E58); then the
// start time and the flag/word block to +0x329. The first player becomes the
// global at 0x009FE4CC and builds the tooltip map. Member element types are
// the existing rows' spellings; their original types are unproven.
#include <hash_map>
#include <set>
#include <vector>
typedef int Bool;
#include "subsystem_interface.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
struct Rva00224C76Element {Rva00224C76Element();Rva00224C76Element(const Rva00224C76Element&);Rva00224C76Element&operator=(const Rva00224C76Element&);~Rva00224C76Element(){}char bytes[8]; bool operator==(const Rva00224C76Element&)const;};
typedef _STL::hash_map<int, Rva00224C76Element> AptPlayerTable;
class Rva00224C95 { public: Rva00224C95(); ~Rva00224C95(); private: char m_bytes[0x28]; };
class AptPlayer : public SubsystemInterface
{
public:
 AptPlayer();
 virtual ~AptPlayer();
 virtual void init();
 virtual void reset();
 virtual void update();
private:
 AptPlayerTable m_0C, m_20, m_34, m_48, m_5C, m_70;
 _STL::set<AsciiString> m_84;
 AptPlayerTable m_90, m_A4, m_B8;
 Rva00224C95 m_levels[14];
 _STL::vector<int> m_2FC;
 int m_308;
 unsigned long m_startTime;
 bool m_310, m_311, m_312;
 int m_314, m_318, m_31C, m_320;
 int m_324;
 bool m_328, m_329;
};
extern AptPlayer *TheAptPlayer;
AptPlayer::AptPlayer() : m_startTime(timeGetTime()), m_310(false), m_311(false), m_312(false),
 m_314(0), m_318(0), m_31C(0), m_320(0), m_324(-1), m_328(false), m_329(false)
{
 if (TheAptPlayer == 0) {
  TheAptPlayer = this;
  rva00224D80();
 }
}
