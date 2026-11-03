// Target facts (code addresses are RVAs; table addresses are VAs): ctor 0x0031454D clears the dwords at +4/+8 and stores 0x00C0BBF8 at +0; dtor 0x003148E6 restores that same table and jumps to 0x00314581. These bodies are rowed as Rva0031455E. Derived ctor 0x00521623 calls 0x0031454D and places its first member at +0x0C, bounding this pointer-bearing prefix to 12 bytes without an additional base.
// Table 0x00C0BBF8 has five slots: deleting dtor 0x003149EA, link 0x0031455E, unlink 0x00314581, input dispatch 0x00314596 and system dispatch 0x003145B1; the next word at 0x00C0BC0C is string data. The link body reads its argument's +0x1DC, not this object's storage. Slot names remain structural because those rows use another class spelling or nonvirtual ledger names.
// 0x00314596 dispatches through the pointer at +4 slot 3 or +8 slot 1; 0x003145B1 uses +4 slot 4 or +8 slot 2, then own slot 2 for message 2. Both take three ints and return int. Their ledger names below are nonvirtual out-of-line entry points. TargetA/TargetB and m_04/m_08 retain neutral private-view labels for the two four-byte pointers.
#ifndef BFME2_GAMELOGIC_RVA003145B1_H
#define BFME2_GAMELOGIC_RVA003145B1_H

class TargetA;
class TargetB;

class Rva003145B1
{
public:
    virtual ~Rva003145B1();
    virtual void vslot01(void *);
    virtual void v2();
    virtual int vslot03(int, int, int);
    virtual int vslot04(int, int, int);

    int Rva003145B1Dispatch(int, int, int);
    int rva00314596(int, int, int);

private:
    TargetA *m_04;
    TargetB *m_08;
};

#endif
