// Target facts (code addresses are RVAs; tables are VAs): constructor 0x005FA7EB stores table 0x00C078DC at 0x005FA7FB and its Impl pointer at +4 at 0x005FA827. It allocates 0x64 bytes at 0x005FA7F9 for Impl, whose constructor 0x005FA3B1 receives this as its owner. Derived constructor 0x005E9CC3 calls 0x005FA7EB at 0x005E9D00 and stores its own first member at +8 at 0x005E9D1C, bounding the base to sizeof 8. No parent constructor or additional base subobject is established.
// Target facts: destructor 0x005FA393 restores the same 0x00C078DC table, adjusts this by 4 and jumps to the owning-pointer cleanup 0x005FA146. Table 0x00C078DC has five __purecall entries (RVA 0x0003B810), followed by the separately installed table 0x00C078F0. Derived table 0x00C78078 contains callbacks 0x005E95A8, 0x005E95B9, 0x005E965A, 0x005E9669 and 0x005E9678, followed by string data. None is a destructor: this class has five virtual callbacks and a nonvirtual destructor. Folded purecall tables alone establish no parent identity.
// Target facts: Impl callbacks 0x005F8E7D, 0x005F8E94, 0x005F8EAA, 0x005F8EBA and 0x005F8ECA call owner slots 1, 0, 2, 3 and 4 without arguments. Their names do not establish the owner's callback names. AddAlly 0x005FA3A1 and AddEnemy 0x005FA3A9 load Impl from +4 and tail-call 0x005FA205 and 0x005FA2CC; caller 0x005E9B4A passes the ledger's Rva005F91F3Src record. The constructor, destructor and these methods remain out-of-line declarations.
#ifndef BFME2_BATTLEPROMPTMOVIECLIP_H
#define BFME2_BATTLEPROMPTMOVIECLIP_H

class AsciiString;
struct Rva005F91F3Src;

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
    class Impl;

    BattlePromptMovieClip(int level, const AsciiString &name, const Rva005F91F3Src &ally);
    ~BattlePromptMovieClip();

    virtual void vslot00() = 0;
    virtual void vslot01() = 0;
    virtual void vslot02() = 0;
    virtual void vslot03() = 0;
    virtual void vslot04() = 0;

    void AddAlly(const Rva005F91F3Src &ally);
    void AddEnemy(const Rva005F91F3Src &enemy);

private:
    Impl *m_impl;
};
}

// The class unqualified: header_adopt_lane's layout probe names the header's classes so.
using StrategicHUD::BattlePromptMovieClip;

#endif
