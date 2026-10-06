// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?PopulateLobbyComboBox@AptOnlineCustomMatch@@QAEXXZ @ 0x0059FD3A (241B).
// Combo-box population from GameSpy map: reset, iterate RB tree from slot 3,
// skip entries matching slot 8 or with m_f != 1, add Unicode text with color
// g_00DB91A0, set item data to m_a, select entry matching slot 12.
// Evidence: callees GadgetComboBoxReset/AddEntry/SetItemData/SetSelectedPos,
// AsciiUnicodePair copy 0x382444, BfmeMappedValueEBD dtor 0x38240F,
// StringBase wide copy 0x37050, RB increment 0x24250, TheGameSpyInfo slot 0xC.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class GameWindow;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide);

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *) throw();
};
}

struct AsciiUnicodePair
{
	AsciiString m_ascii;
	UnicodeString m_unicode;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
	AsciiUnicodePair(const AsciiUnicodePair &other);
};

struct MapNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_10;
	AsciiUnicodePair m_14;
};

struct MapHolder
{
	_STL::_Rb_tree_node_base *m_header;
};

class GameSpyInfoInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual MapHolder *s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual int s08();
	virtual void s09();
	virtual void s0A();
	virtual void s0B();
	virtual int s0C();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class G00E05FB4Provider
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual int f08();
};

extern G00E05FB4Provider *g_00E05FB4;
extern int g_00DB91A0;

class AptOnlineCustomMatch
{
public:
	void PopulateLobbyComboBox();
private:
	char m_pad[0x490];
	GameWindow *m_combo;
};

void AptOnlineCustomMatch::PopulateLobbyComboBox()
{
	GameWindow *combo = m_combo;
	if (combo == 0)
		return;
	GadgetComboBoxReset(combo);
	int selected = -1;
	_STL::_Rb_tree_node_base *node = TheGameSpyInfo->s03()->m_header->_M_left;
	while (node != TheGameSpyInfo->s03()->m_header)
	{
		{
			AsciiUnicodePair tmp(((MapNode *)node)->m_14);
			if (tmp.m_a != g_00E05FB4->f08())
			{
				if (tmp.m_f == 1)
				{
					int cur = TheGameSpyInfo->s0C();
					int pos;
					if (tmp.m_a == cur)
					{
						pos = GadgetComboBoxAddEntry(combo, tmp.m_unicode, g_00DB91A0);
						GadgetComboBoxSetItemData(combo, pos, (void *)tmp.m_a);
						selected = pos;
					}
					else
					{
						pos = GadgetComboBoxAddEntry(combo, tmp.m_unicode, g_00DB91A0);
						GadgetComboBoxSetItemData(combo, pos, (void *)tmp.m_a);
					}
				}
			}
		}
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	GadgetComboBoxSetSelectedPos(combo, selected, false);
}
