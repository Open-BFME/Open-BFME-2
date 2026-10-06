// ?rva00245F14@GameLogic@@QAEXUMyEntry@@@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00245F14@GameLogic@@QAEXUMyEntry@@@Z @0x00245F14 101B u2 exact-shape.
// Unlock: callee of 0x00245F79; GameLogic +0x1C0 list; AsciiString set/push.
// Evidence: rowed set 0x000366F0 plus push_back 0x00242EE7 plus releaseBuffer 0x00036410 plus prev 0x00245EDF GameLogic plus direct-receiver lever.
// Bytes exact vs retail (0 regions, only relocs); callee list names need Rva vs AsciiString resolution for gate.
// The target address 0x00242EE7 is already owned by a matched STLport
// list<Rva00242EE7Obj*> push_back. The MyEntry/MyList spellings here are
// codegen probes only; bytes do not settle the element type or owner, and a
// second real-name pin is not justified by this caller alone.
#include "ascii_string.h"
struct MyEntry { AsciiString s; unsigned short id; };
class MyList { public: void push_back(const MyEntry &e); };
class GameLogic {
public:
  void rva00245F14(MyEntry e);
private:
  char pad[0x1C0];
  MyList lst;
};
// ?rva00245F14@GameLogic@@QAEXUMyEntry@@@Z present-unmatched
void GameLogic::rva00245F14(MyEntry e) {
  MyEntry tmp;
  tmp.s.set(e.s);
  tmp.id = e.id;
  ((MyList*)((char*)this + 0x1C0))->push_back(tmp);
}
