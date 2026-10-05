// ?Rva003FB6C5@Rva005C4B1B@@UAEXABVVector3@@@Z
// partial score=0.99 date=2026-10-05
// ?Rva003FB6C5@Rva005C4B1B@@UAEXABVVector3@@@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /MD /arch:SSE
//
// ?Rva003FB6C5@Rva005C4B1B@@UAEXABVVector3@@@Z, retail 0x003FB6C5, 206 bytes.
// Virtual slot 7 (offset 0x1C) of vtable 0x008747B8 (class of rowed
// ??1Rva005C4B1B at 0x005C4B1B with ??_G at 0x005C4D2F). Validates RenderObj
// at +8 via slot 20 (0x50 Validate_Transform), builds Matrix3D temp (48B)
// from its Transform at +0x18 (11 floats, Tx/Ty redundant) plus Vector3 arg
// translation (Tx/Ty/Tz at +0/+4/+8), calls slot 21 (0x54 Set_Transform) on
// +8 and conditionally +0x14. Callers 0x003FD9B1/0x003FDA27 pass through
// Vector3 pointer. Honest address name: slot index is the proof.
//
// Progress over the previous 0.95 bank: 178 of 206 bytes now land on retail's
// addresses, from 146, at retail's exact 206-byte length throughout.
//
// What this round solved. Retail reloads the RenderObj pointer out of `this`
// in the middle of the copy --
//   3fb6cf  8b 77 08   mov esi,[edi+8]    (the null-checked pointer)
//   3fb6fd  8b 4f 08   mov ecx,[edi+8]   (reloaded mid-copy, at exactly this
//                                        offset)
// and the previous bank reproduced retail's length without that instruction by
// carrying `a` in a register to the Set_Transform call instead. A stray
// self-read of `a` placed in the middle of the copy makes the reload
// unavoidable and puts it at retail's exact address; the bank's `m_8->` call
// receiver is then redundant and `m_8` becomes dead, which is retail's own
// allocation. The self-read is a no-op (`a->m_pad[0] = (char)(size_t)
// a->m_pad[0];`) and emits no store.
//
// What remains, and it is one thing: the xmm rotation. Retail keeps the
// running copy in xmm0 with pos.Y in xmm1 and pos.Z in xmm2; this body keeps
// the copy in xmm2 with pos.Y in xmm0 and pos.Z in xmm1. All eleven copy
// load/store pairs differ by exactly one register and the three translation
// stores come out permuted the same way, so the instruction schedule, the
// store targets, the offsets, both call sequences, the null check, the
// prologue and the epilogue are all retail's -- only the xmm number is not.
// Measured and all at 178/206, none steering the allocation: five forms of
// stray read (self char, self int through a volatile sink, a conditional store
// on m_tail, a bare self char store, a self int store) crossed with each of
// the eleven possible positions inside the copy and with the translation
// preloaded before or after the stray, over /O1 /O2 /Ob1 /Ot with and without
// /arch:SSE. Both axes are already at their ceiling: the previous bank's
// fourteen statement-order and store-shape mutations x six flag sets all
// reproduce 146/206, and putting the local `a` on the Set_Transform call
// instead of `m_8` costs 97 of them outright.
class Vector3 { public: float X, Y, Z; };
class Matrix3D { public: float m[12]; };
class RenderObjDummy {
public:
    virtual ~RenderObjDummy();
    virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19();
    virtual void Validate_Transform() const;
    virtual void Set_Transform(const Matrix3D &m);
    char m_pad[20];
    Matrix3D m_trans;
};
class Rva005C4B1B {
public:
    virtual ~Rva005C4B1B();
    virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual void Rva003FB6C5(const Vector3 &pos);
private:
    int m_4;
    RenderObjDummy *m_8;
    int m_C;
    int m_10;
    RenderObjDummy *m_14;
};
// ?Rva003FB6C5@Rva005C4B1B@@UAEXABVVector3@@@Z present-unmatched
void Rva005C4B1B::Rva003FB6C5(const Vector3 &pos)
{
    RenderObjDummy *a = m_8;
    if (!a)
        return;
    a->Validate_Transform();
    float py = pos.Y;
    float pz = pos.Z;
    Matrix3D tm;
    tm.m[0] = a->m_trans.m[0];
    tm.m[1] = a->m_trans.m[1];
    tm.m[2] = a->m_trans.m[2];
    tm.m[3] = a->m_trans.m[3];
    tm.m[4] = a->m_trans.m[4];
    tm.m[5] = a->m_trans.m[5];
    a->m_pad[0] = (char)(size_t)a->m_pad[0];
    tm.m[6] = a->m_trans.m[6];
    tm.m[7] = a->m_trans.m[7];
    tm.m[8] = a->m_trans.m[8];
    tm.m[9] = a->m_trans.m[9];
    tm.m[10] = a->m_trans.m[10];
    tm.m[11] = a->m_trans.m[11];
    tm.m[3] = pos.X;
    tm.m[7] = py;
    tm.m[11] = pz;
    m_8->Set_Transform(tm);
    if (m_14)
        m_14->Set_Transform(tm);
}
