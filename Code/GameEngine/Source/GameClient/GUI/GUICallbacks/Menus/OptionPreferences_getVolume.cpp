// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#pragma optimize("y", off)
//
// Real OptionPreferences::getVolume, retail 0x002E4B2D (154 bytes).
// Dedicated TU: BFME2's indexed volume getter generalises BFME1's
// getSoundVolume/getSpeechVolume (same file in reference/open-bfme-1)
// over the five volume keys. The TRUE name is unproven (no ZH/BFME1
// indexed getter exists); getVolume follows the family convention with
// the evidence cited here and in the row notes.
//
// Shape, all retail-measured: index outside 0..4 reads 0.0f; otherwise
// the 20-byte key at the 0x00DBD190 table selects the preference lookup
// (map at this+4 via explicit rebasing cast, in the BFME1 shim spellings
// below); a miss reads the audio settings float at +0x1C plus index and
// scales by 100.0f; a hit runs atof over the mapped text with negatives
// clamped to 0.0. The P4 scheduler (/G7, not /G6) emits the imul stride,
// the fcomip clamp and the index-in-ebx coloring; /Os keeps it 154 bytes.
// Calles resolve through pins: key init/destroy alias the StringBase
// ctor/releaseBuffer pair, the Custom find aliases the pinned _M_find
// worker, atof is the msvcrt import.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl atof(const char *str);

// 20-byte volume preference keys at retail 0x00DBD190 (SFX/Voice/Music/
// Ambient/MovieVolume in index order).
// Matched DIR32 witness (w=1) places this 5-by-20-byte table in .data; the
// index guard below bounds it to five keys, ending at VA 0x00DBD1F4.
#pragma const_seg(".data")
extern const char g_volumePreferenceKeys[5][20] = {
	"SFXVolume", "VoiceVolume", "MusicVolume", "AmbientVolume", "MovieVolume",
};
#pragma const_seg()

// Custom string/map shims, verbatim from reference/open-bfme-1's
// OptionsMenu.cpp: explicit init/destroy instead of a destructor so no
// unwind frame is needed, and the mapped characters read in place.
struct CustomAsciiStringShim
{
	void *m_data;
	void init(const char *s);
	void destroy();
};

struct CustomStringDataShim
{
	UnsignedByte m_header[8]; ///< characters follow at +8
};

struct CustomMapNodeShim
{
	UnsignedByte m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value; ///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
	CustomMapNodeShim *find(CustomAsciiStringShim *key);
};

// BFME2's audio settings carry five default volumes at +0x1C (retail
// measured); BFME1's older layout kept three at +0x80.
struct BfmeAudioSettings
{
	UnsignedByte m_unreconstructed_00[0x1C];
	Real m_defaultVolumes[5];
};

class BfmeAudioVtblIndexed
{
public:
	virtual void _a120_0() = 0;
	virtual void _a120_1() = 0;
	virtual void _a120_2() = 0;
	virtual void _a120_3() = 0;
	virtual void _a120_4() = 0;
	virtual void _a120_5() = 0;
	virtual void _a120_6() = 0;
	virtual void _a120_7() = 0;
	virtual void _a120_8() = 0;
	virtual void _a120_9() = 0;
	virtual void _a120_10() = 0;
	virtual void _a120_11() = 0;
	virtual void _a120_12() = 0;
	virtual void _a120_13() = 0;
	virtual void _a120_14() = 0;
	virtual void _a120_15() = 0;
	virtual void _a120_16() = 0;
	virtual void _a120_17() = 0;
	virtual void _a120_18() = 0;
	virtual void _a120_19() = 0;
	virtual void _a120_20() = 0;
	virtual void _a120_21() = 0;
	virtual void _a120_22() = 0;
	virtual void _a120_23() = 0;
	virtual void _a120_24() = 0;
	virtual void _a120_25() = 0;
	virtual void _a120_26() = 0;
	virtual void _a120_27() = 0;
	virtual void _a120_28() = 0;
	virtual void _a120_29() = 0;
	virtual void _a120_30() = 0;
	virtual void _a120_31() = 0;
	virtual void _a120_32() = 0;
	virtual void _a120_33() = 0;
	virtual void _a120_34() = 0;
	virtual void _a120_35() = 0;
	virtual void _a120_36() = 0;
	virtual void _a120_37() = 0;
	virtual void _a120_38() = 0;
	virtual void _a120_39() = 0;
	virtual void _a120_40() = 0;
	virtual void _a120_41() = 0;
	virtual void _a120_42() = 0;
	virtual void _a120_43() = 0;
	virtual void _a120_44() = 0;
	virtual void _a120_45() = 0;
	virtual void _a120_46() = 0;
	virtual void _a120_47() = 0;
	virtual void _a120_48() = 0;
	virtual void _a120_49() = 0;
	virtual void _a120_50() = 0;
	virtual void _a120_51() = 0;
	virtual void _a120_52() = 0;
	virtual void _a120_53() = 0;
	virtual void _a120_54() = 0;
	virtual void _a120_55() = 0;
	virtual void _a120_56() = 0;
	virtual void _a120_57() = 0;
	virtual void _a120_58() = 0;
	virtual void _a120_59() = 0;
	virtual void _a120_60() = 0;
	virtual void _a120_61() = 0;
	virtual void _a120_62() = 0;
	virtual void _a120_63() = 0;
	virtual void _a120_64() = 0;
	virtual void _a120_65() = 0;
	virtual void _a120_66() = 0;
	virtual void _a120_67() = 0;
	virtual void _a120_68() = 0;
	virtual void _a120_69() = 0;
	virtual void _a120_70() = 0;
	virtual void _a120_71() = 0;
	virtual void _a120_72() = 0;
	virtual void _a120_73() = 0;
	virtual void _a120_74() = 0;
	virtual void _a120_75() = 0;
	virtual void _a120_76() = 0;
	virtual const BfmeAudioSettings *getAudioSettings() = 0;
};

extern BfmeAudioVtblIndexed *TheAudio;

class OptionPreferences
{
public:
	Real getVolume(Int index);
};

// ?getVolume@OptionPreferences@@QAEMH@Z
Real OptionPreferences::getVolume(Int index)
{
	if (index < 0 || index >= 5)
		return 0.0f;

	CustomAsciiStringShim key;
	key.init(g_volumePreferenceKeys[index]);

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return ((BfmeAudioVtblIndexed *)TheAudio)->getAudioSettings()->m_defaultVolumes[index] * 100.0f;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	Real volume = (Real)atof(text);
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	return volume;
}
// ?TheAudio@@3PAVBfmeAudioVtblIndexed@@A: the global at VA 0xdfe6e8 is ?TheAudio@@3PAVAudioManager@@A.
#pragma comment(linker, "/alternatename:?TheAudio@@3PAVBfmeAudioVtblIndexed@@A=?TheAudio@@3PAVAudioManager@@A")
