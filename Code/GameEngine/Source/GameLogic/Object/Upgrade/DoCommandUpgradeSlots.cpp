// cl: /O1 /DNDEBUG /MD
//
// Two DoCommandUpgrade overrides on the upgrade-mux vtable 0x00C57B10 that its
// matched ctor 0x004B4C2E installs at +0x10, compiled with that subobject
// this. Each looks a command button up by a name from the module data in
// TheControlBar and has our Object do it. Names are by address.
//
// ?rva004B4C7B@DoCommandUpgrade@@UAEXXZ, retail 0x004B4C7B, 50 bytes: slot 8,
// the button named at module data +0x11C.
// ?rva004B4CAD@DoCommandUpgrade@@UAEXXZ, retail 0x004B4CAD, 50 bytes: slot 10,
// the button named at module data +0x118.

class AsciiString;
class CommandButton;

class Object
{
public:
	void doCommandButton(const CommandButton *button, int a2, int a3);
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

struct DoCommandUpgradeModuleData
{
	unsigned char m_pad000[0x118];
	unsigned char m_118[4]; // +0x118 (AsciiString)
	unsigned char m_11C[4]; // +0x11C (AsciiString)
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const DoCommandUpgradeModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };

class UpgradeMux
{
public:
	virtual void gap0() = 0; virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0;
	virtual void gap4() = 0; virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void rva004B4C7B() = 0;
	virtual void gap9() = 0;
	virtual void rva004B4CAD() = 0;
};

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public UpgradeMux
{
};

class DoCommandUpgrade : public UpgradeModule
{
public:
	virtual void rva004B4C7B();
	virtual void rva004B4CAD();
};

// ?rva004B4C7B@DoCommandUpgrade@@UAEXXZ @0x004B4C7B
void DoCommandUpgrade::rva004B4C7B()
{
	Object *obj = m_object;
	if (obj && m_moduleData)
	{
		const CommandButton *button = TheControlBar->findCommandButton(*(const AsciiString *)m_moduleData->m_11C);
		if (button)
			obj->doCommandButton(button, 0, 0);
	}
}

// ?rva004B4CAD@DoCommandUpgrade@@UAEXXZ @0x004B4CAD
void DoCommandUpgrade::rva004B4CAD()
{
	Object *obj = m_object;
	if (obj && m_moduleData)
	{
		const CommandButton *button = TheControlBar->findCommandButton(*(const AsciiString *)m_moduleData->m_118);
		if (button)
			obj->doCommandButton(button, 0, 0);
	}
}
