// cl: /DNDEBUG /MD /EHsc
// The handle-from-plain constructor at 0x00785140 installs VA 0x01126AB8
// and increments its target's WORD count at +4. That vtable's slot 0 reaches
// 0x007851A0 through ILT 0x00017DAA; it calls the destructor at 0x007851D0.
// This is a counted resource handle, not NetCommandRef: it releases through
// 0x009EB7A0 and restores base vtable VA 0x01126A80. Real BFME network refs
// have no vptr and use the 12-byte destructor at 0x00676280.
// The owning class remains address-named, consistent with its proven ctor.
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/CountedAsset.h"
class Rva00782CB0
{
public:
    Rva00782CB0();
    virtual ~Rva00782CB0();
    virtual int slot04() = 0;
    virtual int slot08() { return 0; }
    virtual int slot0C() { return 0; }
    virtual int slot10() { return 0; }
};
// ??0Rva00782CB0@@QAE@XZ @0x000A8EB9 9B: the default constructor, storing the
// class's own vtable (VA 0x00BC93C8) and returning this.
Rva00782CB0::Rva00782CB0()
{
}
// Retail's table (VA 0x00BC940C), in slot order: the deleting destructor,
// folded 0x000910FB (returns 1), the base's folded 0x000D43D0, folded
// 0x0047A6A9 (returns this) and folded 0x005C4AD1 (the address of +4).
class Rva00785140Handle : public Rva00782CB0
{
public:
    virtual ~Rva00785140Handle();
    virtual int slot04() { return 1; }
    virtual int slot0C() { return (int)this; }
    virtual int slot10() { return (int)&m_target; }
private:
    CountedAsset *m_target;
};
Rva00785140Handle::~Rva00785140Handle()
{
    if (m_target)
        m_target->Release_Ref();
}

// ??1Rva00782CB0@@UAE@XZ @0x000A8EC2 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline).
Rva00782CB0::~Rva00782CB0()
{
}
