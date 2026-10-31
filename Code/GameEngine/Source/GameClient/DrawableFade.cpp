// cl: /DNDEBUG /MD
//
// ?fadeIn@Drawable@@QAEXI@Z @0x002707A8 82B, ?fadeOut@Drawable@@QAEXI@Z @0x00270756 82B.
// BFME2 Drawable fade pair transferred from BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/GameClient/Drawable.cpp
// (fadeIn sets 0.0F mode 1, fadeOut sets 1.0F mode 2, both clear elapsed and
// store frames plus start frame). Retail divergences all measured:
// - zero-frames guard (opaque no-fade for fadeIn, transparent no-fade for fadeOut)
// - start frame at +0x37C via holder at 0xDFE77C slot 0x7C (ScriptEngine_setFrame precedent)
// - 1.0F loads from shared literal 0xBBB8D8, 0.0F via xorps.
// Layout: opacity +0xB0, fadeMode +0x128, elapsed +0x12C, toFade +0x130 (contiguous
// fade triple proven by updater 0x0027566B), start frame +0x37C.
// Callers: 0x00265173 calls fadeOut then selectable(0) vs fadeIn then selectable(1)
// with LogicFrames 0xDBA4E4; 0x00275894 calls fadeIn when mode reaches 5;
// ObjectCreationList debris calls fadeIn/fadeOut with m_fadeFrames.


#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)

void Drawable::fadeIn(unsigned int frames)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	float opacity;
	if (frames == 0) {
		opacity = 1.0f;
		self->m_fadeMode &= frames;
	} else {
		opacity = 0.0f;
		self->m_fadeMode = 1;
	}
	self->m_timeElapsedFade = 0;
	self->m_explicitOpacity = opacity;
	self->m_timeToFade = frames;
	self->m_fadeStartFrame = TheRva00DFE77C->slot1F();
}

void Drawable::fadeOut(unsigned int frames)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	float opacity;
	if (frames == 0) {
		opacity = 0.0f;
		self->m_fadeMode &= frames;
	} else {
		opacity = 1.0f;
		self->m_fadeMode = 2;
	}
	self->m_timeElapsedFade = 0;
	self->m_explicitOpacity = opacity;
	self->m_timeToFade = frames;
	self->m_fadeStartFrame = TheRva00DFE77C->slot1F();
}
// @0x00272D77 (68B): third fade mode 5 setter; holder call with 1 then elapsed 0
// toFade a plus field +0x134 b plus start frame via holder slot1F. Caller 0x0045BEA0.
void Drawable::rva00272D77(unsigned int frames, unsigned int fadeInFrames)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	setDrawableHidden(true);
	self->m_timeElapsedFade = 0;
	self->m_timeToFade = frames;
	self->m_fadeMode = 5;
	self->m_134 = fadeInFrames;
	self->m_fadeStartFrame = TheRva00DFE77C->slot1F();
}
// @0x00272C9E (101B): opacity getter over draw modules at +0x14C via slots
// 0xC4/0xF0 with shared 1.0F literal 0xBBB8D8; returns B4*B0. Callers in
// 0x00070xxx 0x000D0091 0x000E459F 0x000E5406.
float Drawable::rva00272C9E(int key)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	float opacity = self->m_opacityB4;
	if (key != 0)
	{
		for (DrawModule **drawModule = ((DrawModule **)m_modules[0]); *drawModule; ++drawModule)
		{
			if ((*drawModule)->slotC4() == key)
			{
				if (!(*drawModule)->slotF0())
					opacity = 1.0f;
				break;
			}
		}
	}
	return opacity * self->m_explicitOpacity;
}
