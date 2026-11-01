// cl: /O1 /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?onContaining@OpenContain@@UAEXPAVObject@@_N@Z @0x00463097 161B
// Evidence: Native463097..463138 RET8 with unread two args; SlaughterHordeContain-family secondary interface20 flagBD owner minus18. Drawable key2F owning8B reference feeds canonical136B event ctor2D97D6 then conditional owner setter2D9531 and TheAudio slot25. Exact hot161 and native EH lifetime shape; current ownership/provider recovery closes old missing-release bank. Identity: slot 22 of the OpenContain +0x20 contain-interface vtable 0x008433B0 installed by the OpenContain ctor 0x004649F8, and the base call of GarrisonContain::onContaining 0x00478C2C and TransportContain::onContaining; the receiver is that interface, as in OpenContain::onRemoving (OpenContainOnRemoving.cpp). The ZH body in OpenContain.cpp plays its enter sound from the template; BFME2 keys it by Drawable.
#include "Common/BfmeAudioEventPrefix136.h"
class Rva002390CB {public:Rva002390CB(const Rva002390CB&);__forceinline ~Rva002390CB(){if(value.referent)value.referent->Release_Ref();}__forceinline operator const OpaqueRefElement4&()const{return value;}private:void*unknown;OpaqueRefElement4 value;};
class Drawable {public:Rva002390CB rva00462D95();};
class Object {public:Drawable*getDrawable()const;char pad[0x74];int id;};
class Rva002D9531
{
public:
	void rva002D9531(int v); // AudioEventRTS::setObjectID
};
class AudioManager {public:virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24(); virtual void add(BfmeAudioEventPrefix136*);};
extern AudioManager*TheAudio;
struct ContainModuleInterface {virtual void onContaining(Object*,bool)=0;};
class OpenContain:public ContainModuleInterface {public:virtual void onContaining(Object*,bool);private:__forceinline Object*owner(){return *reinterpret_cast<Object**>(reinterpret_cast<char*>(this)-0x18);}char pad[0xBD-4];bool flag;};
void OpenContain::onContaining(Object*,bool){if(flag&&owner()->getDrawable()){
 BfmeAudioEventPrefix136 event(owner()->getDrawable()->rva00462D95(),0);
 reinterpret_cast<Rva002D9531*>(&event)->rva002D9531(owner()->id);
 TheAudio->add(&event);
}}
