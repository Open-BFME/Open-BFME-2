// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/bfme2_ascii
// BFME1 donor BfmeThreeStringCopyWH.cpp reviewed at
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d already uses real AsciiString.
// BFME2's complete 77-byte constructor at RVA 0x0021613D copies the
// four-byte strings at +0/+4/+8 through actual StringBase<char>::copy365F0.
// Retail unwind cleanup calls the existing AsciiString destructor48BA39,
// so use the canonical header's declaration-only destructor contract.
// Gen_003A8BE0 remains the donor address label; original owner identity
// and BFME1's donor RVA 0x003A8BE0 are not asserted for the BFME2 target.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class Gen_003A8BE0
{
public:
    Gen_003A8BE0(const Gen_003A8BE0 &other);

    AsciiString m_bfmeFirst;  // +0x00
    AsciiString m_bfmeSecond; // +0x04
    AsciiString m_bfmeThird;  // +0x08
};

Gen_003A8BE0::Gen_003A8BE0(const Gen_003A8BE0 &other)
    : m_bfmeFirst(other.m_bfmeFirst),
      m_bfmeSecond(other.m_bfmeSecond),
      m_bfmeThird(other.m_bfmeThird)
{
}
