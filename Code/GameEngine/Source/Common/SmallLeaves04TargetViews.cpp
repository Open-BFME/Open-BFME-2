// cl: /O2 /DNDEBUG /MD /EHsc
// Clean whole BFME1 donor at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/Common/UnclaimedSmallLeaves04.cpp.
// Native entries independently establish the receiver-first-word access.
// Original classes, field meanings, full object sizes and signedness are unknown.
// Integer spelling is carried from the donor, not asserted as a target fact.

class Rva006CFD30
{
public:
    int step();
private:
    int m_word;
};

// Native: INT3 padding before 6CFD30 and after terminal RET at 6CFD35.
// Preincrements receiver's first word and returns its new value.
int Rva006CFD30::step()
{
    return ++m_word;
}

class Rva006CFD40
{
public:
    int step();
private:
    int m_word;
};

// Native: INT3 padding before 6CFD40 and after terminal RET at 6CFD45.
// Predecrements receiver's first word and returns its new value.
int Rva006CFD40::step()
{
    return --m_word;
}
