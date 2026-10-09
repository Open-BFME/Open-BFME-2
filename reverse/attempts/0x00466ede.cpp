// ?slot38@TransportContain@@UAE_NPAVObject@@HH@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /MD /DNDEBUG /Oy-
// ZH TransportContain.cpp admission supplies the fake-container and capacity
// semantics; BFME2 native466EDE..466FE0 adds status62, owner-bit gate14C and
// the kind132/data13D branch. Existing slot38 pin proves secondary receiver20.
// Prefix and virtual-slot views describe only consumed ABI; no instances.
enum ObjectStatusTypes { STATUS_62=62 };
enum KindOfType { KIND_NONE=0 };
class Object;
template<int N> class Rva00466EDESlots:public Rva00466EDESlots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00466EDESlots<1> { public: virtual void gap(char (*)[1]); };
struct Rva00466EDENode { Rva00466EDENode *next; void *previous; Object *object; };
struct Rva00466EDEList { Rva00466EDENode *head; };
struct Rva00466EDEPair { int unknown; Rva00466EDEList *list; };
class Rva00466EDEContained:public Rva00466EDESlots<5> { public: virtual bool slot5(); };
class Rva00466EDEListView:public Rva00466EDESlots<70> { public: virtual void slot70(Rva00466EDEPair *); };
class Rva00466EDECount:public Rva00466EDESlots<69> { public: virtual unsigned slot69(int); };
class Rva00466EDEMax:public Rva00466EDESlots<28> { public: virtual unsigned slot28(); };
class Object { public:
    bool testStatus(ObjectStatusTypes) const;
    bool isKindOf(KindOfType) const;
    int rva0028FBBE();
    char unknown00[4]; const unsigned char *type;
    char unknown08[0x250-8]; Rva00466EDEContained *contain;
};
class OpenContain { public: virtual bool isValidContainerFor(Object *,bool,bool); };
struct Rva00466EDEData { char unknown00[0x13D]; unsigned char flag13D; char unknown13E[0x14C-0x13E]; int ownerBit; };
class TransportContain:public Rva00466EDESlots<38> {
public:
    virtual bool slot38(Object *,int,int);
    __forceinline Rva00466EDEData *moduleData() const { return *reinterpret_cast<Rva00466EDEData *const *>(reinterpret_cast<const char *>(this)-0x1C); }
    __forceinline Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x18); }
    __forceinline unsigned count() { return reinterpret_cast<Rva00466EDECount *>(this)->slot69(0); }
    __forceinline unsigned maximum() { return reinterpret_cast<Rva00466EDEMax *>(this)->slot28(); }
    __forceinline unsigned extraSlots() const { return *reinterpret_cast<const unsigned *>(reinterpret_cast<const char *>(this)+0xE0); }
};
bool TransportContain::slot38(Object *rider,int checkCapacity,int trailing)
{
    Rva00466EDEData *data=moduleData();
    if (!rider) {
failed:
        return false;
    }
    if (rider->testStatus(STATUS_62)) goto failed;
    int required=data->ownerBit;
    if (required!=-1 && !object()->isKindOf(static_cast<KindOfType>(required))) goto failed;
    Rva00466EDEContained *const &contained=rider->contain;
    if (contained && contained->slot5()) {
        Rva00466EDEPair pair;
        reinterpret_cast<Rva00466EDEListView *>(contained)->slot70(&pair);
        Rva00466EDENode *head=pair.list->head;
        Rva00466EDENode *first=head->next;
        if (first!=head && first->object) rider=first->object;
    }
    if (!reinterpret_cast<OpenContain *>(this)->OpenContain::isValidContainerFor(rider,*reinterpret_cast<bool *>(&checkCapacity),*reinterpret_cast<bool *>(&trailing))) goto failed;
    if ((rider->type[0x118]&0x10) && moduleData()->flag13D) {
        unsigned used=count();
        return used<maximum();
    }
    register unsigned slots=static_cast<unsigned>(rider->rva0028FBBE());
    if (!slots) goto failed;
    if (*reinterpret_cast<const unsigned char *>(&checkCapacity)) {
        unsigned used=count();
        used+=extraSlots();
        used+=slots;
        return maximum()>=used;
    }
    return true;
}
