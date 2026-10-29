// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// ?postProcessCommands@ControlBar@@QAEXXZ @0x0031AC39 22B: walk the command
// button list (+0x2C) calling the rowed image resolve 0x0035B77D on each
// button via its +0x18 next. Identity: ControlBar::init calls it right after
// the command-button parse (0x0031C863, the ZH order), and the INI reload
// notice calls it again (0x0031E850); body is ZH's
// ControlBar::postProcessCommands loop.
typedef bool Bool;
#include "subsystem_interface.h"
class CommandButton
{
public:
	void cacheButtonImage();
	CommandButton *friend_getNext() { return m_next; }
private:
	char m_pad00[0x18];
	CommandButton *m_next;	// +0x18
};

#include "ControlBarMemberTypes.h"
class ControlBar : public SubsystemInterface
{
public:
	void postProcessCommands(void);
private:
	char m_pad0C[0x2C - 0x0C];
	CommandButton *m_commandButtons;	// +0x2C
};

void ControlBar::postProcessCommands(void)
{
	for (CommandButton *button = m_commandButtons; button; button = button->friend_getNext())
		button->cacheButtonImage();
}
