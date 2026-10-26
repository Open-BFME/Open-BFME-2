// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?DoXfer@AIUpgrade@@UAEXPAVXfer@@PAX@Z @0x005974CC 244B: slot12 xfer override pruning via AsciiString and command buttons; vtable 0x00870BD0 caller 0x005972B3
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "GameLogicObjectLookupView.h"

class Object
{
public:
	const AsciiString *rva00290E67() const;
};


extern GameLogic *TheGameLogic;

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *s);
};

class CommandButton
{
public:
	char m_pad00[0x10];
	AsciiString m_10;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

#include "AIXferTypes.h"
#include "../../Include/Common/BfmeXfer.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void Rva0055AED6(Xfer *x, void *p);
protected:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class AIUpgrade : public Rva0055B0CC
{
public:
	virtual void DoXfer(Xfer *x, void *p);
private:
	int m_2C;
	CommandButton *m_30;
};

struct TwoBytes
{
	bool a;
	bool b;
};

void AIUpgrade::DoXfer(Xfer *xfer, void *p)
{
	TwoBytes t;
	t.a = true;
	t.b = true;
	*xfer == *reinterpret_cast<Xfer::Version *>(&t);
	Rva0055B0CC::Rva0055AED6(xfer, p);
	*xfer == m_2C;
	const AsciiString *src;
	if (m_30 != 0)
		src = &m_30->m_10;
	else
		src = &AsciiString::TheEmptyString;
	AsciiString tmp(*src);
	*xfer == tmp;
	if (!xfer->IsLoading())
		return;
	_ReadWriteBarrier();
	if (((const StringBase<char> *)&tmp)->compare(*(const StringBase<char> *)&AsciiString::TheEmptyString) == 0)
		return;
	Object *obj = TheGameLogic->findObjectByID(m_08);
	if (obj == 0)
		return;
	const AsciiString *name = obj->rva00290E67();
	void *world = ((Rva0031D5F8 *)((BfmeWorldRV *)TheControlBar))->rva0031D5F8(name);
	for (int i = 0; i < 0x20; ++i)
	{
		if (m_30 != 0)
			break;
		const CommandButton *commandButton = ((CommandSet *)world)->getCommandButton(i);
		if (commandButton != 0)
		{
			if (((const StringBase<char> *)&commandButton->m_10)->compare(*(const StringBase<char> *)&tmp) == 0)
			{
				m_30 = (CommandButton *)commandButton;
			}
		}
	}
}
