// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// Retail0045F084..0045F21C RET4. WB118ACD0 names changeStance and
// agrees on the rider/stance/attribute/listener/AI call relationships.
// Registered named class factory24B37C and constructor45EF80 establish
// primary data4/object8, listener descriptor20 and current stance30.
// No applicable Stances source was found at BFME1 revision575ba2b04743;
// this reconstruction follows target bytes and the existing owned helpers.
// The store lookup returns an int payload. Target uses an8-byte index
// stride and words1/2 relative to it; record boundaries remain unresolved.
// Rider and AI virtual slot purposes remain neutral. Listener vcall slot1
// uses the already admitted folded thunk and existing forEach ABI.
// The existing27-byte stance classifier precedes this body as an ordinary
// definition so the compiler observes its preserved ECX/EDX. The comparison
// puts newClass first to retain retail's one-byte operand encoding.
// Native0045F084..0045F21C, WB118ACD0 changeStance callgraph semantic lead.
// Named constructor/factory prove StancesBehavior primary data4/object8,
// listener-list20 and stance30; neutral rider slots retain target behavior.
class AsciiString;
enum NameKeyType{KEY0=0};class NameKeyGenerator{public:const AsciiString&keyToName(NameKeyType);};extern NameKeyGenerator*TheNameKeyGenerator;
class Rva004260DE{public:int*rva004260DE(int);};class Rva00425F10;extern Rva00425F10*TheStancesStore;
template<int N>class VGap:public VGap<N-1>{public:virtual void gap(char(*)[N])=0;};template<>class VGap<0>{};
class StanceRider:public VGap<23>{public:virtual bool slot23()=0;
 virtual void slot24()=0;
 virtual void gap25()=0;
 virtual void gap26()=0;
 virtual void gap27()=0;
 virtual void gap28()=0;
 virtual void gap29()=0;
 virtual void gap30()=0;
 virtual void gap31()=0;
 virtual void gap32()=0;
 virtual void gap33()=0;
 virtual void gap34()=0;
 virtual void gap35()=0;
 virtual void gap36()=0;
 virtual void gap37()=0;
 virtual void gap38()=0;
 virtual void gap39()=0;
 virtual void gap40()=0;
 virtual void gap41()=0;
 virtual void gap42()=0;
 virtual void gap43()=0;
 virtual void gap44()=0;
 virtual void gap45()=0;
 virtual void gap46()=0;
 virtual void gap47()=0;
 virtual void gap48()=0;
 virtual void gap49()=0;
 virtual void gap50()=0;
 virtual void gap51()=0;
 virtual void gap52()=0;
 virtual void gap53()=0;
 virtual void gap54()=0;
 virtual void gap55()=0;
 virtual void gap56()=0;
 virtual void gap57()=0;
 virtual void gap58()=0;
 virtual void gap59()=0;
 virtual bool slot60()=0;
 virtual void gap61()=0;
 virtual void gap62()=0;
 virtual void gap63()=0;
 virtual void gap64()=0;
 virtual void gap65()=0;
 virtual void gap66()=0;
 virtual void gap67()=0;
 virtual void gap68()=0;
 virtual void gap69()=0;
 virtual void gap70()=0;
 virtual void gap71()=0;
 virtual void gap72()=0;
 virtual void gap73()=0;
 virtual void gap74()=0;
 virtual void gap75()=0;
 virtual void gap76()=0;
 virtual void gap77()=0;
 virtual void gap78()=0;
 virtual void gap79()=0;
 virtual void gap80()=0;
 virtual void gap81()=0;
 virtual void gap82()=0;
 virtual void gap83()=0;
 virtual void gap84()=0;
 virtual void gap85()=0;
 virtual void gap86()=0;
 virtual void gap87()=0;
 virtual void gap88()=0;
 virtual void gap89()=0;
 virtual void gap90()=0;
 virtual void gap91()=0;
 virtual void gap92()=0;
 virtual void gap93()=0;
 virtual void gap94()=0;
 virtual void gap95()=0;
 virtual void gap96()=0;
 virtual void gap97()=0;
 virtual void gap98()=0;
 virtual void gap99()=0;
 virtual void gap100()=0;
 virtual void gap101()=0;
 virtual void gap102()=0;
 virtual void gap103()=0;
 virtual void gap104()=0;
 virtual void gap105()=0;
 virtual void gap106()=0;
 virtual void gap107()=0;
 virtual void gap108()=0;
 virtual void gap109()=0;
 virtual void gap110()=0;
 virtual void gap111()=0;
 virtual void gap112()=0;
 virtual void gap113()=0;
 virtual void gap114()=0;
 virtual void gap115()=0;
 virtual void gap116()=0;
 virtual void gap117()=0;
 virtual void gap118()=0;
 virtual void gap119()=0;
 virtual void gap120()=0;
 virtual void gap121()=0;
 virtual void gap122()=0;
 virtual void gap123()=0;
 virtual void gap124()=0;
 virtual void gap125()=0;
 virtual void gap126()=0;
 virtual void gap127()=0;
 virtual void gap128()=0;
 virtual void gap129()=0;
 virtual void gap130()=0;
 virtual void gap131()=0;
 virtual void gap132()=0;
 virtual void gap133()=0;
 virtual void gap134()=0;
 virtual void gap135()=0;
 virtual void gap136()=0;
 virtual void gap137()=0;
 virtual void gap138()=0;
 virtual void gap139()=0;
 virtual void gap140()=0;
 virtual void gap141()=0;
 virtual void gap142()=0;
 virtual void gap143()=0;
 virtual void gap144()=0;
 virtual void gap145()=0;
 virtual void gap146()=0;
 virtual void gap147()=0;
 virtual void gap148()=0;
 virtual void gap149()=0;
 virtual void gap150()=0;
 virtual void gap151()=0;
 virtual void slot152(int)=0;};
