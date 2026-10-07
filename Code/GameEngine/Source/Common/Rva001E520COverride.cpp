// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 001E520C..001E525A, 78 bytes, RET4; incoming ECX is unused.
// Existing rowed assignment 001E3955 fixes the template's neutral name.
// Constructor 001E4ABE..001E4DB0 only initializes fields and cannot throw.
// Allocation size 0x154, override link +4 and flag +8 are target facts.
// CrateSystem::newCrateTemplateOverride supplies the source pattern;
// original receiver and member names remain unknown.
class Rva001E3955
{
public:
    Rva001E3955() throw();
    Rva001E3955 &operator=(const Rva001E3955 &rhs);
    void setNextOverride(Rva001E3955 *next) { m_next = next; }
    void markAsOverride() { m_override = true; }
private:
    void *m_vptr;
    Rva001E3955 *m_next;
    bool m_override;
    char m_unknown09[0x154 - 9];
};
class Rva001E520C
{
public:
    Rva001E3955 *rva001E520C(Rva001E3955 *original);
};
extern unsigned char g_00E01EA8;
Rva001E3955 *Rva001E520C::rva001E520C(Rva001E3955 *original)
{
    if (!original)
        return 0;
    Rva001E3955 *result = new Rva001E3955;
    g_00E01EA8 = 1;
    *result = *original;
    g_00E01EA8 = 0;
    original->setNextOverride(result);
    result->markAsOverride();
    return result;
}
