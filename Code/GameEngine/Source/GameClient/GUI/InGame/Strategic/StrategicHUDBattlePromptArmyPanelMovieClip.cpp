// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?SetUnitIconString@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z @ 0x005FF450 (109B).
// Apt Unit text setter; formats APT:_level%u.%s_Unit%s%d from m_level at +4 and team name at +8.
// Team pointer null uses g_Rva0107301CEmptyString; manager via TheRva00222A8BTarget.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF593 0x005FFA3C; precedent AptPlayerNameSet 0x005FB770.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
	char m_pad;
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005FF450Team
{
	char m_pad[8];
	char m_name[1];
};

struct BfmePod8
{
	int a[2];
};

class BfmePod8Vector
{
public:
	void resize(unsigned int n, BfmePod8 x);
	BfmePod8 *m_begin;
	BfmePod8 *m_end;
private:
	void *m_alloc;
};

int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);

class Image;
namespace StrategicHUD {
class BattlePromptArmyPanelMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl
{
public:
	void SetUnitIconProperties(int index, const Image *image, int quantity);
    void rva005FF5C0(const UnicodeString &text);
	void SetUnitIconString(int count, const char *kind, const UnicodeString &text);
	void SetArmyNameString(const UnicodeString &text);
	void SetUnitIconCount(int count);
private:
	char m_pad[4];
	unsigned int m_level;
	Rva005FF450Team *m_team;
	char m_padC[0x18-0xC];
    char m_images18[0x2C-0x18];
    UnicodeString m_cached2C;
	BfmePod8Vector m_icons;
};

void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetUnitIconString(int count, const char *kind, const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_team ? m_team->m_name : "";
	key.format("APT:_level%u.%s_Unit%s%d", m_level, team, kind, count);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

// ?SetArmyNameString@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z @ 0x005FF3E9 (103B).
// Apt Army name setter; formats APT:_level%u.%s_ArmyName from m_level at +4 and team name at +8.
// Same layout and globals as SetUnitIconString above; team null uses empty string.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF5DB 0x005FF8D4.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetArmyNameString(const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_team ? m_team->m_name : "";
	key.format("APT:_level%u.%s_ArmyName", m_level, team);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

// ?SetUnitIconCount@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEXH@Z @ 0x005FF9D8 118B
// SetUnitIconCount via rowed Rva0052519DFire then BfmePod8 resize to count with fill {0,-1}
// then Quantity text per new index via own SetUnitIconString with UnicodeString::TheEmptyString.
// Evidence: callees rowed 0x0052519D 0x005FF96A 0x005FF450; globals TheRva00222A8BTarget
// g_Rva0107301CEmptyString TheEmptyString; strings SetUnitIconCount Quantity; layout +4 level
// +8 team +0x30 icons; caller jmp 0x005FFA51; precedent Rva0035ABC0Resize.
void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetUnitIconCount(int count)
{
	BfmePod8Vector *vec = &m_icons;
	int cur = vec->m_end - vec->m_begin;
	if (count == cur)
		return;
	const char *team = m_team ? m_team->m_name : "";
	Rva0052519DFire(TheRva00222A8BTarget, (void *)m_level, team, "SetUnitIconCount", &count);
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
 BfmePod8 *slot = m_icons.m_begin + index;
 if (image != (const Image *)slot->a[0]) {
  AsciiString key;
  const char *team = m_team ? m_team->m_name : "";
  key.format("_level%u.%s_UnitIcon%d", m_level, team, index);
  if (image) ((Rva00524306 *)m_images18)->rva00524725(key,image);
  else ((Rva00524306 *)m_images18)->rva00524306(*(const StringBase<char> *)&key);
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
