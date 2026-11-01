// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?getStartFrame@SubtitleManager@@QBEHH@Z retail 0x00688680 (98B).
// Evidence: the assert string at VA 0x00CE4558 reads "Index out of range in
// SubTitleManager::GetStartFrame."; the class layout (m_entries vector at
// +0x14) and the Debug slots 0x60/0x6C/0x38/0x4C match the
// SubtitleManagerAccessors.cpp sibling and the Rva003625C3Glow Debug shape.
// The near file parseSubtitle.cpp already links this manager.

#include "unicode_string.h"

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);

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

// The entry list at +0x14 is a vector of SubtitleEntry pointers; this unit
// spells only its three words and the inline size()/operator[] it uses, so
// the TU keeps its own STLport-free C++-linkage free binding.
struct SubtitleEntryList
{
	SubtitleEntry *const *begin() const { return m_start; }
	SubtitleEntry *const *end() const { return m_finish; }
	unsigned int size() const { return (unsigned int)(end() - begin()); }
	SubtitleEntry *const &operator[](unsigned int n) const { return *(begin() + n); }

	SubtitleEntry **m_start;
	SubtitleEntry **m_finish;
	SubtitleEntry **m_endOfStorage;
};

class SubtitleManager
{
public:
	int getStartFrame(int index) const;

private:
	char m_pad[0x14];
	SubtitleEntryList m_entries;
};

int SubtitleManager::getStartFrame(int index) const
{
	if (index < (int)m_entries.size())
		return m_entries[index]->m_startFrame;
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Index out of range in SubTitleManager::GetStartFrame.").CrashDone(1);
	return 0x7fffffff;
}
