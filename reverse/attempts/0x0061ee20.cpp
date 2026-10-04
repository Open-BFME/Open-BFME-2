// ?rva0061EE20@Rva0061EE20@@QAEXXZ
// partial score=1.0 date=2026-10-04
// Bank-only BFME2 port from donor1281192f68 Rva009EB8A0.cpp.
// Native61EE20/36 readsword4, masksFF0000, forwards this viaTheQ1Receiver(E09C0C) to623600.
// Target623600 has2742B boundary and no current C++ provider; do not land an unresolved caller.
// Donor table/name facts in copied comments below refer only to BFME1.
// cl: /O2 /MD
// Retail009EB8A0..009EB8C4: table VA01145744 slot11 (+2C),
// installed by the matched base constructor009EB7D0. Derived prototype
// tables also share this slot. The original method identity is unknown.
// Global pointer VA0134FAAC is the existing Q1 registry receiver.
// The one stacked argument is this object: target009F0FA0 reads its+4
// state bits and+8 key, keeps incoming ECX as the registry, and RET4 at
// 009F144B. The call binding is address-derived and independently checked.
class Rva00623600Element;
class Q1Receiver0134FAAC {
public:
    void rva00623600(Rva00623600Element *);
};
extern Q1Receiver0134FAAC *TheQ1Receiver;
class Rva0061EE20 {
public:
    void rva0061EE20();
private:
    char prefix[4];
    unsigned int word0004;
};
void Rva0061EE20::rva0061EE20()
{
    if ((word0004 & 0xff0000) != 0x30000 && TheQ1Receiver)
        TheQ1Receiver->rva00623600(reinterpret_cast<Rva00623600Element *>(this));
}