class StanceContain:public VGap<31>{public:virtual StanceRider*getRider()=0;};
enum CommandSourceType{SOURCE0=0,SOURCE2=2};class AICommandInterface{public:void aiIdle(CommandSourceType);};
class AIUpdateInterface:public VGap<110>{public:virtual bool slot110()=0;void rva00262D40(int);AICommandInterface&commands(){return*(AICommandInterface*)((char*)this+0x20);}};
class Object{public:char pad[0x250];StanceContain*contain;int pad254;AIUpdateInterface*ai;void removeAttributeModifierFromPool(const AsciiString&);bool addAttributeModifierToPool(const AsciiString&,int);__forceinline StanceRider*getRider(){StanceContain*c=contain;return c?c->getRider():0;}};
class Rva0045EF55Listener{public:virtual void gap0()=0;
 virtual void notify(void*,int,int)=0;};
class Rva0045EF55List{public:void forEach(void(Rva0045EF55Listener::*)(void*,int,int),void*,int,int);char pad[16];};
struct StanceData{char pad[8];int key;};
class StancesBehavior{public:bool changeStance(int);int rva0045ED4B()const;void*vtable;StanceData*data;Object*object;char pad0c[0x14];Rva0045EF55List listeners;int stance;};
int StancesBehavior::rva0045ED4B()const{switch(stance){case 2:return 2;case 3:case 4:case 5:return 3;}return 1;}
bool StancesBehavior::changeStance(int value){
 Object*obj=object;if(value==stance)return false;
 StanceRider*rider=obj->getRider();
 if(rider && stance==4 && rider->slot60() && rider->slot23()){rider->slot24();rider=obj->getRider();}
 if(value==3){AIUpdateInterface*ai=obj->ai;if(ai)ai->commands().aiIdle(SOURCE0);}
 int key=data->key;if(!key)return false;
 int*entries=((Rva004260DE*)TheStancesStore)->rva004260DE(key);if(!entries)return false;
 NameKeyType oldMod=(NameKeyType)entries[stance*2+1];int*entry=entries+value*2;NameKeyType newMod=(NameKeyType)entry[1];
 if(oldMod!=newMod){if(oldMod)obj->removeAttributeModifierFromPool(TheNameKeyGenerator->keyToName(oldMod));if(newMod)obj->addAttributeModifierToPool(TheNameKeyGenerator->keyToName(newMod),-1);}
 if(rider)rider->slot152(entry[2]);
 int oldStance=stance;int oldClass=rva0045ED4B();stance=value;int newClass=rva0045ED4B();
 if(oldStance==0 || newClass!=oldClass){
 listeners.forEach(&Rva0045EF55Listener::notify,this,oldClass,newClass);
 AIUpdateInterface*ai=obj->ai;if(ai && ai->slot110()){
 if(value==1)ai->rva00262D40(0);else if(value==3 || value==4)ai->rva00262D40(1);else if(oldStance==1 || oldStance==3)ai->commands().aiIdle(SOURCE2);
 }}return true;
}
