// cl: /O1 /G7 /MD /EHsc
// Native4673C0..46740C complete76B RET0. TransportContain ctor468559 stores
// the secondary contain table at full object+20; this body reads owner at -18.
// Eight transport-family secondary tables point to this shared callback.
// WB115C5C0 corroborates three Object::clearModelConditionState operations.
// The original callback name is unasserted; retain its target address name.
// Target words at Object+10C clear bits18/19/20, each notifying only if set.
// Separate bit test/clear inlines mirror matched TransportContainRiders and
// Locomotor helpers. Existing change notifier28AE6D resolves every call.
// Partial accessed owner prefix/interface only; no vtable is emitted here.
class ModelConditionFlags {public:
 unsigned test(int bit)const{return words[bit>>5]&(1U<<(bit&31));}
 void clear(int bit){words[bit>>5]&=~(1U<<(bit&31));}
 unsigned words[19];
};
class Object {public:
 void rva0028AE6D();
 __forceinline void clearModelConditionBit(int bit){if(conditions.test(bit)!=0){conditions.clear(bit);rva0028AE6D();}}
 char prefix[0x10c];ModelConditionFlags conditions;
};
class TransportOwnerPrefix {public:virtual ~TransportOwnerPrefix();const void *data;Object *object;char rest[0x20-0xc];};
class TransportConditionInterface {public:virtual void rva004673C0()=0;};
class TransportContain : public TransportOwnerPrefix,public TransportConditionInterface {
public:virtual void rva004673C0();
};
void TransportContain::rva004673C0(){
 Object *owner=object;
 owner->clearModelConditionBit(18);
 owner->clearModelConditionBit(19);
 owner->clearModelConditionBit(20);
}
