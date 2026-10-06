// ??0Rva00355C8E@@QAE@PAX0@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ??0Rva00355C8E@@QAE@PAX0@Z, 0x00355C8E, 74B. Address-named derived constructor; packet shows its rowed base ctor, two arguments, and inherited-link call.
class Gen_004902A0
{
public:
    Gen_004902A0();
    virtual ~Gen_004902A0() throw();
    virtual void slot1(void *value);
    Gen_004902A0 *m_next;
};
class Rva00355C8E : public Gen_004902A0
{
public:
    Rva00355C8E(void *first, void *second);
private:
    void *m_first;
    void *m_second;
};
Rva00355C8E::Rva00355C8E(void *first, void *second)
    : Gen_004902A0()
{
    m_second = second;
    m_first = first;
    if (m_next != 0)
        m_next->slot1(first);
}
