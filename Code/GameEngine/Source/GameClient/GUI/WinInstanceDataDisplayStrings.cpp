// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z, retail 0x00322352, 97 bytes.
// New file-unit TU (sibling setters init/setText to follow).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp,
// setTooltipText): allocate the tooltip display string on first use through
// the display-string manager, then give it the text through DisplayString's
// second virtual. DEBUG_ASSERTCRASH compiles out under /DNDEBUG.
// BFME2 facts (all retail-measured):
// - The manager global (0xDFEAD8) is DIR32-masked, so any extern spelling
//   verifies; the name follows the donor.
// - Retail calls the manager's slot 0x38 for the factory (the BFME1 donor's
//   slot 0x24 predates BFME2's wider manager vtable), and the display
//   string's slot 0x04 for the setter.
// - The by-value parameter is copied for the virtual call and destroyed here
//   at the end (MSVC callee-destroys rule for value parameters); the stack
//   temp becomes the callee's parameter, so this body destroys only [ebp+8].
// - The StringBase copy/destructor pins at 0x37050/0x36E70 carry the private
//   (AAE) spelling, so StringBase keeps its copy and releaseBuffer private.
// - m_tooltip sits at +0x1A0 (sibling m_tooltipString ends at +0x194).

typedef int Int;
typedef bool Bool;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

template <typename T>
class StringBase
{
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() { m_data = NULL; }
	~StringBase() { releaseBuffer(); }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &that) : m_data(that.m_data) {}
	~UnicodeString() {}

private:
	StringBase<wchar_t> m_data;
};

// Retail fetch call uses vtable offset 0x38 for the factory (BFME2 widens
// the manager vtable past the donor's slot 0x24); pads stay declared-only
// so no vtable is emitted from this TU (VersionUnicode.cpp recipe).
class DisplayString
{
public:
	virtual ~DisplayString() {}
	virtual void setText(UnicodeString text);
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

class WinInstanceData
{
public:
	void setTooltipText(UnicodeString tip);

private:
	char m_pad[0x1A0];
	DisplayString *m_tooltip;
};

// ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setTooltipText(UnicodeString tip)
{
	// allocate a tooltip display string if needed
	if (m_tooltip == NULL)
		m_tooltip = TheDisplayStringManager->newDisplayString();

	// set text
	m_tooltip->setText(tip);
}
