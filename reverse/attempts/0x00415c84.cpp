// ?assignMembers@Rva00415C84@@QAEPAV1@ABV1@@Z
// partial score=0.8974358974 date=2026-10-04
// cl: /O1 /Ob2 /GX- /GS
// BFME1 source lead5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv1623.cpp, sibling profile.
// Its39B emitted copy-constructor shape is NOT a proven target constructor:
// native415C84 first calls rowed StringBase narrow copy SET132 at366F0,
// copies the word at+4, then calls tree-like assignment115 at4159E2 on+8.
// That helper's live8B header-pointer/word view is supported by existing
// Rva0041580E cleanup/dtor and native sentinel parent/left/right accesses.
// The donor's second4B string member and complete12B record layout are refused.
// This target-address view records just witnessed fields/protocols, at least
// 16B; original owner, complete layout and original method/lifetime are unknown.
// Remaining blocker: assign helper4159E2 and its unrowed clone415937.
#include "../../Code/Libraries/Source/WWVegas/WWLib/string_base.h"
struct Rva0041580EHead {
    unsigned m_bits00;
    Rva0041580EHead *m_root04;
    Rva0041580EHead *m_left08;
    Rva0041580EHead *m_right0C;
};
struct Rva0041580E {
    Rva0041580EHead *m_head00;
    unsigned m_word04;
    Rva0041580E *rva004159E2(const Rva0041580E &other);
    void rva00415886();
    __forceinline Rva0041580EHead *&rootRef() { return m_head00->m_root04; }
    Rva0041580EHead *rva00415937(Rva0041580EHead *root,Rva0041580EHead *parent);
};
class Rva00415C84 {
public:
    Rva00415C84 *assignMembers(const Rva00415C84 &other);
private:
    StringBase<char> m_string00;
    unsigned m_word04;
    Rva0041580E m_tree08;
};
Rva00415C84 *Rva00415C84::assignMembers(const Rva00415C84 &other) {
    m_string00.set(other.m_string00);
    m_word04=other.m_word04;
    m_tree08.rva004159E2(other.m_tree08);
    return this;
}

// Native assignment115: self guard, existing clear41, clone other root into
// this sentinel, refresh both extreme pointers, and copy the word/count bits.
// No original container/key/value or complete node layout is asserted.
Rva0041580E *Rva0041580E::rva004159E2(const Rva0041580E &other) {
    if (this!=&other) {
        rva00415886();
        m_word04=0;
        if (other.m_head00->m_root04==0) {
            m_head00->m_root04=0;
            m_head00->m_left08=m_head00;
            m_head00->m_right0C=m_head00;
        } else {
            rootRef()=rva00415937(other.m_head00->m_root04,m_head00);
            Rva0041580EHead *cur=m_head00->m_root04;
            while(cur->m_left08) cur=cur->m_left08;
            m_head00->m_left08=cur;
            cur=m_head00->m_root04;
            while(cur->m_right0C) cur=cur->m_right0C;
            m_head00->m_right0C=cur;
            m_word04=other.m_word04;
        }
    }
    return this;
}
