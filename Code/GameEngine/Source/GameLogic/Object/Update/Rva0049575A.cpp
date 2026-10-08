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

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

class CommandButton;
class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

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

class UpdateModule
{
public:
	virtual void s00() = 0;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime t);
};

struct Virt0
{
	virtual void s00();
};

class Rva0049575A : public UpdateModule
{
public:
	void rva0049575A(const AsciiString *name);
private:
	void *m_4;
	Object *m_8;
	char m_pad0C[0x10 - 0x0C];
	Virt0 m_10;
	char m_pad14[0x20 - 0x14];
	AsciiString m_20;
	const CommandButton *m_24;
};

void Rva0049575A::rva0049575A(const AsciiString *name)
{
	Object *obj = m_8;
	((StringBase<char> *)&m_20)->set(*(const StringBase<char> *)name);
	m_24 = 0;
	const AsciiString *s = obj->rva00290E67();
	void *p = ((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(s);
	CommandSet *cmdSet = (CommandSet *)p;
	if (cmdSet != 0)
	{
		*(int *)&name = 0;
		for (*(int *)&name = 0; *(int *)&name < 0x20; ++*(int *)&name)
		{
			const CommandButton *b = cmdSet->getCommandButton(*(int *)&name);
			m_24 = b;
			if (b == 0)
			{
				m_24 = 0;
				continue;
			}
			const StringBase<char> *bs = (const StringBase<char> *)((char *)b + 0x10);
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
	m_10.s00();
	setWakeFrame(obj, UST_1);
}
