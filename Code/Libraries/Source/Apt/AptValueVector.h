// Target facts (all code addresses are RVAs): AptValueVector has no virtual functions. Constructor 0x006E6CF0 stores the integer argument at +0, zeroes +4 and +0xC, and stores the allocated AptValue pointer array at +8; no vtable is stored. Push 0x006E6C00 compares +4 against +0, indexes +8 in four-byte steps, and raises +0xC to the new count. Assertions at 0x006CC040 and 0x006E6CF0 name mCurrentNum and mpValues; the other field names remain neutral.
// Target facts: initializer 0x006CF230 allocates 0x10 bytes at 0x006CF873/0x006CF8BE and calls the constructor at 0x006CF890/0x006CF8DB. Cleanup 0x006E6D50 frees the +8 array with size 4 * [+0]; deleting-shaped helper 0x006CC350 calls it and optionally frees 0x10 bytes, with no vtable access or store. Sized operator delete 0x006D8680 is called by the initializer's unwind actions 0x007A8300/0x007A830F. No constructor or destructor vtable belongs to this plain 16-byte class.
// Target facts: out-of-line ledger methods are Allocate 0x006CC020, GetData 0x006CBFD0 (address of +8), const operator[] 0x006CC040, rva006CC0A0 0x006CC0A0, rva006CC350 0x006CC350, rva006E6C00 0x006E6C00, PopValue 0x006E6C90, rva006E6D50 0x006E6D50 and ReleaseValues 0x006E6D90. The retail call at 0x006CE1E8 to the pinned const GetNumValues uses 0x007244B0, whose four bytes load the dword at +4 and return. These methods and the constructor are declared out of line.

#pragma once

#ifndef BFME2_APTVALUEVECTOR_H
#define BFME2_APTVALUEVECTOR_H

class AptValue;

class AptValueVector
{
    int field00;
    int mCurrentNum;
    AptValue **mpValues;
    int field0C;

public:
    AptValueVector(int capacity);
    static void *Allocate(int size);
    static void operator delete(void *block, unsigned int size);
    AptValue ***GetData();
    int GetNumValues() const;
    AptValue *operator[](int iPos) const;
    void rva006CC0A0(int iPos);
    AptValueVector *rva006CC350(unsigned int flag);
    void rva006E6C00(AptValue *pValue);
    AptValue *PopValue();
    void rva006E6D50();
    void ReleaseValues();
};

#endif
