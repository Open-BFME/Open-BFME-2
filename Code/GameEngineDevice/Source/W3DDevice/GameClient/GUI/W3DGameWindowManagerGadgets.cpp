// cl: /O1 /G7 /DNDEBUG /MD /ICode/GameEngine/Source/GameClient/GUI
//
// Device-side gadget factory overrides in the window manager vtable at VA
// 0x00BC7C90 (scalar deleting dtor ??_GRva008FCA3 in slot 0). Each one picks one
// of two rowed device factories by status bit 0x80 of the create record,
// stores it at record+0x18 and forwards the call unchanged to the shared
// gadget factory (GameWindowManager_RecordFactories.cpp). This is Zero Hour's
// W3DGameWindowManager split: the image/non-image draw-function choice made
// before GameWindowManager::gogoGadget*; in BFME2 the stored callbacks are the
// 58-byte new+ctor factories. Class and method names stay address derived.

#include "GameWindowManagerRecordView.h"

class Rva000A4969;
class Rva000A4916;
class Rva000A08D9;
class Rva000A0891;
class Rva000A43A4;
class Rva000A435C;
class Rva000A0D3A;
class Rva000A0CE7;
class Rva000A3E2B;
class Rva000A3DE3;
class Rva000A334F;
class Rva000A3307;
Rva000A4969 *__stdcall Rva0008F78FCreate(void *context);
Rva000A4916 *__stdcall Rva0008F755Create(void *context);
Rva000A08D9 *__stdcall Rva0008F71BCreate(void *context);
Rva000A0891 *__stdcall Rva0008F6E1Create(void *context);
Rva000A43A4 *__stdcall Rva0008F877Create(void *context);
Rva000A435C *__stdcall Rva0008F83DCreate(void *context);
Rva000A0D3A *__stdcall Rva0008FB2FCreate(void *context);
Rva000A0CE7 *__stdcall Rva0008FAF5Create(void *context);
Rva000A3E2B *__stdcall Rva0008F803Create(void *context);
Rva000A3DE3 *__stdcall Rva0008F7C9Create(void *context);
Rva000A334F *__stdcall Rva0008F8EBCreate(void *context);
Rva000A3307 *__stdcall Rva0008F8B1Create(void *context);
class Rva0009FDBD;
class Rva0009FD78;
Rva0009FDBD *__stdcall Rva0008F95FCreate(void *context);
Rva0009FD78 *__stdcall Rva0008F925Create(void *context);
class Rva000A217F;
class Rva000A2137;
Rva000A217F *__stdcall Rva0008FABBCreate(void *context);
Rva000A2137 *__stdcall Rva0008FA81Create(void *context);

// The shared entry and combo box factories are rowed under the base manager's name
// (GameWindowManager_gogoGadgetTextEntry.cpp, _gogoGadgetComboBox.cpp); only
// their direct calls are used.
typedef struct _EntryData EntryData;
typedef struct _ComboBoxData ComboBoxData;
class GameWindowManager
{
public:
	virtual GameWindow *gogoGadgetTextEntry(GadgetCreateView *view, EntryData *entryData, GameFont *defaultFont, bool defaultVisual);
	virtual GameWindow *gogoGadgetComboBox(GadgetCreateView *view, ComboBoxData *comboBoxDataTemplate, GameFont *defaultFont, bool defaultVisual);
};

enum { GADGET_CREATE_IMAGE = 0x80 };

class Rva008FCA3 : public TabWindowManagerView
{
public:
	GameWindow *rva0008FCE3(GadgetCreateView *view, GameFont *font, bool flag);
	GameWindow *rva0008FD0E(GadgetCreateView *view, StaticTextDataView *data, GameFont *font, bool flag);
	GameWindow *rva0008FD3D(GadgetCreateView *view, GameFont *font, bool flag);
	GameWindow *rva0008FD68(GadgetCreateView *view, RadioButtonDataView *data, GameFont *font, bool flag);
	GameWindow *rva0008FD97(GadgetCreateView *view, TabControlDataView *data, GameFont *font, bool flag);
	GameWindow *rva0008FE84(GadgetCreateView *view, GameFont *font, bool flag);
	GameWindow *rva0008FEAF(GadgetCreateView *view, EntryData *data, GameFont *font, bool flag);
	GameWindow *rva0008FEDE(GadgetCreateView *view, ComboBoxData *data, GameFont *font, bool flag);
};

// vtable 0x00BC7C90 slot 19
GameWindow *Rva008FCA3::rva0008FCE3(GadgetCreateView *view, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F78FCreate;
	else
		view->unknown24 = (void *)Rva0008F755Create;
	return gogoGadgetPushButton(view, font, flag);
}

// vtable 0x00BC7C90 slot 27
GameWindow *Rva008FCA3::rva0008FD0E(GadgetCreateView *view, StaticTextDataView *data, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F71BCreate;
	else
		view->unknown24 = (void *)Rva0008F6E1Create;
	return gogoGadgetStaticText(view, data, font, flag);
}

// vtable 0x00BC7C90 slot 21
GameWindow *Rva008FCA3::rva0008FD3D(GadgetCreateView *view, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F877Create;
	else
		view->unknown24 = (void *)Rva0008F83DCreate;
	return gogoGadgetCheckBox(view, font, flag);
}

// vtable 0x00BC7C90 slot 22
GameWindow *Rva008FCA3::rva0008FD68(GadgetCreateView *view, RadioButtonDataView *data, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F803Create;
	else
		view->unknown24 = (void *)Rva0008F7C9Create;
	return gogoGadgetRadioButton(view, data, font, flag);
}

// vtable 0x00BC7C90 slot 23
GameWindow *Rva008FCA3::rva0008FD97(GadgetCreateView *view, TabControlDataView *data, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F8EBCreate;
	else
		view->unknown24 = (void *)Rva0008F8B1Create;
	return gogoGadgetTabControl(view, data, font, flag);
}

// vtable 0x00BC7C90 slot 26
GameWindow *Rva008FCA3::rva0008FE84(GadgetCreateView *view, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008FB2FCreate;
	else
		view->unknown24 = (void *)Rva0008FAF5Create;
	return gogoGadgetProgressBar(view, font, flag);
}

// vtable 0x00BC7C90 slot 28
GameWindow *Rva008FCA3::rva0008FEAF(GadgetCreateView *view, EntryData *data, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008F95FCreate;
	else
		view->unknown24 = (void *)Rva0008F925Create;
	return ((GameWindowManager *)this)->GameWindowManager::gogoGadgetTextEntry(view, data, font, flag);
}

// vtable 0x00BC7C90 slot 29
GameWindow *Rva008FCA3::rva0008FEDE(GadgetCreateView *view, ComboBoxData *data, GameFont *font, bool flag)
{
	if (view->status & GADGET_CREATE_IMAGE)
		view->unknown24 = (void *)Rva0008FABBCreate;
	else
		view->unknown24 = (void *)Rva0008FA81Create;
	return ((GameWindowManager *)this)->GameWindowManager::gogoGadgetComboBox(view, data, font, flag);
}
