// cl: /DNDEBUG /MD
// ?setSelectable@Drawable@@QAEX_N@Z 0x00271700 69B
// Drawable::setSelectable transferred from BFME1 donor
// reference/open-bfme-1/game/GameEngine/Source/GameClient/Drawable.cpp:4436
// (void Drawable::setSelectable(Bool selectable) with TheInGameUI->deselectDrawable
// preamble plus draw-module broadcast via getObjectDrawInterface).
// Evidence: caller Object::setSelectable 0x0028B76D (pin ?setSelectable@Object@@QAEX_N@Z)
// stores +0x434 then calls this via Drawable+0x84; same +0x14C/0xA8 walk as landed
// Drawable_rva00270FAC 0x00270FAC and Drawable_rva002724FD 0x002724FD; TheInGameUI at
// VA 0x00DFEDF0 slot 0x10C (deselectDrawable; BFME1 slot 0xE4); inner slot 0x60
// (setSelectable; BFME1 slot 0x5C).
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class Drawable;

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void deselectDrawable(Drawable *draw);
};

extern InGameUI *TheInGameUI;

class Object
{
public:
	bool isSelectable() const;
};


void Drawable::setSelectable(bool selectable)
{
	if (!selectable)
		TheInGameUI->deselectDrawable(this);
	DrawModule **modules = *reinterpret_cast<DrawModule ***>((unsigned char *)this + 0x14c);
	for (DrawModule **dm = modules; *dm; ++dm) {
		ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->setSelectable(selectable);
	}
}

int Drawable::rva00271745() const
{
	if (m_object != 0) {
		if (m_object->isSelectable() != 0)
			return 1;
	}
	return 0;
}
