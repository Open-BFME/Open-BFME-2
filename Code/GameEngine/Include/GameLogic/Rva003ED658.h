// Target facts (retail RVAs): copy constructor 0x003ED658 calls the four-byte-element vector copy 0x002CFAB9 at unchanged this, then retains selected keys through 0x003ED498. Neither that constructor nor destructor 0x003ED94F stores a vptr; this class has no virtual functions or polymorphic base.
// The vector copy reads begin at +0 and end at +4. Its allocation base 0x004F62A4 stores begin at +0, end at +4 and begin + count*4 at +8; 0x003ED498 and 0x003ED7A2 independently read the same begin/end pair. These three words are pointers, not a tree header and count.
// Copy caller 0x004ABF47 constructs this member at +8 and copies the next field at +0x14, bounding its size to 0x0C with four-byte alignment. Destructor 0x003ED94F calls 0x003ED7A2 then frees the pointer at +0; return cleanups 0x003EDDBB and 0x00783788 call it out of line. The enclosing tables stored by 0x0020D98D and 0x004ABF47 belong to their owners, not this member.
#ifndef BFME2_RVA003ED658_H
#define BFME2_RVA003ED658_H

#include "../Common/RvaTreeFamilyHolder.h"

class Rva003ED658
{
public:
    Rva003ED658(const Rva003ED658 &other);
    ~Rva003ED658();

private:
    // Owning begin pointer; the holder's legacy name does not assert a tree
    // pointee. End and capacity remain unsigned-element pointers below.
    RvaTreeFamilyHolder m_field00;
    unsigned int *m_field04;
    unsigned int *m_field08;
};

typedef char Rva003ED658SizeCheck[sizeof(Rva003ED658) == 0x0C ? 1 : -1];

#endif
