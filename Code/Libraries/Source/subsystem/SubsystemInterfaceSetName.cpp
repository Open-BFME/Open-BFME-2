// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?setName@SubsystemInterface@@QAEXVAsciiString@@@Z,
// retail 0x0006F3CC, 52 bytes. Dedicated shard.
//
// Out-of-line m_name assignment at +0x08 taking AsciiString by value.
// Retail callees 0x366F0 (AsciiString copy assignment) and 0x36410
// (AsciiString dtor for the by-value arg) are already pinned; the EH prolog
// with cookie plus state handling comes from /EHsc. Shard (not graft) so the
// landed initSubsystem caller in SubsystemInterface.cpp keeps calling
// out-of-line instead of inlining.

class AsciiString
{
public:
	AsciiString& operator=(const AsciiString& other);
	~AsciiString();
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

void SubsystemInterface::setName(AsciiString name)
{
	AsciiString& nameSlot = m_name;
	nameSlot = name;
}
