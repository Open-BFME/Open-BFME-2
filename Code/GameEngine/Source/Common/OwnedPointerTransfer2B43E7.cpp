// cl: /O1 /MD /EHs
// Consuming owner constructor entry 0x002B43E7..002B4404, RET4.
// The native caller2BB7D6 calls owned getter2B54BB, transfers its pointer
// into an outgoing four-byte Rva002B4349 value, clears the source, and
// constructs the destination at EBP-18 here. The input value is nulled
// before publishing its pointer and then destroyed by owned2B4349.
// That destructor calls Rva004FA2E2 directly and frees the pointee;
// its chain establishes the payload spelling independently. Original
// complete container/constructor names remain unasserted; neutral views
// describe the target ABI and ownership. No applicable named ZH/BF1 donor
// constructor found; target consumer+getter+destructor prove the transfer.
class Rva004FA2E2;
class Rva002B4349 {public: ~Rva002B4349(); Rva004FA2E2 *m_ptr;};
class Rva002B43E7 {public: Rva002B43E7(Rva002B4349 take); Rva004FA2E2 *m_ptr;};
Rva002B43E7::Rva002B43E7(Rva002B4349 take) {Rva004FA2E2 *p=take.m_ptr; take.m_ptr=0;m_ptr=p;}
