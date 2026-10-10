// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?setName@SubsystemInterface@@QAEXVAsciiString@@@Z
// retail 0x0006F3CC, 52 bytes. Dedicated shard.
//
// Out-of-line m_name assignment at +0x08 taking AsciiString by value.
// Retail callees 0x366F0 (AsciiString copy assignment) and 0x36410
// (AsciiString dtor for the by-value arg) are already pinned; the EH prolog
// with cookie plus state handling comes from /EHsc. Shard (not graft) so the
// landed initSubsystem caller in SubsystemInterface.cpp keeps calling
// out-of-line instead of inlining.

// The canonical AsciiString: its copy assignment calls StringBase<char>::set
// (0x366F0) and its dtor the releaseBuffer worker (0x36410), the two names
// those addresses carry as rows. A private operator= spelling resolved to
// ascii_string.cpp's ??4AsciiString row (0x00001733) instead, so the link
// judged this copy not retail's.
#include "ascii_string.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	void setName(AsciiString name);

private:
	char m_padAfterVptr[4];
	AsciiString m_name;
};

inline void SubsystemInterface::setName(AsciiString name)
{
	AsciiString& nameSlot = m_name;
	nameSlot = name;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (SubsystemInterface::*_bfmeInlineAnchor_SubsystemInterfaceSetName_0)(AsciiString name) = &SubsystemInterface::setName;
