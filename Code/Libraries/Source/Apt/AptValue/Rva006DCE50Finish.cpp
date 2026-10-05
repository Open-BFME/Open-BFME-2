// cl: /O2 /DNDEBUG /MD
// ?checkedString@BfmeAptValue006DCD20@@QAEPAV1@XZ @0x006DCE50, 68 bytes.
//
// NOT a copy of the sibling checked casts: the assert prefix at +0..+0x2D is
// identical (isString predicate, "isString()" at AptValue.inl:732, the break
// global, the int3), but this body does not return this. Its tail dispatches
// on the value payload: the flags dword at +4 masked with 0xFE000000 compared
// against 0x02000000 yields `this` when equal and the string pointer at +0x20
// otherwise. 0x02000000 is the type-1 slot the rowed isString accepts (types 1
// or 42, see AptValueTypePredicatesBFME2.cpp), so the two selects are
// consistent with target evidence rather than a guessed constant.
// Evidence: assert string VA 0x00CEAF58 and AptValue.inl line 0x2DC are read
// from the retail pushes; the +0x20 load feeds the rowed
// ?toInteger@BfmeAptValue006DCD20@@QBEHXZ type-1 string path, whose note
// records this opaque resolver and the string accessor at +0x20.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class BfmeAptValue006DCD20 {
    virtual void vtableSlot0();
    unsigned int m_flags; // +4, signed 7-bit type in bits 25..31
    unsigned char m_padTo20[0x18];
public:
    int isString() const;
    BfmeAptValue006DCD20 *checkedString();
private:
    void *m_string; // +0x20, AptValue string payload
};

BfmeAptValue006DCD20 *BfmeAptValue006DCD20::checkedString()
{
    if (!static_cast<unsigned char>(isString())) {
        g_bfmeAptAssertAtE17734("isString()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x2DC);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    if ((m_flags & 0xFE000000u) == 0x02000000u)
        return this;
    return reinterpret_cast<BfmeAptValue006DCD20 *>(m_string);
}