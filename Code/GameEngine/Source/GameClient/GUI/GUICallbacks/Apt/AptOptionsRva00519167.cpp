// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common
//
// ?rva00519167@AptOptions@@UAEHHII@Z
// retail 0x00519167..0x005194F5 (911 bytes) thiscall RET 0xC.
//
// The options screen's Apt window-message handler: slot 2 of the AptOptions
// vftable (absolute reference 0x008666A0, beside the base handler's slot at
// 0x008659F0). It first runs the base _bfme_AptGameWindow handler
// 0x0051274F, then answers messages 1, 2 and 0x17 and the gadget messages
// of Zero Hour's OptionsMenuSystem (OptionsMenu.cpp): the detail-preset
// combo (+0x2B0; item 5 invokes "ShowAdvancedSettings", any other preset
// warns through 0x00518FEA and refreshes through 0x005183FA), the
// resolution combo (+0x2AC; "APT:WarnHighGraphicResolution" through the
// pinned 0x00518B05 above +0x30C and +0x304), the EAX check box (+0x2D4;
// "DoOpenPopMessage"/"Eax3NotSupported" and unchecking when the audio slot
// at +0x184 refuses), the gamma slider (+0x2F4; Zero Hour's gamma formula
// into TheDisplay slot 25, setGamma) and the five volume sliders (+0x2DC;
// audio volume slot +0xE8, then the preview sound: misc-audio entry +0xA8
// per slider through the 136-byte event constructor 0x002D97D6, suppressed
// for slider 2 in a multiplayer game or with +0x280 set). Message 0x4010
// stops the preview and falls into the base result. The WorldBuilder twin
// 0x013D6C20 has the same shape with its fields 4 lower from +0x2A8.
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "GameLogicObjectLookupView.h"

class GameWindow;

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
bool GadgetCheckBoxIsChecked(GameWindow *checkBox);
void GadgetCheckBoxSetChecked(GameWindow *checkBox, bool isChecked);

class _bfme_AptGameWindow
{
public:
	int rva0051274F(int message, unsigned int data1, unsigned int data2);
};

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The rowed 0x005183FA, called on the screen.
class Rva005183A0
{
public:
	void rva005183FA();
};

// The audio manager's misc-audio record: one sound per volume slider at +0xA8.
struct AptOptionsMiscAudio
{
	unsigned char m_pad000[0xA8];
	OpaqueRefElement4 m_sliderSounds[5]; // +0xA8
};

template <int N> class AptOptionsAudioSlots : public AptOptionsAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AptOptionsAudioSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class AudioManager : public AptOptionsAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);			// +0x64
	virtual void slot26();
	virtual void slot27();
	virtual void removeAudioEvent(int handle);									// +0x70
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48();
	virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual bool isCurrentlyPlaying(int handle);								// +0xD0
	virtual void slot53(); virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57();
	virtual void setVolume(int which, float volume);							// +0xE8
	virtual void slot59(); virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70();
	virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual AptOptionsMiscAudio *getMiscAudio();								// +0x138
	virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82();
	virtual void slot83(); virtual void slot84(); virtual void slot85(); virtual void slot86();
	virtual void slot87(); virtual void slot88(); virtual void slot89(); virtual void slot90();
	virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94();
	virtual void slot95(); virtual void slot96();
	virtual bool setUseEAX(bool use);											// +0x184
};

extern AudioManager *TheAudio;

class Display : public AptOptionsAudioSlots<25>
{
public:
	virtual void setGamma(float gamma, float bright, float contrast, bool calibrate);	// +0x64
};

extern Display *TheDisplay;

extern GameLogic *TheGameLogic;

class AptOptions
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual int rva00519167(int message, unsigned int data1, unsigned int data2);

	void rva00518FEA(int query, int kind);
	// Unrowed 0x00518B05 (a warning prompt), pinned by address.
	void rva00518B05(const AsciiString &text, int kind);

