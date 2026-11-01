// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??1SubtitleEntry@@MAE@XZ 0x006885A0 14B: SubtitleEntry dtor (protected virtual).
// Retail mov [ecx],0x8E451C then add ecx,4 then jmp releaseBuffer 0x36E70.
// BFME1 donor SubtitleEntryConstructorDestructor.cpp proves protected virtual
// and the wide text at +4 with scalars and bool after. Caller is ??_G at
// 0x006886F0 and Unwind. Vtable 0x008E451C slot 0 is the ??_G. The text is
// the shared header's UnicodeString, whose inline dtor is the bare
// releaseBuffer (?releaseBuffer@?$StringBase@G@@AAEXXZ); the class is the
// SubtitleEntry.cpp TU's view.
#include "unicode_string.h"

// vftable 0x008E451C: slot 0 is the deleting dtor 0x006886F0 over the
// protected virtual dtor 0x006885A0 (vptr store, then the text member's
// releaseBuffer). The ctor 0x00688550 stores that vptr and copy-constructs
// the text at +0x04; SubtitleManager::getStartFrame 0x00688680 reads
// m_startFrame (+0x18) directly.
class SubtitleEntry
{
	friend class SubtitleManager;
public:
	SubtitleEntry(const UnicodeString &text, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);
protected:
	virtual ~SubtitleEntry();
private:
	UnicodeString m_text;
	unsigned int m_color;
	int m_style;
	int m_alignment;
	int m_line;
	int m_startFrame;
	int m_endFrame;
	bool m_displayed;
};

SubtitleEntry::~SubtitleEntry() {}
