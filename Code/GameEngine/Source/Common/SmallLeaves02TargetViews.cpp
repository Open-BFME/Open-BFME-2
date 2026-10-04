// cl: /O1 /DNDEBUG /MD /EHsc
// Whole clean BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/Common/UnclaimedSmallLeaves02.cpp.
// Native bodies below independently establish these accesses and call contracts.
// Original classes, field meanings and full object sizes remain unknown.
// These address-based partial views retain the donor's integer spelling;
// the call-free native loads/stores do not establish scalar signedness.
#pragma pack(push, 1)

class Rva00176D60
{
public:
    int get() const;
private:
    int *m_pointer;
};

// Native: INT3 before176D60 and afterRET176D6B; nullable first pointer,
// returning its first word or0. The zero arm176D69 is an internal branch.
int Rva00176D60::get() const
{
    return m_pointer ? *m_pointer : 0;
}

class Rva00167E1C
{
public:
    void set(int on);
private:
    char m_prefix20[0x20];
    bool m_flag20;
};

// Native: predecessorRET4 at167E19, complete14B at167E1C throughRET4,
// then next body167E2A; stack word is tested against0, SETNE stored at+20.
void Rva00167E1C::set(int on)
{
    m_flag20 = on != 0;
}

class Rva0006341B
{
public:
    void reset();
private:
    char m_prefix08[8];
    int m_word08;
};

// Native: predecessorRET at6341A, complete11B before next Ghidra body63426,
// rdata pointer7C5988 names this entry; conditionally zeroes the+8 word.
void Rva0006341B::reset()
{
    if (m_word08)
        m_word08 = 0;
}

struct Rva00170B92Inner
{
    char m_prefix08[8];
    int m_word08;
};

class Rva00170B92
{
public:
    void sync();
private:
    char m_prefix08[8];
    Rva00170B92Inner *m_inner;
    char m_gap0C[8];
    int m_word14;
};

// Native: Ghidra34B predecessor170B70 endsRET4 at170B8F; complete10B
// from170B92 throughRET170B9B, then next stack-argument body170B9C.
// Copies word+8 through receiver pointer+8 to receiver word+14.
void Rva00170B92::sync()
{
    m_word14 = m_inner->m_word08;
}

#pragma pack(pop)