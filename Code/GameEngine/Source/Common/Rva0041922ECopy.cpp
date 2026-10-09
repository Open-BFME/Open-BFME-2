// cl: /O1 /Ireference/shims/bfme2_ascii /EHs /MD
#include "ascii_string.h"
// Native41922E..41926B constructs an AsciiString at0 and the established
// 28-byte record4191E5 at4. This differs from the two-string pair twin
// in its second member's callee. Original container/record identity unknown.
class Rva00419035 {
public: Rva00419035(const Rva00419035 &);
private: char m_pad[12];
};
class BfmeFixedStorage002CF0F0 {
public: BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
private: char m_pad[12];
};
struct Rva004191E5 {
 Rva004191E5(const Rva004191E5 &);
 AsciiString m_00; Rva00419035 m_04; BfmeFixedStorage002CF0F0 m_10;
};
struct Rva0041922E {
 Rva0041922E(const Rva0041922E &);
 AsciiString m_00; Rva004191E5 m_04;
};
Rva0041922E::Rva0041922E(const Rva0041922E &o):m_00(o.m_00),m_04(o.m_04){}
