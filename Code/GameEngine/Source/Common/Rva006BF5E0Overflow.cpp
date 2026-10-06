// BFME2 0x006BF5E0/268B: non-POD 36-byte vector insertion overflow.
// Reference guide: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/Common/Rva0087FBE0Overflow.cpp, reconciled with
// target Ghidra boundary and all seven native REL32 call sites.
// Native allocation calls the existing byte allocator (bytes, hint=0),
// unlike the donor small/large split. Native cleanup expands the release
// loop and free in this body. Load finish before start to retain its order.
// Prefix/suffix and counted fill call the verified workers at 6BE840/6BE8C0;
// the one-record branch calls the existing 63BE4 constructor directly.
// Record application identity remains unknown. These are 36-byte ABI views;
// the nested group preserves the donor constructor-worker layout, and the
// existing named constructor supplies copy behavior independently of it.
// cl: /Ob1 /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc_alloconly
// stlport
#include <memory>
#pragma comment(linker, "/alternatename:?releaseBuffer@BfmeTailBE@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct BfmeFalseBE {};
struct BfmeStringRecord00063BE4 { int words[7]; void *text; unsigned char tail[2]; BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &); };
struct BfmeTailBE { char *m_p; void releaseBuffer(); };
struct BfmeGroup10BE { int m_10, m_14, m_18; BfmeTailBE m_1C; char m_20, m_21; };
struct BfmeElemBE {
    int m_00, m_04, m_08, m_0C;
    BfmeGroup10BE m_10;

};
BfmeElemBE *bfmeCopyBE(const BfmeElemBE *, const BfmeElemBE *, BfmeElemBE *, const BfmeFalseBE &);
BfmeElemBE *bfmeFillBE(BfmeElemBE *, unsigned, const BfmeElemBE &, const BfmeFalseBE &);
class BfmeVecBE {
public:
    void overflow(BfmeElemBE *, const BfmeElemBE &, const BfmeFalseBE &, unsigned, bool);
    BfmeElemBE *_M_start, *_M_finish, *_M_end_of_storage;
};
void BfmeVecBE::overflow(BfmeElemBE *pos, const BfmeElemBE &value,
    const BfmeFalseBE &, unsigned fill, bool atEnd)
{
    unsigned oldSize = (unsigned)(_M_finish - _M_start);
    const unsigned &growth = oldSize < fill ? fill : oldSize;
    unsigned length = growth + oldSize;
    BfmeElemBE *newStart = length ? (BfmeElemBE *)_STL::allocator<char>::allocate(length * sizeof(BfmeElemBE), 0) : 0;
    BfmeElemBE *newFinish = bfmeCopyBE(_M_start, pos, newStart,
        reinterpret_cast<const BfmeFalseBE &>(atEnd));
    if (fill == 1) {
        if (newFinish != 0)
            new ((BfmeStringRecord00063BE4 *)newFinish) BfmeStringRecord00063BE4(*(const BfmeStringRecord00063BE4 *)&value);
        ++newFinish;
    } else {
        newFinish = bfmeFillBE(newFinish, fill, value,
            reinterpret_cast<const BfmeFalseBE &>(atEnd));
    }
    if (!atEnd)
        newFinish = bfmeCopyBE(pos, _M_finish, newFinish,
            reinterpret_cast<const BfmeFalseBE &>(atEnd));
    BfmeElemBE *last = _M_finish;
    BfmeElemBE *first = _M_start;
    for (; first != last; ++first)
        first->m_10.m_1C.releaseBuffer();
    if (_M_start != 0)
        ::free(_M_start);
    _M_start = newStart;
    _M_finish = newFinish;
    _M_end_of_storage = newStart + length;
}
