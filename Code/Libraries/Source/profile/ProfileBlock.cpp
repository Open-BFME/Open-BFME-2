// cl: /MD /EHsc
// ZH profile_highlevel.cpp Block constructor is the primary semantic lead.
// Native6C65F0..6C67E7 establishes a three-argument worker/RET12, linked
// current-block pointer E0C624, Id0 timestamp8 previous10 and dotted names.
// BFME2 adds parent-name qualification, value .v and optional calls .c IDs.
// The original class/method identity is unproved: retain an address name.
#include <windows.h>
#include <string.h>
#include "internal.h"
inline const char *ProfileHighLevel::Id::GetName() const {
 return m_idPtr ? m_idPtr->GetName() : NULL;
}
// ?ProfileHighLevel::Id::Increment present-unmatched
inline void ProfileHighLevel::Id::Increment(double add) {
 if(m_idPtr) m_idPtr->Increment(add);
}
class Rva006C65F0 {
public:
 Rva006C65F0(const char *,const char *,bool);
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
  strcpy(qualified,previous->id.GetName());
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
