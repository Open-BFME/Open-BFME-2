// cl: /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 27B forwarder at 0x0031979C: resolve the argument
// through the +0x78 helper (callee 0x0040CB79, pinned from the retail
// call), then run the sibling 0x319517 body on the result (pinned from
// its call; same this). All names are address-derived.
class Rva0040CB79Helper {
public:
    int rva0040CB79(int value);
};

class Rva0031979COwner {
public:
    void rva00319517(int value);
    void rva0031979C(int value);
private:
    unsigned char pad00[0x78];
    Rva0040CB79Helper* m_78;
};

void Rva0031979COwner::rva0031979C(int value)
{
    int r = m_78->rva0040CB79(value);
    rva00319517(r);
}
