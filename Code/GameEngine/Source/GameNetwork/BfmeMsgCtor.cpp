// cl: /DNDEBUG /MD
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1BfmeMsgVJH@@QAE@XZ=??1BfmeMsgVJH@@UAE@XZ")

// BfmeMsg::~BfmeMsg at 0x00655780 (7B). The FESL message base (vtable
// 0xCE0BC4) proven by the landed BfmeMsgVJH ctor row. The 7B direct vptr
// reinstall (no eax homing) is a trivial destructor, not a constructor:
// MSVC 7.1 ctors copy this to EAX (they return it), dtors do not. The 16B
// sibling stays matched under the PrototypeClass ICF alias (it is the
// ctor: vptr plus m_state zero). The 121 image-wide direct callers are
// explicit base destructions at FESL message-creation sites.

class BfmeMsg
{
public:
    virtual ~BfmeMsg();

    // NOTE: the full base has an int m_state at +4 (proven by the landed
    // VJH row and the 16B sibling zeroing [eax+4]), omitted here because
    // this body never touches it.
};

BfmeMsg::~BfmeMsg()
{
}

// BfmeMsgVJH is the derived message type constructed at 0x00655900. Its
// virtual dtor restores the same BfmeMsg base vptr as this base dtor, so its
// retail body at 0x00655780 is an ICF alias of the row above.
class BfmeMsgVJH : public BfmeMsg
{
public:
	virtual ~BfmeMsgVJH();
};

BfmeMsgVJH::~BfmeMsgVJH()
{
}

// ??_GBfmeMsg@@UAEPAXI@Z, retail 0x00655880 (29B), is emitted by the
// delete below. The trivial dtor inlines to nothing, leaving the vptr
// reinstall plus conditional operator delete (no dtor call, like retail).

// Anchor: emits the ??_G scalar-deleting-destructor COMDAT.
void deleteBfmeMsg(BfmeMsg *p)
{
    delete p;
}

// Generated callers name this vptr-reinstall destructor by its placeholder pin (0x00655780, thiscall, no args); bind that spelling here.
#pragma comment(linker, "/alternatename:?m@Gen_007e86c0@@QAEXXZ=??1BfmeMsg@@UAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?clear@BfmeC994@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Gen00808FB0@@UAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsg1052@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva00800780Addr@@QAE@XZ=??1BfmeMsg@@UAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDone1045@BfmeSub1045@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsgVJI@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDtorTWB@BfmeStrTWB@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDoneVJO@BfmeMsgVJO@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsg803BF0@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsg803A00@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsg803B60@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDtorTWA@BfmeStrTWA@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1BfmeMsg803C90@@QAE@XZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDoneVJN@BfmeMsgVJN@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDoneVJM@BfmeMsgVJM@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDoneVJL@BfmeMsgVJL@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDoneVJK@BfmeMsgVJK@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeDtorTWC@BfmeHeadTWC@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeReset1015@BfmeL1015@@QAEXXZ=??1BfmeMsg@@UAE@XZ")
