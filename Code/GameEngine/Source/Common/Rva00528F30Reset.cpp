// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native528F30..528FD9 RET0; rowed pointer wrapper528FD9 calls this reset.
// WB13CA990 repeats HideCommandInterface and CommandUI/Portrait plus six
// record clears. All offsets and calls below are native facts; owner identity
// remains address-derived. Public AsciiString clear uses its owned worker.
#include "ascii_string.h"
class Rva00222A8BTarget {public:int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);};
class Rva00223A94 {public:int rva00223A94(const AsciiString *);};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00528B98 {public:void rva00528B98();private:void *owner;bool flag04;};
class Rva00528BDD {public:void rva00528BDD();private:void *owner;bool flag04;};
class Rva002BED91 {public:void clear();private:void *reference;};
struct ResetRecord528F30 {Rva002BED91 reference;void *value;char unknown08[12];};
class Rva00528F30Target {
public:void reset();
private:
 char unknown00[4];void *level04;char unknown08[0x2c-8];
 bool flag2C,shown2D;char unknown2E[2];int value30;AsciiString text34;
 Rva00528B98 rank38;char unknown40[16];Rva00528BDD cost50;char unknown58[8];
 void *portrait60;char unknown64[12];ResetRecord528F30 records70[6];
};
void Rva00528F30Target::reset() {
 if(shown2D) {
  rank38.rva00528B98();cost50.rva00528BDD();
  ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(level04,"HideCommandInterface",0,0,0,0,0,0);
  shown2D=false;
  if(portrait60) {
   { AsciiString key("CommandUI/Portrait");
   ((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&key); }
   portrait60=0;
  }
 }
 flag2C=false;value30=0;text34.clear();
 for(int i=0;i<6;++i) {records70[i].reference.clear();records70[i].value=0;}
}

// Owned7-byte pointer forwarder shares its provider view in this TU.
class Rva00528FD9Owner {public:void reset();private:Rva00528F30Target *target;};
void Rva00528FD9Owner::reset() {target->reset();}
