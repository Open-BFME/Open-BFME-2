// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BannerCarrier update394 directly calls this native214B spawn helper.
// BFME1 update donor final contained-object helper supplies its semantic
// relation; target retail/WB establish slot95 cap,98 count,99 spawn.
// Original internal method name remains unknown. W3DBridge::setEnabled
// is the existing folded +110 Boolean setter provider; the receiver here
// is Player's +3BC credit view, not established as a W3DBridge instance.
class Object; class Player; class FXList;
template<int N> class BannerSpawnSlots:public BannerSpawnSlots<N-1> { public:virtual void gap(char(*)[N])=0; };
template<> class BannerSpawnSlots<0> {};
class BannerSpawnHorde:public BannerSpawnSlots<95> {
public: virtual unsigned cap()=0; virtual void slot96()=0;virtual void slot97()=0;
 virtual unsigned count()=0;virtual Object *spawn(void *)=0;
};
class BannerSpawnContain:public BannerSpawnSlots<31> { public:virtual BannerSpawnHorde *horde()=0; };
class W3DBridge { public: void setEnabled(bool); char pad00[0x110];bool enabled; };
class Player { public: char pad00[0x3BC];W3DBridge credits; };
class Object { public:
 Player *getControllingPlayer() const;void updateShroudNow();
 char pad00[8];char matrix[0x30];char pad38[0x250-0x38];BannerSpawnContain *contain;
 char pad254[0x274-0x254];Object *containedBy;
};
class FXList { public:static void doFXObj(const FXList *,const Object *,const Object *); };
class Rva00496B48 { public:bool rva00496B48(); };
struct BannerSpawnConfig { char pad00[0x34]; const FXList *unitSpawnFX; };
class BannerCarrierUpdate { public:
 bool rva00496BD2(Object *obj);
 char pad00[4];const BannerSpawnConfig *data;Object *object;
};
bool BannerCarrierUpdate::rva00496BD2(Object *obj) {
 Object *container=obj->containedBy;
 if(container) {
  BannerSpawnContain *contain=container->contain;
  if(!contain) return false;
  BannerSpawnHorde *h=contain->horde();
  if(h) {
   unsigned cap=h->cap();
   unsigned count=h->count();
   if(count<cap) {
    if(!reinterpret_cast<Rva00496B48 *>(this)->rva00496B48()) return false;
    Player *p=container->getControllingPlayer();
    W3DBridge *credits=&p->credits;
    bool enabled=credits->enabled;
    credits->setEnabled(false);
    Object *created=h->spawn(obj->matrix);
    if(created) {
     const BannerSpawnConfig *d=data;
     created->updateShroudNow();
     const FXList *fx=d->unitSpawnFX;
     if(fx) FXList::doFXObj(fx,created,0);
     credits->setEnabled(enabled);
     return true;
    }
    credits->setEnabled(enabled);
   }
  }
 }
 return false;
}
