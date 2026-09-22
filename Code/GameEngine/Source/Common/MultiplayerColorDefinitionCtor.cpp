// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0MultiplayerColorDefinition@@QAE@XZ, retail 0x00380C4E, 90 bytes.
// Dedicated TU (the shared MultiplayerSettings.cpp TU carries the ZH-shaped
// ctor unmatched; a same-TU definition would also capture its callers'
// REL32 locally -- and that TU's /G7 emits the push-style SEH prologue while
// retail uses the __EH_prolog cookie style here).
//
// BFME1 reference gives the ZH layout (AsciiString + RGBColor + int +
// RGBColor + int = 0x24, cf. reference/open-bfme-1/.../MultiplayerColorDefinitionAssign.cpp).
// BFME2 grew the class: retail touches two more RGBColors at +0x24/+0x30
// (both setFromInt(-1)) and a zeroed byte at +0x3C. The INI parse function
// only reaches the ZH fields, so the growth is invisible to it; the names
// below for the added members are honest placeholders at retail-proven
// offsets, not recovered identities.
// Retail shape, all read off the body: inline-null string default
// (mov [ebx],0), flag byte via shared al-zero, tooltip teardown through the
// 0x36410 fold, setFromInt(-1) on +0x04, 12B movs copy +0x04 -> +0x14, one
// shared -1 (or esi,-1) stored to +0x10/+0x20 and pushed to the +0x24/+0x30
// setFromInt calls. Called from the color-list miss path (lookup 0x3812E6)
// and the new-color path (0x3813B7), which is the identity proof.

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}

private:
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	void clear();
	AsciiString(const AsciiString &other);
	AsciiString &operator=(const AsciiString &other);
	// Inline teardown to the 0x36410 fold (writeNameKey/openDataChunk
	// precedent): temp destruction emits a direct releaseBuffer call, which
	// is what retail does here. A declare-only dtor instead resolves via the
	// evidence-free 0x6CEAD0 pin (re_log proves that address is a 57B
	// list-destroy, not the scalar dtor) and mismatches.
	__forceinline ~AsciiString() { releaseBuffer(); }

protected:
	void releaseBuffer();
};

struct RGBColor
{
	float red;
	float green;
	float blue;
	void setFromInt(int value);
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	MultiplayerColorDefinition *operator=(const MultiplayerColorDefinition &other);
	AsciiString getTooltipName() const;

private:
	AsciiString m_tooltipName; // +0x00
	RGBColor m_rgbValue; // +0x04
	int m_color; // +0x10
	RGBColor m_rgbValueNight; // +0x14
	int m_colorNight; // +0x20
	RGBColor m_rgbExtra1; // +0x24 BFME2 addition (retail setFromInt(-1))
	RGBColor m_rgbExtra2; // +0x30 BFME2 addition (retail setFromInt(-1))
	bool m_extraFlag; // +0x3C BFME2 addition (retail zeroed)
};

typedef char MultiplayerColorDefinitionSizeMatchesRetail[(sizeof(MultiplayerColorDefinition) == 0x40) ? 1 : -1];

// ??0MultiplayerColorDefinition@@QAE@XZ
MultiplayerColorDefinition::MultiplayerColorDefinition()
{
	m_extraFlag = false;
	m_tooltipName.clear();
	m_rgbValue.setFromInt(-1);
	m_rgbValueNight = m_rgbValue;
	// One shared -1 below: retail materializes it once (or esi,-1 reusing the
	// dead movs source) and stores/pushes it four times, while the first
	// setFromInt above keeps its literal push-imm.
	const int unsetWhite = -1;
	m_color = unsetWhite;
	m_colorNight = unsetWhite;
	m_rgbExtra1.setFromInt(unsetWhite);
	m_rgbExtra2.setFromInt(unsetWhite);
}

// ??4MultiplayerColorDefinition@@QAEPAV0@ABV0@@Z, retail 0x00380CAE, 127 bytes.
// Same TU as the ctor (same shells/flags; neither body calls the other, so no
// same-TU capture). Retail reads every member directly off `other` -- only
// the tooltip goes through the out-of-line getter (0x2E4336, pinned) plus the
// 0x366F0 assign fold and the 0x36410 temp teardown -- then copies the two
// BFME2-added RGBColors and the flag byte like the ZH ones.
// ??4MultiplayerColorDefinition@@QAEPAV0@ABV0@@Z
MultiplayerColorDefinition *MultiplayerColorDefinition::operator=(const MultiplayerColorDefinition &other)
{
	m_tooltipName = other.getTooltipName();
	m_rgbValue = other.m_rgbValue;
	m_color = other.m_color;
	m_rgbValueNight = other.m_rgbValueNight;
	m_colorNight = other.m_colorNight;
	m_rgbExtra1 = other.m_rgbExtra1;
	m_rgbExtra2 = other.m_rgbExtra2;
	m_extraFlag = other.m_extraFlag;
	return this;
}
