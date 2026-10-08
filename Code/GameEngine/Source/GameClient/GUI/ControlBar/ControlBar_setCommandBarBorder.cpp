// cl: /O1 /DNDEBUG /MD
// ?setCommandBarBorder@ControlBar@@QAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z
// @0x0031ABD9 96B: Zero Hour's ControlBar::setCommandBarBorder
// (ControlBar.cpp). The border colors sit at +0x218 (build), +0x21C (action),
// +0x220 (upgrade) and +0x224 (system) as in Zero Hour's member order; BFME 2
// adds a fifth border type with its color at +0x228. Anything else clears the
// border (GAME_COLOR_UNDEFINED, not drawn).

typedef int Color;
typedef bool Bool;
enum { GAME_COLOR_UNDEFINED = 0x00FFFFFF };

class Image;
class GameWindow
{
public:
	int winHide(Bool hide);
	int winSetEnabledImage(int index, const Image *image);
	unsigned int winSetStatus(unsigned int status);
	unsigned int winClearStatus(unsigned int status);
};
enum { WIN_STATUS_IMAGE = 0x80 };
enum { MAX_UPGRADE_CAMEO_UPGRADES = 5 };
void GadgetButtonSetBorder(GameWindow *g, unsigned int color, Bool drawBorder = 1);

enum CommandButtonMappedBorderType
{
	COMMAND_BUTTON_BORDER_NONE,
	COMMAND_BUTTON_BORDER_BUILD,
	COMMAND_BUTTON_BORDER_UPGRADE,
	COMMAND_BUTTON_BORDER_ACTION,
	COMMAND_BUTTON_BORDER_SYSTEM,
	COMMAND_BUTTON_BORDER_BFME5
};

class ControlBar
{
public:
	void setCommandBarBorder(GameWindow *button, CommandButtonMappedBorderType type);
	void setPortraitByImage(const Image *image);

private:
	unsigned char m_pad000[0x84];
	GameWindow *m_rightHUDWindow;						// +0x84
	GameWindow *m_rightHUDCameoWindow;					// +0x88
	GameWindow *m_rightHUDUpgradeCameos[MAX_UPGRADE_CAMEO_UPGRADES];	// +0x8C
	GameWindow *m_rightHUDUnitSelectParent;				// +0xA0
	unsigned char m_pad0A4[0x218 - 0xA4];
	Color m_commandButtonBorderBuildColor;		// +0x218
	Color m_commandButtonBorderActionColor;		// +0x21C
	Color m_commandButtonBorderUpgradeColor;	// +0x220
	Color m_commandButtonBorderSystemColor;		// +0x224
	Color m_commandButtonBorderBfme5Color;		// +0x228
};

void ControlBar::setCommandBarBorder(GameWindow *button, CommandButtonMappedBorderType type)
{
	if (!button)
		return;

	switch (type)
	{
		case COMMAND_BUTTON_BORDER_BUILD:
			GadgetButtonSetBorder(button, m_commandButtonBorderBuildColor);
			break;
		case COMMAND_BUTTON_BORDER_UPGRADE:
			GadgetButtonSetBorder(button, m_commandButtonBorderUpgradeColor);
			break;
		case COMMAND_BUTTON_BORDER_ACTION:
			GadgetButtonSetBorder(button, m_commandButtonBorderActionColor);
			break;
		case COMMAND_BUTTON_BORDER_SYSTEM:
			GadgetButtonSetBorder(button, m_commandButtonBorderSystemColor);
			break;
		case COMMAND_BUTTON_BORDER_BFME5:
			GadgetButtonSetBorder(button, m_commandButtonBorderBfme5Color);
			break;
		default:
			GadgetButtonSetBorder(button, GAME_COLOR_UNDEFINED, 0);
			break;
	}
}

// ?setPortraitByImage@ControlBar@@QAEXPBVImage@@@Z @0x0031AC4F 166B: Zero
// Hour's ControlBar::setPortraitByImage unchanged, over the right HUD
// windows at +0x84 (window), +0x88 (cameo), +0x8C (five upgrade cameos) and
// +0xA0 (unit select parent).
void ControlBar::setPortraitByImage(const Image *image)
{
	if (image)
	{
		m_rightHUDUnitSelectParent->winHide(false);
		m_rightHUDCameoWindow->winSetEnabledImage(0, image);
		m_rightHUDWindow->winClearStatus(WIN_STATUS_IMAGE);
		m_rightHUDCameoWindow->winSetStatus(WIN_STATUS_IMAGE);
		for (int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
			m_rightHUDUpgradeCameos[i]->winHide(true);
	}
	else
	{
		m_rightHUDWindow->winSetStatus(WIN_STATUS_IMAGE);
		m_rightHUDCameoWindow->winClearStatus(WIN_STATUS_IMAGE);
		m_rightHUDUnitSelectParent->winHide(true);
		for (int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
			m_rightHUDUpgradeCameos[i]->winHide(true);
	}
}
