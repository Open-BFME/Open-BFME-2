// cl: /O1 /G7 /MD /EHsc
// Native87973..879A9; caller8B7CF in the W3D view factory family.
// A changed integer at +23CC is sent as message 0x452 when the named
// TheMessageStream global (VA E00950) exists; without it the member
// is updated directly. The concrete field/message semantics remain unknown.
// MessageStream appendMessage is slot18 as in ControlBarUpdateConstruction;
// GameMessage::appendIntegerArgument is the owned 30F936 provider.
class GameMessage{public:void appendIntegerArgument(int);};
class MessageStream{public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual GameMessage*appendMessage(int);};
extern MessageStream*TheMessageStream; // ledger alias of MessageStreamSubsystem at 0x00A00950
class Rva00087973 {public:void rva00087973(int value);private:char pad[0x23cc];int state;};
void Rva00087973::rva00087973(int value){if(value==state)return;if(TheMessageStream){GameMessage*m=TheMessageStream->appendMessage(0x452);m->appendIntegerArgument(value);}else state=value;}
