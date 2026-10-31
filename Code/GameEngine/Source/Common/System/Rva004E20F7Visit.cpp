// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// Target-only view of the complete 110B destructor at 0x003EF14A.
// The queue's Rva00382574 name is refuted by this body's different layout.
// Target facts: primary vptr C363C8; unregister this from global E02E88 via
// matched 2B7250; cleanup 3EE9F1(this); secondary vptr at +4C becomes
// C363B8; destroy narrow strings +1C/+18 via matched 36410; destroy the
// container at +8 through 4E2E58; restore primary base vptr BFDF68.
// Original class, container type, and member names remain unknown.
#include "ascii_string.h"



class Rva004E2E58Value;
// stlport
#include <set>

// Only the two called vslots and reference word are recovered. The names
// and signatures of unused slots remain opaque in this local call view.
class Rva003EE9F1Ref {
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2C() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual void slot38() = 0;
    virtual void slot3C() = 0;
    virtual void slot40() = 0;
    virtual void slot44() = 0;
    virtual void slot48() = 0;
    virtual void slot4C() = 0;
    virtual void slot50() = 0;
    virtual void slot54() = 0;
    virtual void slot58() = 0;
    virtual void slot5C() = 0;
    virtual void slot60() = 0;
    virtual void slot64() = 0;
    virtual void slot68() = 0;
    virtual void slot6C() = 0;
    virtual void slot70() = 0;
    virtual void slot74() = 0;
    virtual Rva003EE9F1Ref *slot78(unsigned key) = 0;
    virtual void slot7C() = 0;
    virtual void slot80() = 0;
    virtual void slot84() = 0;
    virtual void slot88() = 0;
    virtual void slot8C() = 0;
    virtual void slot90() = 0;
    virtual void slot94() = 0;
    virtual void slot98() = 0;
    virtual void slot9C() = 0;
    virtual void slotA0() = 0;
    virtual void slotA4() = 0;
    virtual void slotA8() = 0;
    virtual void slotAC() = 0;
    virtual void slotB0() = 0;
    virtual void slotB4() = 0;
    virtual void slotB8() = 0;
    virtual void slotBC() = 0;
    virtual void slotC0() = 0;
    virtual void slotC4() = 0;
    virtual void slotC8() = 0;
    virtual void slotCC() = 0;
    virtual void slotD0() = 0;
    virtual void slotD4() = 0;
    virtual void slotD8() = 0;
    virtual void slotDC() = 0;
    virtual void slotE0() = 0;
    virtual void slotE4() = 0;
    virtual void slotE8() = 0;
    virtual void slotEC() = 0;
    virtual void slotF0() = 0;
    virtual void slotF4() = 0;
    virtual void slotF8() = 0;
    virtual void slotFC() = 0;
    virtual void slot100() = 0;
    virtual void slot104() = 0;
    virtual void slot108() = 0;
    virtual void slot10C() = 0;
    virtual void slot110() = 0;
    virtual void slot114() = 0;
    virtual void slot118() = 0;
    virtual void slot11C() = 0;
    virtual void slot120() = 0;
    virtual void slot124() = 0;
    virtual void slot128() = 0;
    virtual void slot12C() = 0;
    virtual void slot130() = 0;
    virtual void slot134() = 0;
    virtual void slot138() = 0;
    virtual void slot13C() = 0;
    virtual void slot140() = 0;
    virtual void slot144() = 0;
    virtual void slot148() = 0;
    virtual void slot14C() = 0;
    virtual void slot150() = 0;
    virtual void slot154() = 0;
    virtual void slot158() = 0;
    virtual void slot15C() = 0;
    virtual void slot160() = 0;
    virtual void slot164() = 0;
    virtual void slot168() = 0;
    virtual void slot16C() = 0;
    virtual void slot170() = 0;
    virtual void slot174() = 0;
    virtual void slot178() = 0;
    virtual void slot17C() = 0;
    virtual void slot180() = 0;
    virtual void slot184() = 0;
    virtual void slot188() = 0;
    virtual void slot18C() = 0;
    virtual void slot190() = 0;
    virtual void slot194(int value) = 0;
    unsigned references;
};

struct Rva00072F7CNode {
    unsigned unknown00;
    Rva00072F7CNode *parent04;
    Rva00072F7CNode *left08;
    Rva00072F7CNode *right0C;
    unsigned value10;
};
struct Rva00072FE6 {
    // Only the receiver at record+8 is known; the remaining record bytes
    // are opaque. This span preserves the independently measured 0x20 stride.
    Rva00072F7CNode *header00;
    unsigned count04;
    char unknown08[0x10];
    void rva00072FE6();
    void rva00072F7C(Rva00072F7CNode *);
};
struct Rva004E2199Record {
    unsigned unknown00;
    Rva003EE9F1Ref *ref04;
    Rva00072FE6 container08;
};
class Rva004E2E58Value {
public:
    virtual ~Rva004E2E58Value();
    void rva004E2199();
    void rva004E20F7(bool force);
private:
    char unknown04[0x10];
    Rva004E2199Record *begin14;
    Rva004E2199Record *end18;
    unsigned unknown1C;
    bool flag20;
    bool flag21;
};


// Native4E20F7..4E2199, 162-byte complete method. The +14/+18 range
// and 32-byte records are independently shared with rowed cleanup4E2199.
// Word payload+10 is passed into record ref's virtual slot78; returned
// counted object receives slot194(1) and reference release, then tree clears.
// Original owner and virtual operation names remain unestablished.
void Rva004E2E58Value::rva004E20F7(bool force)
{
    flag20=false;
    // Two redundant re-reads of flag21 against its own copy: the compare folds
    // away (no bytes) but the extra loads change which operand cl 7.1 puts first
    // in the [base+index] addressing of the record accesses below.
    bool again=flag21;
    if ((flag21 && flag21==again && flag21==again) || force) {
        for (unsigned i=0;i<(unsigned)(end18-begin14);++i) {
            Rva00072F7CNode *node=begin14[i].container08.header00->left08;
            while(node!=begin14[i].container08.header00) {
                Rva003EE9F1Ref *value=begin14[i].ref04->slot78(node->value10);
                if(value) {
                    value->slot194(1);
                    if (--value->references == 0)
                        value->slot00();
                }
                node=(Rva00072F7CNode*)::_STL::_Rb_global<bool>::_M_increment((::_STL::_Rb_tree_node_base*)node);
            }
            begin14[i].container08.rva00072FE6();
        }
    }
}
