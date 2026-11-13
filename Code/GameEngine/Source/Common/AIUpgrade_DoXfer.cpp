// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?DoXfer@AIUpgrade@@UAEXPAVXfer@@PAX@Z @0x005974CC 244B: slot12 xfer override pruning via AsciiString and command buttons; vtable 0x00870BD0 caller 0x005972B3
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "GameLogicObjectLookupView.h"

class CommandButton;
#include "../GameLogic/Object/object.h"


extern GameLogic *TheGameLogic;

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../Include/Common/Rva0031D5F8.h"

#include "../../Include/GameClient/CommandButton.h"
#include "../../Include/GameClient/CommandSet.h"

#include "AIXferTypes.h"
#include "../../Include/Common/BfmeXfer.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void Rva0055AED6(Xfer *x, void *p);
	float m_04; // +0x04
	ObjectID m_builderID; // +0x08
	AsciiString m_0C; // +0x0C
	int m_remaining10; // +0x10
	char m_pad14[0x4];
	float m_18; // +0x18
	char m_pad1C[0x4];
	bool m_20; // +0x20
	bool m_21; // +0x21
	char m_pad22[0x2];
	ObjectID m_24; // +0x24
	bool m_28; // +0x28
	char m_pad29[0x3];
};

// Table 0x00870BD0 places getCostPerTick at slot 8, DoXfer at slot 12 and
// build at slot 15; the base slots between them are not recovered, so the
// declaration order states no slot positions.
class AIUpgrade : public Rva0055B0CC
{
public:
	AIUpgrade();
	virtual ~AIUpgrade();
	virtual float getCostPerTick(void *p);
	virtual void DoXfer(Xfer *x, void *p);
	virtual bool build(void *context);
	int rva005973D8();
	void rva005975C0();
	int m_2C; // +0x2C
	const CommandButton *m_commandButton; // +0x30
};

#include "../../Include/Common/TwoBytes.h"

void AIUpgrade::DoXfer(Xfer *xfer, void *p)
{
	TwoBytes versionBytes;
	versionBytes.a = true;
	versionBytes.b = true;
	*xfer == *reinterpret_cast<Xfer::Version *>(&versionBytes);
	Rva0055B0CC::Rva0055AED6(xfer, p);
	*xfer == m_2C;
	const AsciiString *buttonNameSource;
	if (m_commandButton != 0)
		buttonNameSource = &m_commandButton->getName();
	else
		buttonNameSource = &AsciiString::TheEmptyString;
	AsciiString tmp(*buttonNameSource);
	*xfer == tmp;
	if (!xfer->IsLoading())
		return;
	_ReadWriteBarrier();
	if (((const StringBase<char> *)&tmp)->compare(*(const StringBase<char> *)&AsciiString::TheEmptyString) == 0)
		return;
	Object *object = TheGameLogic->findObjectByID(m_builderID);
	if (object == 0)
		return;
	const AsciiString *commandSetName = object->rva00290E67();
	void *commandSet = ((Rva0031D5F8 *)((BfmeWorldRV *)TheControlBar))->rva0031D5F8(commandSetName);
	for (int i = 0; i < 0x20; ++i)
	{
		if (m_commandButton != 0)
			break;
		const CommandButton *commandButton = ((CommandSet *)commandSet)->getCommandButton(i);
		if (commandButton != 0)
		{
			if (((const StringBase<char> *)&commandButton->getName())->compare(*(const StringBase<char> *)&tmp) == 0)
			{
				m_commandButton = commandButton;
			}
		}
	}
}
