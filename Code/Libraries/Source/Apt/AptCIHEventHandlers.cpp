// cl: /MD
// APT0.19.03 Xbox final PDB/MAP supplies AptCIH method spellings.
// Target caller6EE6C0 asserts pContext->isCIH(), obtains its CIH at6EE713,
// checks it using AptCIH.h, and keeps that object in ESI for calls6EF199 /
// 6EF1B6 /6EF218 /6EF27E to the two bodies below. Target virtual slot0C
// returns the hash; its flags at+10 agree with AptNativeHashBFME2.cpp.
// Only the accessed virtual prefix and hash field are modeled. This does not
// claim the complete donor class layout or identities of unused virtual slots.
struct AptNativeHash { unsigned char unaccessed[16]; int eventFlags; };
class AptCIH {
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual AptNativeHash *GetNativeHashVirtual();
public:
    void SetEventHandler(int mask);
    void RemoveEventHandler(int mask);
};
void AptCIH::SetEventHandler(int mask) { AptNativeHash *hash=GetNativeHashVirtual(); hash->eventFlags |= mask; }
void AptCIH::RemoveEventHandler(int mask) { AptNativeHash *hash=GetNativeHashVirtual(); hash->eventFlags &= ~mask; }
