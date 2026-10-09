// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?ShowSelectAllHeroesBttn@Impl@InGameHeroSelectInterface@@QAEXXZ
// retail 0x00525633..0x00525783 (336 bytes).
#include "ascii_string.h"

class CommandButton
{
public:
	const AsciiString &rva0035B1E9() const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct HotKeyActionCountView
{
	void *m_vtable;
	int m_references;
};

struct TreeHintRef00217D4C
{
	void *m_node;
	TreeHintRef00217D4C(void *node) : m_node(node)
	{
		if (node)
			++((HotKeyActionCountView *)node)->m_references;
	}
	~TreeHintRef00217D4C()
	{
		if (m_node)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_node);
	}
};

struct Rva00359302Result
{
	Rva00359302Result(void *node, bool alternate) : m_node(node), m_alt(alternate) {}
	void *m_node;
	bool m_alt;
};

class HotKeyManager
{
public:
	AsciiString rva00358CCD(const AsciiString &name);
	Rva00359302Result addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool flag);
};

class Rva00E01E28Owner;
extern Rva00E01E28Owner *g_00E01E28;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

class InGameHeroSelectInterface
{
public:
	class Impl;
};

// Reference-counted hotkey action (vtable 0x00867E60: shared scalar deleting
// destructor, two shared predicates, the select-all execute at 0x00526342).
class HotKeyAction
{
public:
	HotKeyAction() : m_references(0) {}
	virtual ~HotKeyAction();
	virtual bool slot04(int);
	virtual bool slot08(int);
	virtual bool execute(int) = 0;

	int m_references;
};

class SelectAllHeroesHotKeyAction : public HotKeyAction
{
public:
	SelectAllHeroesHotKeyAction(InGameHeroSelectInterface::Impl *owner) : m_owner(owner) {}
	virtual bool execute(int);

	InGameHeroSelectInterface::Impl *m_owner;
};

class InGameHeroSelectInterface::Impl
{
public:
	void ShowSelectAllHeroesBttn();

private:
	void *m_00;
	void *m_04;
	void *m_level08;						// +0x08
	AsciiString m_prefix0C;					// +0x0C
	unsigned char m_pad10[0x45 - 0x10];
	bool m_selectAllHeroesShown;			// +0x45
	unsigned char m_pad46[0x1C8 - 0x46];
	Rva00359302Result m_selectAllHotKey;	// +0x1C8
	unsigned char m_pad1D0[0x1D8 - 0x1D0];
	bool m_selectAllHotKeyAdded;			// +0x1D8
};

void InGameHeroSelectInterface::Impl::ShowSelectAllHeroesBttn()
{
	if (m_selectAllHeroesShown)
		return;
	if (g_00E01E28)
	{
		static AsciiString s_buttonName("NonCommand_SelectAllHeroes");
		const CommandButton *button = TheControlBar->findCommandButton(s_buttonName);
		if (button)
		{
			AsciiString hotKey = ((HotKeyManager *)g_00E01E28)->rva00358CCD(button->rva0035B1E9());
			if (!hotKey.isEmpty())
			{
				TreeHintRef00217D4C action(new SelectAllHeroesHotKeyAction(this));
				m_selectAllHotKey = ((HotKeyManager *)g_00E01E28)->addHotKey(action, hotKey, true);
				m_selectAllHotKeyAdded = true;
			}
		}
	}
	Rva005FB5E6AptCall(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager, m_level08,
		m_prefix0C.str(), "SetSelectAllHeroesButtonState", "_up");
	m_selectAllHeroesShown = true;
}
