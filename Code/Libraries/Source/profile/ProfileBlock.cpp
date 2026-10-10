// cl: /MD /EHsc /Ireference/shims/sweep
// ZH profile_highlevel.cpp Block constructor is the primary semantic lead.
// Native6C65F0..6C67E7 establishes a three-argument worker/RET12, linked
// current-block pointer E0C624, Id0 timestamp8 previous10 and dotted names.
// BFME2 adds parent-name qualification, value .v and optional calls .c IDs.
// The original class/method identity is unproved: retain an address name.
#include <windows.h>
#include <string.h>
#include "internal.h"
// ProfileHighLevel::Id::GetName is rowed out of line (profile_highlevel.cpp, 0x006C5FB0) and
// retail inlines it below; an inline definition here would emit a second copy under the row's
// name, so the expansion reads Id's one pointer through a layout view.
struct ProfileHighLevelIdView {
 ProfileId *m_idPtr;
};
static inline const char *ProfileHighLevelIdName(const ProfileHighLevel::Id &id) {
 ProfileId *p = ((const ProfileHighLevelIdView &)id).m_idPtr;
 return p ? p->GetName() : NULL;
}
// ?ProfileHighLevel::Id::Increment present-unmatched
inline void ProfileHighLevel::Id::Increment(double add) {
 if(m_idPtr) m_idPtr->Increment(add);
}
class Rva006C65F0 {
public:
 Rva006C65F0(const char *,const char *,bool);
 ~Rva006C65F0();
 void rva006C6000();
 static Rva006C65F0 *current;
private:
 ProfileHighLevel::Id id;
 __int64 start;
 Rva006C65F0 *previous;
};
Rva006C65F0 *Rva006C65F0::current;
Rva006C65F0::Rva006C65F0(const char *name,const char *descr,bool countCalls) {
 previous=current;
 current=this;
 if (!name) return;
 char qualified[512];
 if (strchr(name,'.')) {
  if (name[0]=='.') ++name;
 } else if(previous) {
  strcpy(qualified,ProfileHighLevelIdName(previous->id));
  qualified[strlen(qualified)-2]=0;
  strcat(qualified,".");
  strcat(qualified,name);
  name=qualified;
 }
 char help[256];
 strncpy(help,name,sizeof(help));
 help[sizeof(help)-1-2]=0;
 strcat(help,".v");
 id=ProfileHighLevel::AddProfile(help,descr,"\xb5sec",6,-6);
 if(countCalls) {
  strncpy(help,name,sizeof(help));
  help[sizeof(help)-1-2]=0;
  strcat(help,".c");
  ProfileHighLevel::AddProfile(help,descr,"calls",6,0).Increment();
 }
 ProfileGetTime(start);
}

// Native 006C6000..006C608D: RDTSC time delta, Id increment, restore current,
// and clear the timestamp. ZH Block destructor is the semantic guide; BFME2
// moves this work into a stop-like worker guarded by the nonzero timestamp.
void Rva006C65F0::rva006C6000() {
 if(start) {
  __int64 end;
  ProfileGetTime(end);
  end-=start;
  id.Increment(double(end)/double(Profile::GetClockCyclesPerSecond()));
  current=previous;
  start=0;
 }
}
// Native 006C6090 jumps directly to 006C6000. The owning constructor and
// caller EH cleanup prove this is the destructor of the same 24-byte object.
Rva006C65F0::~Rva006C65F0() {rva006C6000();}
