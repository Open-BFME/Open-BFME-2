// ?rva000A3E4F@Rva000A3E4F@@QAEXHPAVWinInstanceData@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva000A3E4F@Rva000A3E4F@@QAEXHPAVWinInstanceData@@@Z, 0x000A3E4F, 274
// Evidence: callers 0x000A3F61/472 and 0x000A4139/495 (Rva000A3F61Draw/
// Rva000A4139Draw free helpers taking GameWindow+WinInstanceData); all
// winGet callees rowed in GameWindow_winGetScreenPosition.cpp and
// GameWindowStatusUserData.cpp; interface virtuals called through the
// WinInstanceData +0x19c pointer at slots +0xc/+0x18/+0x1c/+0x28/+0x38/+0x3c.

class GameFont;
class WinInstanceData;

class GameWindow
{
public:
	int winGetScreenPosition(int *a, int *b);
	int winGetSize(int *a, int *b);
	unsigned int winGetStatus();
	int winGetDisabledTextColor();
	int winGetDisabledTextBorderColor();
	int winGetHiliteTextColor();
	int winGetHiliteTextBorderColor();
	int winGetEnabledTextColor();
	int winGetEnabledTextBorderColor();
	GameFont *winGetFont();
};

class WinTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int HasContent();
	virtual void v4();
	virtual void v5();
	virtual void SetFont(GameFont *f);
	virtual GameFont *GetFontRelated();
	virtual void v8();
	virtual void v9();
	virtual void F10(int textColor, int borderColor);
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void DrawAt(int x, int y, int w, int h);
	virtual void Measure(int *a, int *b);
};

class WinInstanceData
{
public:
	char m_pad00[8];
	unsigned char m_flags08;
	char m_pad09[0x19c - 9];
	WinTextInterface *m_iface19c;
};

class Rva000A3E4F
{
public:
	static void __fastcall Draw(GameWindow *window, WinInstanceData *data);
};

// ?Rva000A3E4FDraw@@YIXPAVGameWindow@@PAVWinInstanceData@@@Z present-unmatched
void __fastcall Rva000A3E4F::Draw(GameWindow *window, WinInstanceData *data)
{
	WinTextInterface *iface = data->m_iface19c;
	if (iface == 0)
		return;
	if (!iface->HasContent())
		return;
	int scrX;
	int scrY;
	window->winGetScreenPosition(&scrX, &scrY);
	int sizeX;
	int sizeY;
	window->winGetSize(&sizeX, &sizeY);
	int measX;
	int measY;
	unsigned int status = window->winGetStatus();
	int textColor;
	int borderColor;
	if ((status & 8) == 0) {
		textColor = window->winGetDisabledTextColor();
		borderColor = window->winGetDisabledTextBorderColor();
	} else if ((data->m_flags08 & 2) != 0) {
		textColor = window->winGetHiliteTextColor();
		borderColor = window->winGetHiliteTextBorderColor();
	} else {
		textColor = window->winGetEnabledTextColor();
		borderColor = window->winGetEnabledTextBorderColor();
	}
	if (iface->GetFontRelated() != window->winGetFont())
		iface->SetFont(window->winGetFont());
	iface->Measure(&measX, &measY);
	int halfX = measX / 2;
	int halfY = measY / 2;
	int posX = sizeX / 2 - halfX + scrX;
	int posY = sizeY / 2 - halfY + scrY;
	iface->F10(textColor, borderColor);
	iface->DrawAt(posX, posY, 1, 1);
}
