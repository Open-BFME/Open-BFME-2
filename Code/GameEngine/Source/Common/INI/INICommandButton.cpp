// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// ?parseCommandButtonDefinition@ControlBar@@SAXPAVINI@@@Z @0x001DAF81 255B.
// Target identity: WB 0x00AC2A00 names ControlBar::parseCommandButtonDefinition
// in INICommandButton.cpp. Native block registration 0x007AD0B7 binds this parser
// to CommandButton. The complete native boundary ends at 0x001DB080.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/INI/INICommandButton.cpp; compiling the clean
// donor under BFME2 settings placed no bodies. Its find/create/override structure
// is retained, with target load type 5 reload and duplicate-body discard paths.
// Target bytes establish load type +0x08, override byte +0x08, link +0x0C,
// node size 0x2CC, and field-table VA 0x00C15468. Callees not independently named
// remain address-derived; this file reuses their existing verified owners.
// Shared AsciiString supplies constructor and releaseBuffer ownership. The
// temporary's inline cleanup view calls the existing 368B node destructor;
// its member contents are not reconstructed or claimed here.

#include "ascii_string.h"
struct FieldParse;
class INI {
public:
 const char *getNextToken(const char *separators=0);
 void initFromINI(void *,const FieldParse*);
 char pad[8]; int loadType;
};
class Rva0035BB4B { public: virtual ~Rva0035BB4B(); };
class Rva0031AB1ENode {
public:
 Rva0031AB1ENode();
 unsigned char bytes[0x2CC];
 // Cleanup through the existing owned CommandButton destructor ABI.
 ~Rva0031AB1ENode() { ((Rva0035BB4B*)this)->Rva0035BB4B::~Rva0035BB4B(); }
};
class Rva0031BE07 {
public:
 void *rva0031BE07(const StringBase<char>&);
};
class Rva0031AB1EOwner {
public:
 Rva0031AB1ENode *rva0031AB1E(const AsciiString*);
};
class Rva0031BF1B {
public:
 void rva0031BF1B(class ModuleData*);
};
class Rva0031EB96 {
public:
 Rva0031AB1ENode *rva0031EB96(Rva0031AB1ENode*);
};

class ControlBar {
public:
 static void parseCommandButtonDefinition(INI*);
 void rva0031AB77SetFlag();
};
extern ControlBar *TheControlBar;
extern const FieldParse g_00C15468[];
void ControlBar::parseCommandButtonDefinition(INI *ini) {
 AsciiString name(ini->getNextToken());
 Rva0031AB1ENode *button=(Rva0031AB1ENode*)((Rva0031BE07*)TheControlBar)->rva0031BE07(*(StringBase<char>*)&name);
 if(!button) {
  button=((Rva0031AB1EOwner*)TheControlBar)->rva0031AB1E(&name);
  if(ini->loadType==2) button->bytes[8]=1;
 } else if(ini->loadType==5) {
  if(button->bytes[8]) TheControlBar->rva0031AB77SetFlag();
  ((Rva0031BF1B*)TheControlBar)->rva0031BF1B((ModuleData*)button);
  button=((Rva0031AB1EOwner*)TheControlBar)->rva0031AB1E(&name);
  *(int*)(button->bytes+12)=0;
 } else if(ini->loadType==2) {
  button=((Rva0031EB96*)TheControlBar)->rva0031EB96(button);
 } else {
  Rva0031AB1ENode ignored;
  ini->initFromINI(&ignored,g_00C15468);
  return;
 }
 ini->initFromINI(button,g_00C15468);
}


