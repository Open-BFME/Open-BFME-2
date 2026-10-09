// cl: /O1 /G7 /arch:SSE /MD /EHsc

// Native224D80..224DFF127B returns the local lazy owning holder's pointer.
// WB B8FC20 has the same static guard, allocation, constructor and slot08 call;
// named AptPlayer constructor B8F880 calls it at AptPlayer.cpp251. The callee
// constructor names AptButtonTooltipMap. Its original accessor spelling is unknown.
// Native allocation proves32B; the constructor declaration is an opaque ABI view.
// A real local static generates retail guard, atexit cleanup and EH state; no
// hand-coded guard global or callback pin is needed. All providers are owned.
class Object { public: virtual void *destroy(int); virtual void slot04(); virtual void slot08(); };
class Rva00575674 {public: void rva00575674(Object*); Object *ptr;};
class Rva000AD6F4 {public: void clear();};
class Rva00224CDC {public: Rva00224CDC(); char data[0x20];};
class AptTooltipHolder {
public:
 Object *ptr;
 // ?AptTooltipHolder::AptTooltipHolder present-unmatched
 AptTooltipHolder():ptr(0){}
 // ?AptTooltipHolder::~AptTooltipHolder present-unmatched
 ~AptTooltipHolder(){ ((Rva000AD6F4*)this)->clear(); }
};
Rva00224CDC *rva00224D80() {
 static AptTooltipHolder holder;
 if(!holder.ptr) {
  ((Rva00575674*)&holder)->rva00575674((Object*)new Rva00224CDC);
  holder.ptr->slot08();
 }
 return (Rva00224CDC*)holder.ptr;
}
