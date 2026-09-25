// cl: /O1 /Oy- /DNDEBUG /MD /Oi-

// MpGameSetup gadget initialization callback, retail 0x0043EB1D (420B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/MpGameSetupOnInitGadget.cpp
// (MpGameSetup::_bfme_onInitGadget, BFME1 0x00525AB0). BFME2 target evidence
// (all retail-measured): no GameType/MapType branches and no mapListReady
// gate; the MapList branch stores the window at +0x394 and applies five
// column widths {8, 2, 0x46, 10, 10}; the name parses via the msvcr71 sscanf
// import with "%d" into an unsigned index (rejected when != 1 or > 8); the
// leaf after the last marker selects Player (+0x2D4, plus listbox tooltip
// 0x83DF71), PlayerTemplate (+0x334), Team (+0x314), Color (+0x2F4 via the
// rowed list<int> const_iterator ctor), Handicap (+0x354) or Hero (+0x374);
// every taken branch falls into the hide tail (index >= 6 with the +0x7C
// flag set hides the window). The MpGameSetup screen exists in BFME2
// (MpGameSetup::InitGadgets dispatch names in .rdata); the method name is
// the BFME1 donor identity for this same role and gadget-name set.

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int flags));
	int winHide(bool hide);
};

typedef void (*GameWinTooltipFunc)(GameWindow *window, WinInstanceData *data, unsigned int flags);

void __cdecl GadgetComboBoxReset(GameWindow *window);
GameWindow *__cdecl GadgetComboBoxGetListBox(GameWindow *window);
void __cdecl GadgetListBoxSetColumnWidths(GameWindow *window, int count, int *widths);
const char *__cdecl bfmePathLeafAfterMarker(const char *path);

namespace _STL
{
	template <class _Tp> struct _List_node;
	template <class _Tp> struct _Const_traits;
	template <class _Tp, class _Traits> struct _List_iterator
	{
		_List_iterator(_List_node<_Tp> *node);

	private:
		void *m_node;
	};
	typedef _List_iterator<int, _Const_traits<int> > ListIntConstIterator;
}

class MpGameSetup
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad0[0x7c];
	int m_hideFlag;
	unsigned char m_pad1[0x2d4 - 0x80];
	GameWindow *m_player[8];
	_STL::ListIntConstIterator m_color[8];
	GameWindow *m_team[8];
	GameWindow *m_playerTemplate[8];
	GameWindow *m_handicap[8];
	GameWindow *m_hero[8];
	GameWindow *m_mapList;
};

// ?_bfme_onInitGadget@MpGameSetup@@QAEXPBDPAXPAVGameWindow@@@Z
void MpGameSetup::_bfme_onInitGadget(const char *name, void *, GameWindow *window)
{
	if (window == 0)
		return;

	if (strcmp(name, "MapList") == 0)
	{
		m_mapList = window;
		int widths[5] = { 8, 2, 0x46, 10, 10 };
		GadgetListBoxSetColumnWidths(window, 5, widths);
		return;
	}

	unsigned int index;
	if (sscanf(name, "%d", &index) != 1 || index > 8)
		return;

	const char *leaf = bfmePathLeafAfterMarker(name);
	if (strcmp(leaf, "Player") == 0)
	{
		GadgetComboBoxReset(window);
		m_player[index] = window;
		GadgetComboBoxGetListBox(window)->winSetTooltipFunc((GameWinTooltipFunc)0x83df71);
	}
	else if (strcmp(leaf, "PlayerTemplate") == 0)
	{
		GadgetComboBoxReset(window);
		m_playerTemplate[index] = window;
	}
	else if (strcmp(leaf, "Team") == 0)
	{
		GadgetComboBoxReset(window);
		m_team[index] = window;
	}
	else if (strcmp(leaf, "Color") == 0)
	{
		GadgetComboBoxReset(window);
		// Explicit constructor call (MSVC extension): placement new via
		// operator new always emits a null check under MSVC 7.1 (retail's
		// own stlport _Construct at 0x3FA3D3 keeps its test/je), while
		// retail here calls the iterator ctor directly with no check, so
		// the body reconstructs the color slot in place this way.
		m_color[index]._STL::ListIntConstIterator::ListIntConstIterator(
			(_STL::_List_node<int> *)window);
	}
	else if (strcmp(leaf, "Handicap") == 0)
	{
		GadgetComboBoxReset(window);
		m_handicap[index] = window;
	}
	else if (strcmp(leaf, "Hero") == 0)
	{
		GadgetComboBoxReset(window);
		m_hero[index] = window;
	}
	else
		return;

	if (index >= 6 && m_hideFlag == 1)
		window->winHide(true);
}
