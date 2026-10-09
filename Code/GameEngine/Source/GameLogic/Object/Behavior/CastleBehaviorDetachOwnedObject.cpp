// cl: /O1 /G7 /arch:SSE /MD
// Native395EB8/83; WB ebb4e0 counterpart and cleanup397D0A caller establish
// CastleBehavior ownership; method purpose inferred from owned Object cleanup.
// Original method name unresolved; layout and bit95 established from target.
// Native395EB8/83: Object* stack argument, unused module receiver, RET4.
// Producer ID, disabled mask and status calls have established providers.
enum ObjectStatusTypes{STATUS3=3,STATUS5=5,STATUS79=79};
enum DisabledType{DISABLED3=3};
struct ModelConditionPrefix{unsigned words[3];unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}void clear(int bit){words[bit>>5]&=~(1U<<(bit&31));}};
class Object{public:void setProducer(Object*);bool clearDisabled(DisabledType);void rva0028AE6D();void setStatus(ObjectStatusTypes,bool);char prefix[0x10C];ModelConditionPrefix flags;};
class CastleBehavior{public:void rva00395EB8(Object*);};
void CastleBehavior::rva00395EB8(Object*owned){
 owned->setProducer(0);owned->clearDisabled(DISABLED3);
 if(owned->flags.test(95)){owned->flags.clear(95);owned->rva0028AE6D();}
 owned->setStatus(STATUS3,false);owned->setStatus(STATUS79,false);owned->setStatus(STATUS5,false);
}
