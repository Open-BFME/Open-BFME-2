// cl: /MD
//
// ?rva002BE8D4@Rva002BE8D4@@QAE_NXZ, RVA 0x002BE8D4, 25 bytes.
// Or-predicate: true when byte at +0x78 is non-zero or the 0x00DFE1C8
// singleton's byte at +0x2C0 is non-zero. Single-return || shares the
// xor+inc true block and keeps zero in al for both compares under /O1.
// Evidence: callers at 0x002B5A39/0x0042CB07/0x0042D0D8 pass the 0x00DFEF18
// object as this and test al; same family as Rva0023C6A4 check.

class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva002BE8D4
{
public:
    bool rva002BE8D4();

private:
    char m_pad[0x78];
    unsigned char m_78;
};

bool Rva002BE8D4::rva002BE8D4()
{
    return m_78 != 0 || *(unsigned char *)((char *)TheLivingWorldManager + 0x2C0) != 0;
}
