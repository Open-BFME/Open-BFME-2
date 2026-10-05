// cl: /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the change-notify setter at 0x00318BC6 (37B): if the
// +0x70 word differs from the argument, forward the argument to the +0x88
// helper object (callee 0x003FDE1A, pinned from the retail call) and store
// it. All names are address-derived; the offsets and the null-guard shape
// are target facts.
class Rva003FDE1AHelper {
public:
    void rva003FDE1A(int value);
};

class Rva00318BC6Owner {
public:
    void rva00318BC6(int value);
private:
    unsigned char pad00[0x70];
    int m_70;
    unsigned char pad74[0x88 - 0x74];
    Rva003FDE1AHelper* m_88;
};

void Rva00318BC6Owner::rva00318BC6(int value)
{
    if (m_70 != value) {
        if (m_88 != 0)
            m_88->rva003FDE1A(value);
        m_70 = value;
    }
}
