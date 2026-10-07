// cl: /O1 /MD
// Native Ghidra0x005D4E22..0x005D4E37 (21B, RET8). ECX is retained
// in EAX as the result. Stack words supply a writable byte pointer and
// an opaque 32-bit value stored at receiver+0/+4; the pointed-to byte is
// then cleared. Returning the receiver is independently observed, and
// fixes the earlier void-model register-allocation miss. Names, original
// constructor/method identity, full class extent and word meaning remain
// unresolved; this is an address-qualified storage/ABI view.
class Rva005D4E22 {
public: Rva005D4E22 &initialize(char *buffer,unsigned int word);
private: char *m_buffer; unsigned int m_word;
};
Rva005D4E22 &Rva005D4E22::initialize(char *buffer,unsigned int word)
{
 m_buffer=buffer; m_word=word; *buffer=0; return *this;
}
