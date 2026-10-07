// cl: /O1 /MD
// Native Ghidra0x005CDCC2..0x005CDCDC (26B, RET8). The receiver is
// returned in EAX. The second stack argument supplies four DWORDs copied
// to receiver+0..0xC; the first supplies the word stored at +0x10.
// Original class/constructor identity and full object extents are unknown.
// The payload aggregate and unsigned word are observed storage/ABI views.
struct Payload005CDCC2 { unsigned int words[4]; };
class Rva005CDCC2 {
public: Rva005CDCC2 &initialize(unsigned int word,const Payload005CDCC2 &payload);
private: Payload005CDCC2 m_payload; unsigned int m_word;
};
Rva005CDCC2 &Rva005CDCC2::initialize(unsigned int word,const Payload005CDCC2 &payload)
{
 m_payload=payload; m_word=word; return *this;
}
