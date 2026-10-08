// stlport
// cl: /O1 /MD /G7 /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
#include <vector>
// WB142F640 names StanceToButtonSlot and WB1430D70 names Impl::SetStance.
// Native helper567807..56783A is51B; dispatch567A6E..567B10 is162B.
// The local helper receives CommandButton in EDI under VC7.1 optimization.
// Its verified vector at +234 and getStance provider establish the lookup.
// Keep the existing Rva receiver/method name for its already-matched caller.
class Image;
class GameWindow;
class CommandButton {public:int getStance(int);const Image *rva0035B19E()const;
 char pad[0x234];_STL::vector<int> stances;
};
class Rva0035B424 {public:void rva0035B424(int);};
class Rva0057C22FByteChaseField {public:unsigned char get()const;};
class Rva005C39AA {public:void rva005C39AA();};
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *,const Image *);
__declspec(noinline) static int StanceToButtonSlot(CommandButton *button,int stance) {
 int count=button->stances.size();
 for(int i=0;i<count;++i)if(button->getStance(i)==stance)return i;
 return -1;
}
class GameMessage {public:enum Type {STANCE_VOICE=0x7E3};void appendIntegerArgument(int);};
class MessageStream {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void v17();virtual GameMessage *createMessage(int);
};
extern MessageStream *MessageStreamSubsystem;
class DrawableList;
class PickAndPlayInfo {public:PickAndPlayInfo();char pad[0x20];CommandButton *button;};
void pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
class InGameUI;
extern InGameUI *TheInGameUI;
class StanceUISelectionView {public:
#define SLOT(N) virtual void v##N();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
 SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
 SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
 SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
 SLOT(72)
#undef SLOT
 virtual const DrawableList *selection();
};
class StanceOwnerView {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void *currentMenu();};
class Rva00525E55 {public:void rva00567A6E(int);char pad[0xC];StanceOwnerView *owner;GameWindow *window;CommandButton *button;};
// ?rva00567A6E@Rva00525E55@@QAEXH@Z present-unmatched
void Rva00525E55::rva00567A6E(int stance) {
 reinterpret_cast<Rva0035B424 *>(button)->rva0035B424(StanceToButtonSlot(button,stance));
 GadgetButtonSetEnabledImage_Rva002C0433(window,button->rva0035B19E());
 GameMessage *message=MessageStreamSubsystem->createMessage(0x468);
 message->appendIntegerArgument(stance);
 void *menu=owner->currentMenu();
 if(menu && reinterpret_cast<Rva0057C22FByteChaseField *>(menu)->get())reinterpret_cast<Rva005C39AA *>(menu)->rva005C39AA();
 const DrawableList *selected=reinterpret_cast<StanceUISelectionView *>(TheInGameUI)->selection();
 PickAndPlayInfo info;
 info.button=button;
 pickAndPlayUnitVoiceResponse(selected,GameMessage::STANCE_VOICE,&info);
}
