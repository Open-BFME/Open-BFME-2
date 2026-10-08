// cl: /DNDEBUG /MD /EHsc
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

template <class T> class StringBase
{
	friend class AsciiString;
	void releaseBuffer();
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString& operator=(const AsciiString& other);
	~AsciiString() { releaseBuffer(); }
};

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