private:
	unsigned char m_pad004[0x274 - 0x04];
	void *m_aptOwner; // +0x274
	unsigned char m_pad278[0x280 - 0x278];
	bool m_280; // +0x280
	unsigned char m_pad281[0x2AC - 0x281];
	GameWindow *m_resolutionCombo; // +0x2AC
	GameWindow *m_detailCombo; // +0x2B0
	unsigned char m_pad2B4[0x2D4 - 0x2B4];
	GameWindow *m_eaxCheckBox; // +0x2D4
	unsigned char m_pad2D8[0x2DC - 0x2D8];
	GameWindow *m_volumeSliders[5]; // +0x2DC
	unsigned char m_pad2F0[0x2F4 - 0x2F0];
	GameWindow *m_gammaSlider; // +0x2F4
	unsigned char m_pad2F8[0x2FC - 0x2F8];
	int m_previewHandle; // +0x2FC
	int m_previewSlider; // +0x300
	int m_304; // +0x304
	unsigned char m_pad308[0x30C - 0x308];
	int m_resolution; // +0x30C
	int m_preset; // +0x310
};

int AptOptions::rva00519167(int message, unsigned int data1, unsigned int data2)
{
	int result = ((_bfme_AptGameWindow *)this)->rva0051274F(message, data1, data2);

	switch (message)
	{
	case 1:
		break;
	case 2:
		break;
	case 0x17:
		break;

	case 0x4026:
	{
		GameWindow *control = (GameWindow *)data1;
		if (control == m_detailCombo)
		{
			int index;
			GadgetComboBoxGetSelectedPos(m_detailCombo, &index);
			int preset = (int)GadgetComboBoxGetItemData(m_detailCombo, index);
			if (preset == 5)
			{
				TheRva00222A8BTarget->invoke(m_aptOwner, "ShowAdvancedSettings", 0, 0, 0, 0, 0, 0);
				break;
			}
			rva00518FEA(preset, 1);
			m_preset = preset;
			((Rva005183A0 *)this)->rva005183FA();
		}
		else if (control == m_resolutionCombo)
		{
			int index;
			GadgetComboBoxGetSelectedPos(m_resolutionCombo, &index);
			if (index > m_resolution && index > m_304)
				rva00518B05(AsciiString("APT:WarnHighGraphicResolution"), 0);
			m_resolution = index;
		}
		break;
	}

	case 0x4008:
	{
		GameWindow *control = (GameWindow *)data1;
		if (control == m_eaxCheckBox)
		{
			bool checked = GadgetCheckBoxIsChecked(m_eaxCheckBox);
			if (checked)
			{
				bool ok = TheAudio->setUseEAX(checked);
				if (!ok)
				{
					TheRva00222A8BTarget->invoke(m_aptOwner, "DoOpenPopMessage", 1, "Eax3NotSupported", 0, 0, 0, 0);
					GadgetCheckBoxSetChecked(m_eaxCheckBox, false);
				}
			}
			else
				TheAudio->setUseEAX(false);
		}
		break;
	}

	case 0x400C:
	{
		GameWindow *control = (GameWindow *)data1;
		int val = (int)data2;
		if (control == m_gammaSlider)
		{
			if (val != -1)
			{
				float gammaval = 1.0f;
				if (val < 50)
				{
					if (val <= 0)
						gammaval = 0.6f;
					else
						gammaval = 1.0f - (0.4f) * (float)(50 - val) / 50.0f;
				}
				else if (val > 50)
					gammaval = 1.0f + (1.0f) * (float)(val - 50) / 50.0f;
				TheDisplay->setGamma(gammaval, 0.0f, 1.0f, false);
			}
		}
		else
		{
			int slider = 5;
			for (int i = 0; i < 5; i++)
			{
				if (control == m_volumeSliders[i])
				{
					slider = i;
					break;
				}
			}
			if (slider != 5 && val != -1)
			{
				TheAudio->setVolume(slider, (float)val / 100.0f);
				if (m_previewSlider != slider)
				{
					TheAudio->removeAudioEvent(m_previewHandle);
					m_previewHandle = 0;
					m_previewSlider = slider;
				}
				if (!TheAudio->isCurrentlyPlaying(m_previewHandle))
				{
					m_previewHandle = 0;
					if (slider != 2 || (TheGameLogic && !TheGameLogic->isInMultiplayerGame() && !m_280))
					{
						BfmeAudioEventPrefix136 preview(TheAudio->getMiscAudio()->m_sliderSounds[slider], 2);
						m_previewHandle = TheAudio->addAudioEvent(&preview);
					}
				}
			}
		}
		break;
	}

	case 0x4010:
		if (m_previewHandle && m_previewSlider != 1)
		{
			TheAudio->removeAudioEvent(m_previewHandle);
			m_previewHandle = 0;
			m_previewSlider = 5;
		}
		// fall through
	default:
		return result;
	}
	return 1;
}
