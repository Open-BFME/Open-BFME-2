// Target facts (code addresses are RVAs): Rva0052413E has no virtual functions or base-class table. Its constructor 0x001F81BF calls 0x00211E58 on unchanged this; stores at 0x00211E65 and 0x00211E67 clear +0/+4, and the call at 0x00211E6A initializes +8 through 0x0014F3C4. That complete call chain only initializes pointers and cannot throw. Neither lifetime body stores a vptr. The table store at 0x0057C176 (VA 0x00C6F2D4) belongs to the enclosing object; its +0x0C member is constructed at 0x0057C18D, and its following flag at +0x18 is written at 0x0057C196, bounding this member to 0x0C bytes.
// The nonvirtual destructor 0x0052413E calls clear 0x00523F22 at 0x00524150 and vector<AsciiString> destruction 0x0002CC70 at 0x0052415C, both with unchanged this. Clear compares +0/+4 at 0x00523F4E..0x00523F50 and decrements +4 by four at 0x00523F42; vector push_back compares +4/+8 at 0x0002DBEC..0x0002DBEF and advances +4 by four at 0x0002DBFD. These are begin, finish and allocation-end pointers at +0/+4/+8, represented by opaque four-byte-aligned storage; their original member name is unproven.
// The owner constructor 0x005EF92D constructs this member at +0x0C (call 0x005EF962) and the next member at +0x18 (call 0x005EF96E); its destructor 0x005EFB05 calls 0x0052413E on +0x0C at 0x005EFB44. The constructor and destructor remain declarations so consumers call those existing out-of-line bodies. There is no constructor/destructor vftable disagreement for this class, and no destructor table or virtual slot belongs to it.
#ifndef BFME2_COMMON_RVA0052413E_H
#define BFME2_COMMON_RVA0052413E_H

class Rva0052413E
{
public:
    Rva0052413E() throw();
    ~Rva0052413E();

private:
    __declspec(align(4)) char m_storage[12];
};

#endif
