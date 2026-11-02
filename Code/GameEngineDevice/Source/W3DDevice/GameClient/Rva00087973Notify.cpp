// cl: /O1 /G7 /MD /EHsc
// Native87973..879A9; caller8B7CF in the W3D view factory family.
// A changed integer at +23CC is sent as message 0x452 when the named
// TheMessageStream global (VA E00950) exists; without it the member
// is updated directly. The concrete field/message semantics remain unknown.
// MessageStream appendMessage is slot18 as in ControlBarUpdateConstruction;
// GameMessage::appendIntegerArgument is the owned 30F936 provider.
#include "../../../../GameEngine/Include/Common/MessageStream.h"
extern MessageStream*TheMessageStream; // ledger alias of MessageStreamSubsystem at 0x00A00950
// The receiver is the W3DView object: the W3DView constructor 0x0008B7CF
// ends by calling this body on its own this with 0.
class W3DView {public:void rva00087973(int value);private:char pad[0x23cc];int state;};
void W3DView::rva00087973(int value){if(value==state)return;if(TheMessageStream){GameMessage*gameMessage=TheMessageStream->appendMessage(0x452);gameMessage->appendIntegerArgument(value);}else state=value;}
