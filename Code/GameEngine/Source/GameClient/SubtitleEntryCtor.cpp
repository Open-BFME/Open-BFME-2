// cl: /Ob0 /MD /EHsc
// Retail 0x00688550 (74B). SubtitleEntry constructor: vptr immediate,
// text member via the shared wide-string copy body, scalar stores, and a
// cleared display flag. Transferred from the BFME1 reconstruction
// (SubtitleEntryConstructorDestructor.cpp); only the ctor is claimed here.
// The text member constructs through the StringBase<wchar_t> copy body at
// 0x37050 (private AAE row, same pattern as the narrow StringBase pins).

extern "C" const void *const vtbl_00CE451C[];  // ??_7SubtitleEntry@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE451C=??_7SubtitleEntry@@6B@")

template <typename T> class StringBase
{
private:
	StringBase(const StringBase &other);
	friend class SubtitleEntry;
public:
	~StringBase();

private:
	char *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
};

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);

private:
	void *m_vft;
	StringBase<unsigned short> m_text;
	unsigned int m_color;
	int m_style;
	int m_alignment;
	int m_line;
	int m_startFrame;
	int m_endFrame;
	bool m_displayed;
};

// ??0SubtitleEntry@@QAE@ABVUnicodeString@@IHHHHH@Z
SubtitleEntry::SubtitleEntry(const UnicodeString &text, unsigned int color,
	int style, int alignment, int line, int startFrame, int endFrame) :
	m_vft((void *)((unsigned int)vtbl_00CE451C)),
	m_text(text),
	m_color(color),
	m_style(style),
	m_alignment(alignment),
	m_line(line),
	m_startFrame(startFrame),
	m_endFrame(endFrame),
	m_displayed(false)
{
}
