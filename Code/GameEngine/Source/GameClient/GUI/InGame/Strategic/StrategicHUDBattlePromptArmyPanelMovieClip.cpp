// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?SetUnitIconString@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z @ 0x005FF450 (109B).
// Apt Unit text setter; formats APT:_level%u.%s_Unit%s%d from m_level at +4 and team name at +8.
// Team pointer null uses g_Rva0107301CEmptyString; manager via g_bfmeAptWindowManager.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF593 0x005FFA3C; precedent AptPlayerNameSet 0x005FB770.
// Retail imports the numeric parsers but uses the game's local allocator.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP
extern "C" void __cdecl free(void *);
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
    // Borrowed manager prefix: native OnClicked reads this32-bit word.
    char m_pad000[0x318];
    int m_word318;
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
	char m_pad;
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../../Common/BattlePromptArmyPanelClipImplView.h"

int __cdecl Rva0052519DFire(void *, void *, const char *, const char *, int *);

void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetUnitIconString(int count, const char *kind, const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_name08.str();
	key.format("APT:_level%u.%s_Unit%s%d", m_level, team, kind, count);
	((BfmeAptWindowManager *)g_bfmeAptWindowManager)->bfmeSetText(key, text, true);
}

// ?SetArmyNameString@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z @ 0x005FF3E9 (103B).
// Apt Army name setter; formats APT:_level%u.%s_ArmyName from m_level at +4 and team name at +8.
// Same layout and globals as SetUnitIconString above; team null uses empty string.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF5DB 0x005FF8D4.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetArmyNameString(const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_name08.str();
	key.format("APT:_level%u.%s_ArmyName", m_level, team);
	((BfmeAptWindowManager *)g_bfmeAptWindowManager)->bfmeSetText(key, text, true);
}

// ?SetUnitIconCount@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXH@Z @ 0x005FF9D8 118B
// SetUnitIconCount via rowed Rva0052519DFire then BfmePod8 resize to count with fill {0,-1}
// then Quantity text per new index via own SetUnitIconString with UnicodeString::TheEmptyString.
// Evidence: callees rowed 0x0052519D 0x005FF96A 0x005FF450; globals g_bfmeAptWindowManager
// g_Rva0107301CEmptyString TheEmptyString; strings SetUnitIconCount Quantity; layout +4 level
// +8 team +0x30 icons; caller jmp 0x005FFA51; precedent Rva0035ABC0Resize.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetUnitIconCount(int count)
{
	BfmePod8Vector *vec = &m_icons;
	int cur = vec->end() - vec->begin();
	if (count == cur)
		return;
	const char *team = m_name08.str();
	Rva0052519DFire(g_bfmeAptWindowManager, (void *)m_level, team, "SetUnitIconCount", &count);
	BfmePod8 fill;
	fill.a[0] = 0;
	fill.a[1] = -1;
	vec->resize((unsigned int)count, fill);
	for (int i = cur; i < count; ++i)
		SetUnitIconString(i, "Quantity", UnicodeString::TheEmptyString);
}

class Rva00524306 {
public:
 void rva00524306(const StringBase<char> &key);
 void rva00524725(const AsciiString &key, const Image *image);
};
UnicodeString __cdecl Rva005FF207Format(int quantity);
// WB 016393E0, StrategicHUDBattlePromptArmyPanelMovieClip.cpp:245-246.
// Native 005FF4F8..005FF5B8 is the complete 192-byte cache update.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetUnitIconProperties(int index, const Image *image, int quantity)
{
 BfmePod8 *slot = m_icons.begin() + index;
 if (image != (const Image *)slot->a[0]) {
  AsciiString key;
  const char *team = m_name08.str();
  key.format("_level%u.%s_UnitIcon%d", m_level, team, index);
  if (image) ((Rva00524306 *)&m_images18)->rva00524725(key,image);
  else ((Rva00524306 *)&m_images18)->rva00524306(*(const StringBase<char> *)&key);
  slot->a[0] = (int)image;
 }
 if (quantity != slot->a[1]) {
  SetUnitIconString(index,"Quantity",Rva005FF207Format(quantity));
  slot->a[1] = quantity;
 }
}
// Unindexed native entry, bounded by the 005FF5B8 tail-jump and the next
// wrapper at 005FF5EE. compare/set calls and the +2C member prove this cache.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::rva005FF5C0(const UnicodeString &text)
{
 if (text.compare(m_cached2C)) {
  SetArmyNameString(text);
  m_cached2C = text;
 }
}
class Rva005FF5B8 {
public: void rva005FF5B8(int index,const Image *image,int quantity);
private: char m_pad[4]; StrategicHUD::BattlePromptArmyPanelMovieClip::Impl *m_04;
};
void Rva005FF5B8::rva005FF5B8(int index,const Image *image,int quantity)
{ m_04->SetUnitIconProperties(index,image,quantity); }
class Rva005FF5EE {
public: void rva005FF5EE(const UnicodeString &text);
private: char m_pad[4]; StrategicHUD::BattlePromptArmyPanelMovieClip::Impl *m_04;
};
void Rva005FF5EE::rva005FF5EE(const UnicodeString &text)
{ m_04->rva005FF5C0(text); }

