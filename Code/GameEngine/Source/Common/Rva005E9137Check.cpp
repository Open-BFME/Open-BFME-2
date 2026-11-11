// cl: /MD
// ?Rva005E9137Check@@YAEPAVRva00318F42@@@Z @0x005E9137 44B
// Evidence: retail checks g_009FEF10 null then +0xF4 then Rva002B280C::check then tail to 0x00318F42.
// Callers at 0x005E9169 0x005E9180 test al as bool.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Arg54;
class Rva00318F42
{
public:
	bool rva00318F42();
	char m_pad[0x20];
	int m_20;
};
#include "../../Include/Common/Rva002B280C.h"
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
unsigned char __cdecl Rva005E9137Check(class Rva00318F42 *target)
{
	class Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
	if (logic == 0)
		return 0;
	if (logic->m_xF4 != 0)
		return 0;
	if (((class Rva002B280C *)logic)->rva002B280C((struct Arg54 *)target))
		return target->rva00318F42();
	return 0;
}
// ?rva005E917A@Rva005E917A@@QAEXXZ @0x005E917A 47B
// Evidence: calls Rva005E9137Check then TheMessageStream slot 0x48 appendType 0x6a9 then GameMessage::appendIntegerArgument.
// Chain on 0x005E9137.
#include "../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;
class Rva005E917A
{
public:
	char m_pad[0x14];
	class Rva00318F42 *m_14;
	void rva005E917A();
};
void Rva005E917A::rva005E917A()
{
	if (Rva005E9137Check(m_14) == 0)
		return;
	class GameMessage *msg = TheMessageStream->appendMessage(0x6a9);
	msg->appendIntegerArgument(m_14->m_20);
}
