#pragma once
// Native 0x88-byte event prefix, distinct from the 0x90-byte vector wrapper.
// The radar notification at 0x002AA9C2 reserves 0x88 for constructor2D97D6;
// W3DTruckDraw independently embeds two events at +0x374/+0x3FC (stride0x88).
// Constructor/default-member stores and initializer2D96D3 establish the fields.
// The vector copy51B40 delegates its prefix to2D99E3 then copies +0x88/+0x8C.
// Original field/type names remain unasserted. AudioEventRTS is the semantic
// lead from GeneralsMD at BFME1 revision6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Provider aliases reuse the already verified common-prefix initializer and
// virtual destructor/scalar destructor; they add no duplicate retail bodies.
#include "ascii_string.h"
class Xfer;
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
typedef long Long;
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(Long volatile *addend);
struct BfmePoolHolder88
{
    unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};
class BfmePoolRef08
{
	OpaqueRefCounted *m_target;
public:
    // ?BfmePoolRef08::BfmePoolRef08 present-unmatched
    __forceinline BfmePoolRef08() : m_target(0) {}
	__forceinline ~BfmePoolRef08() { if (m_target != 0) m_target->Release_Ref(); }
};
class BfmePoolRef10
{
    BfmePoolHolder88 *m_target;
public:
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
    // ?BfmePoolRef10::BfmePoolRef10 present-unmatched
    __forceinline BfmePoolRef10() : m_target(0) {}
    BfmePoolRef10(BfmePoolHolder88 *p);
    BfmePoolRef10(const BfmePoolRef10 &other);
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva000519BD();
    void rva00053D26(BfmePoolHolder88 *p);
};
struct OpaqueRefElement4 { OpaqueRefCounted *referent; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &); };
class Rva000A8C9B { public: void clear(); };
struct BfmeEventPositionView {
    float x,y,z;
    // The native value-returning position worker copies each coordinate;
    // these constructors preserve that return ABI without changing the layout.
    BfmeEventPositionView() {}
    BfmeEventPositionView(const BfmeEventPositionView &p) : x(p.x), y(p.y), z(p.z) {}
    BfmeEventPositionView(float a, float b, float c) : x(a), y(b), z(c) {}
    // ?BfmeEventPositionView::zero present-unmatched
    __forceinline void zero() { x=0.0f; y=0.0f; z=0.0f; }
};
enum ObjectID;
enum DrawableID;
struct BfmeAudioEventPrefix136
{
    BfmeAudioEventPrefix136(const OpaqueRefElement4 &, int);
    BfmeAudioEventPrefix136(const OpaqueRefElement4 &, const BfmeEventPositionView &, int);
    // Native owner overloads2DA461/2DA4DB; Lua ObjectPlaySound and
    // CurDrawablePlaySound prove the corresponding ID domains.
    BfmeAudioEventPrefix136(const OpaqueRefElement4 &, ObjectID);
    BfmeAudioEventPrefix136(const OpaqueRefElement4 &, DrawableID);
    // Native copy constructor2D99E3: default member stores, then copy worker2D9893.
    BfmeAudioEventPrefix136(const BfmeAudioEventPrefix136 &);
    virtual ~BfmeAudioEventPrefix136();
    AsciiString m_string04;
    BfmePoolRef08 m_pool08;
    int m_int0C;
    BfmePoolRef10 m_pool10;
    int m_int14;
    int m_int18;
    AsciiString m_string1C;
    AsciiString m_string20;
    float m_f24;
    float m_f28;
    float m_f2C;
    int m_int30;
    int m_int34;
    int m_int38;
    BfmeEventPositionView m_position;
    unsigned char m_b48;
    unsigned char m_b49;
    unsigned char m_b4A;
    unsigned char m_b4B;
    unsigned char m_b4C;
    unsigned char m_b4D;
    unsigned char m_b4E;
    unsigned char m_b4F;
    unsigned char m_b50;
    unsigned char m_b51;
    unsigned char m_b52;
    unsigned char m_b53;
    float m_f54;
    float m_f58;
    float m_f5C;
    float m_f60;
    float m_f64;
    int m_int68;
    int m_int6C;
    int m_int70;
    int m_int74;
    int m_int78;
    int m_int7C;
    int m_int80;
    AsciiString m_string84;
    void rva002D96D3(const OpaqueRefElement4 &);
    // Rowed copy worker2D9893 (skips the vptr); operator= 2D9A31 wraps it.
    void rva002D9893(const BfmeAudioEventPrefix136 &);
    // Non-virtual xfer 0x002D9FD9 (W3DTruckDraw::xfer calls it on both events).
    void rva002D9FD9(Xfer *xfer);
    BfmeEventPositionView rva002DA1CC(bool &valid);
};

#pragma comment(linker, "/alternatename:??1BfmeAudioEventPrefix136@@UAE@XZ=??1BfmeStringTailRecord144@@UAE@XZ")
#pragma comment(linker, "/alternatename:??_GBfmeAudioEventPrefix136@@UAEPAXI@Z=??_GBfmeStringTailRecord144@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?rva002D96D3@BfmeAudioEventPrefix136@@QAEXABUOpaqueRefElement4@@@Z=?rva002D96D3@BfmeStringTailRecord144@@QAEXABUOpaqueRefElement4@@@Z")
#pragma comment(linker, "/alternatename:?rva002D9893@BfmeAudioEventPrefix136@@QAEXABU1@@Z=?rva002D9893@Rva002D9893@@QAEXABV1@@Z")
typedef char VerifyAudioPrefixSize[(sizeof(BfmeAudioEventPrefix136) == 0x88) ? 1 : -1];
