#ifndef BFME2_BATTLE_PROMPT_COUNTER_VIEW_H
#define BFME2_BATTLE_PROMPT_COUNTER_VIEW_H

// Address-derived views shared by the army-summary visitor and its counter.
// Retail 005FEF11 installs the one-slot C7A460 table and zeros +04..+20.
// Its slot is 005FED99; the callback reads a string at +04 and count at +90.
class AsciiString;
struct Rva005FED99Arg
{
    char m_pad00[4];
    char m_04[0x90 - 4];
    int m_90;
};
class Rva0040CFC7Pred
{
public:
    virtual bool rva005FED99(const Rva005FED99Arg *) = 0;
    ~Rva0040CFC7Pred() {}
};
struct Rva0040CFC7Entry
{
    int m_00;
    const Rva005FED99Arg *m_04;
};
class Rva0040CFC7
{
    int m_pad[0x40 / 4];
    Rva0040CFC7Entry *m_40;
    Rva0040CFC7Entry *m_44;
public:
    void rva0040CFC7(Rva0040CFC7Pred *);
};
struct Rva005FEF11Input
{
    char m_pad00[0x78];
    Rva0040CFC7 *m_78;
};
class Rva005FED61 : public Rva0040CFC7Pred
{
public:
    Rva005FED61(const Rva005FEF11Input *);
    virtual bool rva005FED99(const Rva005FED99Arg *);
    void rva005FED61(const AsciiString *, int);
    void rva005FEE8C(const Rva005FEF11Input *);
private:
    int m_counts04[8];
};

#endif
