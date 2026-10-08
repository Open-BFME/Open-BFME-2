// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00202244@Rva00DFE144Globals@@QAEXHPAVOptionPreferences@@@Z, retail
// 0x00202244..0x002022E9 (165 bytes, RET 8): a method of the object at
// 0x00DFE144 (TheGameLODManager, viewed as Rva00DFE144Globals, the spelling
// its caller AptOptions pinned). It writes the 0x4C-byte preset the first
// argument selects into nine OptionPreferences settings (rowed setSetting):
// the +0x00, +0x34, +0x04 and +0x10 words; 2 when the +0x14 flag is set, else
// the +0x15 flag; the +0x18 word; the +0x2C mode mapped 2 -> 0, 1 -> 1,
// anything else -> 2; and the +0x38 and +0x40 words.

class OptionPreferences
{
public:
	void setSetting(int index, int value);
};

struct Rva00202244Preset
{
	int m_00;
	int m_04;
	unsigned char m_pad08[0x10 - 0x08];
	int m_10;
	bool m_14;
	bool m_15;
	unsigned char m_pad16[0x18 - 0x16];
	int m_18;
	unsigned char m_pad1C[0x2C - 0x1C];
	int m_2C;
	unsigned char m_pad30[0x34 - 0x30];
	int m_34;
	int m_38;
	unsigned char m_pad3C[0x40 - 0x3C];
	int m_40;
	unsigned char m_pad44[0x4C - 0x44];
};

class Rva00DFE144Globals
{
public:
	void rva00202244(int preset, OptionPreferences *prefs);
private:
	Rva00202244Preset m_presets[1];
};

void Rva00DFE144Globals::rva00202244(int preset, OptionPreferences *prefs)
{
	const Rva00202244Preset &p = m_presets[preset];
	prefs->setSetting(0, p.m_00);
	prefs->setSetting(1, p.m_34);
	prefs->setSetting(2, p.m_04);
	prefs->setSetting(3, p.m_10);
	prefs->setSetting(4, p.m_14 ? 2 : (p.m_15 != 0));
	prefs->setSetting(5, p.m_18);
	prefs->setSetting(6, p.m_2C == 2 ? 0 : (p.m_2C == 1 ? 1 : 2));
	prefs->setSetting(7, p.m_38);
	prefs->setSetting(8, p.m_40);
}
