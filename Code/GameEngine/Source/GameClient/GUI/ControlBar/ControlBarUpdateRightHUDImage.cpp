// cl: /DNDEBUG /MD

// ControlBar::updateRightHUDImage ported from the BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp).
// Retail 0x0031ACF5: m_rightHUDWindow sits at this+0x84 here; the call lands
// on the rowed ?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z (0x3143B9).
class Image;
class Object;

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);
};

class ControlBar
{
public:
	void updateRightHUDImage(const Image *image);
	void setPortraitByObject(Object *obj);

	unsigned char m_pad[0x84];
	GameWindow *m_rightHUDWindow;	///< retail this+0x84
};

// ?updateRightHUDImage@ControlBar@@QAEXPBVImage@@@Z
void ControlBar::updateRightHUDImage(const Image *image)
{
	if (!m_rightHUDWindow || !image)
		return;
	m_rightHUDWindow->winSetEnabledImage(0, image);
}

// BFME 2 leaves the portrait alone: ControlBar::setPortraitByObject is
// empty, the shared ret-4 body at 0x0047A69C (populateBeacon 0x0050DBE6
// calls it first, as Zero Hour's does).
void ControlBar::setPortraitByObject(Object *obj)
{
}
