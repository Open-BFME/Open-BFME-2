// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5101E2..510233:81B; served125B incorrectly includes adjacent helpers.
// Native RET510232 is followed by distinct add-ECX24 RET4 helper510233
// (independent call reference at510C54) and erase adapter51023E. Native
// vtable word atRVA865684 points at5101E2. WB1359980/tribute.cpp1369..1370
// corroborates enable-once update semantics but supplies no original owner
// or method name. Canonical4B StringBase and Apt-manager owner are used.
// Child at24 shares the proved Rva0050F5A6 array view with rowed5101C0
// router; native tail callee50FFC0..50FFEC is ordinary ECX method RET0.
#include "ascii_string.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int Rva005FB5E6AptCall(Rva00222A8BTarget*,void*,const char*,const char*,const char*);
bool Rva0023D339Get();
class Rva0050F5A6 { public: void rva0050FFC0(); };
class Rva005101E2 { public:
 void rva005101E2();
 char unknown00[8];void *level;AsciiString name;char unknown10[16];bool enabled;char unknown21[3];Rva0050F5A6 *child;
};
void Rva005101E2::rva005101E2() {
 if (!enabled && Rva0023D339Get()) {
  Rva005FB5E6AptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,level,name.str(),"SetState","_enabled");
  enabled=true;
 }
 if (child) child->rva0050FFC0();
}
