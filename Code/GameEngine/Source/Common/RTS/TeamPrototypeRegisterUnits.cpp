// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x003A0D0A 88B, WB twin EF2670 (identity remains address-derived).
// Target facts: owner +08, unit record array +130 with stride18, second name
// +10 in each record, count +1D8; existing TeamTemplateInfo ctor independently
// establishes seven records and that count. Empty object is the exported
// AsciiString::TheEmptyString at RVA9E0878. Registry and +38 append calls use
// their owned opaque providers; their higher-level purpose is not asserted.
#include "ascii_string.h"
class Player;
class Rva004EC05A { public: void rva004EC05A(void *); };
struct Rva002A8AB1Record;
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
struct UnitInfo { int m_00,m_04,m_08; AsciiString m_0c,m_name10; int m_14; };
class TeamPrototype { public: void rva003A0D0A(); private:
 char pad0[8]; Player *owner; char padc[0x130-12]; UnitInfo units[7]; int count;
};
void TeamPrototype::rva003A0D0A()
{
 if(owner) {
  Rva002A8AB1Record *record=g_00DFEEF8->rva002A8AB1(owner);
  if(record) {
   for(int i=0;i<count;++i) {
    if(units[i].m_name10.compare(AsciiString::TheEmptyString)!=0)
     ((Rva004EC05A *)record)->rva004EC05A(&units[i].m_name10);
   }
  }
 }
}
