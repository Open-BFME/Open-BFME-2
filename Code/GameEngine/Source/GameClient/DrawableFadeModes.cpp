// cl: /O1 /DNDEBUG /MD
//
// ?rva00272D03@Drawable@@QAEXI@Z @0x00272D03 58B and
// ?rva00272D3D@Drawable@@QAEXI@Z @0x00272D3D 58B: Drawable fade modes 4 and
// 3, the siblings just before the mode-5 setter 0x00272D77 (DrawableFade.cpp)
// with the same fade fields (mode +0x128, elapsed +0x12C, toFade +0x130,
// start frame +0x37C from the 0xDFE77C holder's slot 0x7C). Each first calls
// the 0x00271601 holder method, with 0 for mode 4 and 1 for mode 3. Built
// /O1 (retail clears elapsed with and-0), unlike DrawableFade.cpp's bodies.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class GameClient;
extern GameClient *TheGameClient;

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

void Drawable::rva00272D03(unsigned int frames)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	setDrawableHidden(false);
	self->m_timeElapsedFade = 0;
	self->m_fadeMode = 4;
	self->m_timeToFade = frames;
	self->m_fadeStartFrame = TheRva00DFE77C->slot1F();
}

void Drawable::rva00272D3D(unsigned int frames)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	setDrawableHidden(true);
	self->m_timeElapsedFade = 0;
	self->m_fadeMode = 3;
	self->m_timeToFade = frames;
	self->m_fadeStartFrame = TheRva00DFE77C->slot1F();
}
