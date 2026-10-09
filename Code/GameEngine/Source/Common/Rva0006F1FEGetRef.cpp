// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 0x0006F1FE..0x0006F219, 27B, RET4 (hidden return slot). Returns a new
// counted reference to the object held at +0x40 of the receiver (null stays
// null, otherwise its count at +4 is incremented); the 0x6F219 add routine
// follows it. Receiver and object identities are unproven, address-derived
// names only.
struct Rva0006F1FEObject { void *vptr; int refs; };
struct Rva0006F1FERef {
    Rva0006F1FEObject *m_ptr;
    Rva0006F1FERef(Rva0006F1FEObject *p) : m_ptr(p) { if (m_ptr) ++m_ptr->refs; }
    ~Rva0006F1FERef();
};
class Rva0006F1FEHost {
public:
    Rva0006F1FERef rva0006F1FE(void);
private:
    char pad[0x40];
    Rva0006F1FEObject *m_ref;
};
Rva0006F1FERef Rva0006F1FEHost::rva0006F1FE(void)
{
    return Rva0006F1FERef(m_ref);
}
