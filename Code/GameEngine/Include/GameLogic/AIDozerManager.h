// Canonical BFME2 AIDozerManager. Target facts below use RVAs.
// Target facts: AIBuilder's constructor calls 0x00599784 on +0x140 at 0x004EC4F3 with its Player argument, then writes the next member at +0x154 (0x004EC4FB). Its destructor calls 0x005997CD on the same +0x140 receiver at 0x004EC5E0. These lifecycle rows are currently spelled Rva005997CD. Constructor 0x00599784 builds two four-byte list headers at +0/+4 through 0x004EC36C, zeros the AsciiString at +8 (0x005997AE), stores the owner at +0x0C (0x005997B8), and clears byte +0x10 (0x005997BB). The accessed extent and four-byte alignment, bounded by AIBuilder's next member, give sizeof 0x14. Destructor 0x005997CD clears both lists through 0x0023DAA5 and releases the string through 0x00036410 at 0x005997FC, then destroys both list headers through 0x004EC395. The list constructor allocates a twelve-byte self-linked sentinel and stores its pointer at +0 (0x004EC37E..0x004EC38B); the two list headers below retain that pointer storage. Neither lifecycle body installs a vftable or calls a base constructor: this class has no retail virtual functions and no evidenced parent. The tables installed by filters in 0x00599AE3 belong to stack-local filter objects, not this manager. The owner read at 0x0059983D is dereferenced at +0x2EC; 0x00599B48 passes the same +0x0C value to the player relationship filter. The flag is transferred at 0x0059994C and tested as a byte by 0x00599564. The seven ordinary method declarations below follow their ledger rows; their bodies remain out of line. Unproven field names remain neutral.
#ifndef BFME2_CANONICAL_AIDOZERMANAGER_H
#define BFME2_CANONICAL_AIDOZERMANAGER_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Object;
class Player;
class Xfer;

class AIDozerManager
{
public:
    AIDozerManager(int); // 0x00599784
    ~AIDozerManager(); // 0x005997CD

    void buildDozer(Object *); // 0x00599564
    void rva00599606(); // 0x00599606
    void rva00599825(int); // 0x00599825
    void DoXfer(Xfer *); // 0x0059992A
    bool rva00599AE3(Object *); // 0x00599AE3
    void preEmptivelyBuildDozers(); // 0x00599D56
    void rva00599EDC(); // 0x00599EDC

    void *field00;
    void *field04;
    AsciiString field08;
    Player *field0C;
    bool field10;
};

#endif
