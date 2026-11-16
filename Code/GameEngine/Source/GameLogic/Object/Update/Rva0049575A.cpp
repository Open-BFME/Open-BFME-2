// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0049575A@Rva0049575A@@QAEXPBVAsciiString@@@Z 167B @0x0049575A: hunt update via ascii plus world lookup plus command buttons plus wake.
// Evidence: retail StringBase set at plus0x20 plus Object rva00290E67 plus g_bfmeWorldRV plus Rva0031D5F8 lookup plus getCommandButton pin plus StringBase isEmpty compare plus aiIdle plus wake. Caller at 0x003C3DE2.
#include "ascii_string.h"

class Object
{
public:
	virtual void s00() = 0;
	const AsciiString *rva00290E67() const;
	char m_pad04[0x258 - 4];
	void *m_258;
};

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../../../Include/Common/Rva0031D5F8.h"

class CommandButton;
#include "../../../../Include/GameClient/CommandSet.h"

enum CommandSourceType
{
	CST_0 = 0,
	CST_1 = 1,
	CST_2 = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

enum UpdateSleepTime
{
	UST_0 = 0,
	UST_1 = 1
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class Rva0049575A : public UpdateModule
{
public:
	void rva0049575A(const AsciiString *name);
private:
	AsciiString m_20;
	const CommandButton *m_24;
};

void Rva0049575A::rva0049575A(const AsciiString *name)
{
	Object *obj = m_object;
	((StringBase<char> *)&m_20)->set(*(const StringBase<char> *)name);
	m_24 = 0;
	const AsciiString *asciiString = obj->rva00290E67();
	void *p = ((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(asciiString);
	CommandSet *cmdSet = (CommandSet *)p;
	if (cmdSet != 0)
	{
		*(int *)&name = 0;
		for (*(int *)&name = 0; *(int *)&name < 0x20; ++*(int *)&name)
		{
			const CommandButton *commandButton = cmdSet->getCommandButton(*(int *)&name);
			m_24 = commandButton;
			if (commandButton == 0)
			{
				m_24 = 0;
				continue;
			}
			const StringBase<char> *bs = (const StringBase<char> *)((char *)commandButton + 0x10);
			if (bs->isEmpty())
			{
				m_24 = 0;
				continue;
			}
			if (bs->compare(*(const StringBase<char> *)&m_20) != 0)
			{
				m_24 = 0;
				continue;
			}
			break;
		}
	}
	if (m_24 == 0)
		return;
	void *mid = obj->m_258;
	if (mid == 0)
		return;
	((AICommandInterface *)((char *)mid + 0x20))->aiIdle(CST_2);
	update();
	setWakeFrame(obj, UST_1);
}