#include "../../../../Common/BattlePromptMovieClipView.h"
class Rva005FF267 { public: void rva005FF267(int); };
// Native 005FF4BD is the +04 child forwarder used by panel ctor 005FF0F6.
void Rva005FED2A::rva005FF4BD(int state)
{
    ((Rva005FF267 *)m_04)->rva005FF267(state);
}

// Native 005FADEF uses this inherited clip at panel +08 to change its selected overlay.
void Rva005FED2A::rva005FF4CD(bool flag)
{
    ((StrategicHUD::BattlePromptArmyPanelMovieClip::Impl *)m_04)->SetSelected(flag);
}

// WorldBuilder01639000 SetSelected and01639120 SetMouseOver; native101/92B.
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *, void *, const char *, const char *, const char **);
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetSelected(bool flag)
{
    if (flag == m_selected3C) return;
    const char *state = flag ? "_show" : (m_over3D ? "_over" : "_hide");
    Rva0050E9FEAptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_level, m_name08.str(), "SetSelectionOverlayState", &state);
    m_selected3C = flag;
}
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetMouseOver(bool flag)
{
    if (flag == m_over3D) return;
    if (!m_selected3C) {
        const char *state = flag ? "_over" : "_rollOut";
        Rva0050E9FEAptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_level, m_name08.str(), "SetSelectionOverlayState", &state);
    }
    m_over3D = flag;
}

// Constructor005FF675 binds these native65-byte entries to the two unit-icon
// roll events. Both check a signed decimal index against the eight-byte slots.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnUnitIconRollOver(const char *indexText)
{
    if (indexText && isdigit(*indexText)) {
        int index = atoi(indexText);
        if (index >= 0 && (unsigned)index < (unsigned)(m_icons.end() - m_icons.begin()))
            m_parent00->slot04(index);
    }
}
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnUnitIconRollOut(const char *indexText)
{
    if (indexText && isdigit(*indexText)) {
        int index = atoi(indexText);
        if (index >= 0 && (unsigned)index < (unsigned)(m_icons.end() - m_icons.begin()))
            m_parent00->slot05(index);
    }
}

// WB016399F0 OnClicked line315; constructor005FF675 binds this native
// 24-byte RET4 body to _OnClicked. The path is ignored; manager word318
// gates owner virtual slot01. Owner interface name remains unknown.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnClicked(const char *)
{
    if (!g_bfmeAptWindowManager->m_word318) m_parent00->slot01();
}

// Native constructor005FF675 binds _OnRollOver/_OnRollOut to the existing
// folded10-byte entries005C790D/005F057A. Neither has a separate retail body.
// ?StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnRollOver present-unmatched
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnRollOver(const char *)
{ m_parent00->slot02(); }
// ?StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnRollOut present-unmatched
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::OnRollOut(const char *)
{ m_parent00->slot03(); }

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}


// Full native005FF675..005FF8F8 RET12; WB01638760 constructor.
StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::Impl(Rva005FF912 *owner, int level, const AsciiString &name)
 : m_parent00((BattlePromptArmyPanelClipEvents *)owner), m_level(level), m_name08(name), m_state24(0), m_portrait28(0), m_selected3C(false), m_over3D(false)
{
    AsciiString prefix;
    prefix.format("_level%u.",m_level);
    m_commands0C.AddCommandMapDelegate(prefix + m_name08 + "_OnClicked", DelegateDesc(this,&Impl::OnClicked));
    m_commands0C.AddCommandMapDelegate(prefix + m_name08 + "_OnRollOver", DelegateDesc(this,&Impl::OnRollOver));
    m_commands0C.AddCommandMapDelegate(prefix + m_name08 + "_OnRollOut", DelegateDesc(this,&Impl::OnRollOut));
    m_commands0C.AddCommandMapDelegate(prefix + m_name08 + "_OnUnitIconRollOver", DelegateDesc(this,&Impl::OnUnitIconRollOver));
    m_commands0C.AddCommandMapDelegate(prefix + m_name08 + "_OnUnitIconRollOut", DelegateDesc(this,&Impl::OnUnitIconRollOut));
    SetArmyNameString(UnicodeString::TheEmptyString);
}
