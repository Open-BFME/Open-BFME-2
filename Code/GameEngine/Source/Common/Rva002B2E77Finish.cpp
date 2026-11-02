// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002B2E77@LivingWorldLogic@@QAEXH@Z @0x002B2E77 23B
// void(int) wrapper: global factory at 0x00A00950 slot 0x48 creates message
// 0x6B9, then tail-appends the incoming int argument through the rowed
// 0x0030F936. Both retail callers (0x00433D6B in Rva00433D4D, 0x00436014 in
// the AptSaveLoad destructor) load ECX with TheLivingWorldLogic (0x00DFEF10)
// and null-test it before the push, which only the thiscall member spelling
// emits. The body never reads `this` and cleans the same four stack bytes, so
// the former stdcall Rva002B2E77Append row is byte-identical under the
// member name; the callee-clean ABI is what lets MSVC tail-jmp with the
// argument still in place.
#include "../../Include/Common/MessageStream.h"
class GlobalHolder {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual GameMessage* newMessage(int type);
};
extern class MessageStream *TheMessageStream;
#include "../../Include/GameLogic/LivingWorldLogic.h"
void LivingWorldLogic::rva002B2E77(int x)
{
	GameMessage *msg = (*(GlobalHolder **)&TheMessageStream)->newMessage(0x6B9);
	msg->appendIntegerArgument(x);
}
