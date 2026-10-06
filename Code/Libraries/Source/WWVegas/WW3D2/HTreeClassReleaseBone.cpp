// cl: /DNDEBUG /MD /EHsc
//
// ?Release_Bone@HTreeClass@@QAEXH@Z, retail 0x001661F0, 70 bytes.
//
// BFME 2 rewrote Zero Hour's per-pivot IsCaptured flag clear as a sorted
// vector erase of 36-byte captured-bone records (Begin at +0x1C, End at
// +0x20, Index first). Same record model as the landed Is_Bone_Captured unit
// (HTreeClassIsBoneCaptured.cpp) and Control_Bone (htree_control.cpp); the
// tail copy reaches the same random-access copy helper at 0x00161350 the
// vector erase at 0x001661C0 and Free's clear use, with by-reference tag and
// null distance pointer. Identity: pin at 0x001661F0 read from the REL32 at
// the byte-verified Animatable3DObjClass forwarder 0x001A4EE0 (jmp at
// 0x001A4EEA in animobj.cpp). Donor Zero Hour htree.cpp Release_Bone only
// clears a flag; retail follows the vector-erase shape.
// Retail reloads End after the find loop; the volatile read reproduces that
// second load, which /O2+G7 would otherwise CSE away.
struct BfmeRva00161350Tag {};
struct BfmeRva00161350Elem { int Index; unsigned char m_pad[32]; };
BfmeRva00161350Elem *__cdecl bfmeRva00161350(BfmeRva00161350Elem *first, BfmeRva00161350Elem *last, BfmeRva00161350Elem *result, const BfmeRva00161350Tag &tag, int *distance);
class HTreeClass {
    char m_pad0[28];
    BfmeRva00161350Elem *Begin;
    BfmeRva00161350Elem *End;
    BfmeRva00161350Elem *Capacity;
public:
    void Release_Bone(int boneindex);
};
void HTreeClass::Release_Bone(int boneindex)
{
    BfmeRva00161350Elem *p = Begin;
    BfmeRva00161350Elem *end = End;
    if (p == end)
        return;
    do {
        if (p->Index == boneindex)
            goto found;
        ++p;
    } while (p != end);
    return;
found:
    BfmeRva00161350Elem *finish = *(BfmeRva00161350Elem * volatile *)&End;
    BfmeRva00161350Elem *next = p + 1;
    if (next != finish) {
        BfmeRva00161350Tag tag;
        bfmeRva00161350(next, finish, p, tag, (int *)0);
    }
    --End;
}
