// cl: /O1 /DNDEBUG /MD
//
// ?setLowControlBarConfig@ControlBar@@IAEXXZ retail 0x0031B134, 136 bytes.
// Zero Hour ControlBar::setLowControlBarConfig over the BFME 2 offsets:
// stage +0x24 = CONTROL_BAR_STAGE_LOW (2), default x +0x1C, CP_MASTER parent
// window +0x48; Display::getHeight is slot 17 (+0x44) and returns unsigned
// (retail adds 2^32 to a negative fild); View::setHeight is slot 16 (+0x40).
// BFME 2 truncates the 10% band to Int before subtracting it (one __ftol2,
// then an integer sub). setUpDownImages is the rowed ControlBar::rva0031AE13
// (tail call).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class DisplaySlots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
};

class Display : public DisplaySlots
{
public:
	virtual UnsignedInt getHeight(void); // slot 17
};

class ViewSlots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
};

class View : public ViewSlots
{
public:
	virtual void setHeight(Int height); // slot 16
};

extern Display *TheDisplay;
extern View *TheTacticalView;

class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
	Int winHide(Bool hide);
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT,
	CONTROL_BAR_STAGE_SQUISHED,
	CONTROL_BAR_STAGE_LOW,
	CONTROL_BAR_STAGE_HIDDEN
};

class ControlBar
{
public:
	void rva0031AE13(void); // setUpDownImages

protected:
	void setLowControlBarConfig(void);

private:
	unsigned char m_pad00[0x1C];
	ICoord2D m_defaultControlBarPosition;       // +0x1C
	ControlBarStages m_currentControlBarStage;  // +0x24
	unsigned char m_pad28[0x48 - 0x28];
	GameWindow *m_contextParentMaster;          // +0x48 (m_contextParent[CP_MASTER])
};

void ControlBar::setLowControlBarConfig(void)
{
	m_currentControlBarStage = CONTROL_BAR_STAGE_LOW;
	ICoord2D pos;
	pos.x = m_defaultControlBarPosition.x;
	Int band = (Int)(.1 * TheDisplay->getHeight());
	pos.y = TheDisplay->getHeight() - band;
	TheTacticalView->setHeight((Int)(TheDisplay->getHeight()));
	m_contextParentMaster->winSetPosition(pos.x, pos.y);
	m_contextParentMaster->winHide(false);
	rva0031AE13();
}
