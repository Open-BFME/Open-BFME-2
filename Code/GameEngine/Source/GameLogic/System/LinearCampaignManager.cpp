// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// WB AF93C0 names LinearCampaignManager::DoXfer (assert1365).
// Native1EBB73..1EBCC6 is complete339B RET4: Version1/1 and bool current
// precede load/save of the current campaign name, GameDifficulty and block
// CurrentCampaign. The owning pointer is at+10; WB's separate arrow/get
// accessors establish the inline CampaignSlot view that reproduces native.
// Native ctor1EBAEA is the existing137B two-word ABI and C4 allocation.
// Its record pointer4 and difficulty8 are caller-observed; the pointee's concrete class and
// unseen bases remain unknown. Its no-allocation constructor has already
// been consumed as nothrow by the verified99B1ECF03 sibling.
// Existing clearAD6F4/set575674 own slot replacement; no globals or pins.

#include "ascii_string.h"
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct WallVersion
{
    WallVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual int BeginBlock(const char*);
virtual void EndBlock();
virtual void SkipBlock(const char*);
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(WallVersion *);
virtual void slot11();
virtual Xfer &XferSnapshot(void*);
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};


class Rva000AD6F4 {public: void clear();};
class Object;
class Rva00575674 {public: void rva00575674(Object*);};
class Rva001EB8D7 {public: void *rva001EB90C(const StringBase<char>&);};
class Rva001EBAEA {
public: Rva001EBAEA(int,int) throw();
 void *unknown0;
 const AsciiString *record4;
 int argument8;
 unsigned char opaque0c[0xc4-0xc];
};
void XferGameDifficulty(Xfer*,int*);
class CampaignSlot {
public:
 Rva001EBAEA *get() const { return pointer; }
 Rva001EBAEA *operator->() const { return pointer; }
 bool valid() const { return pointer!=0; }
private: Rva001EBAEA *pointer;
};
class LinearCampaignManager {
public: void DoXfer(Xfer*);
private: unsigned char prefix00[0x10]; CampaignSlot current;
};
void LinearCampaignManager::DoXfer(Xfer *xfer) {
 WallVersion version(1,1);
 xfer->xferVersion(&version);
 bool hasCurrent=current.valid();
 xfer->xferBool(&hasCurrent);
 if(xfer->IsLoading()) reinterpret_cast<Rva000AD6F4*>(&current)->clear();
 if(hasCurrent) {
  if(xfer->IsLoading()) {
   AsciiString name;
   xfer->xferAsciiString(&name);
   int difficulty;
   XferGameDifficulty(xfer,&difficulty);
   void *record=reinterpret_cast<Rva001EB8D7*>(this)->rva001EB90C(*reinterpret_cast<const StringBase<char>*>(&name));
   if(!record) xfer->SkipBlock("CurrentCampaign");
   else {
    xfer->BeginBlock("CurrentCampaign");
    Rva001EBAEA *state=new Rva001EBAEA(reinterpret_cast<int>(record),difficulty);
    reinterpret_cast<Rva00575674*>(&current)->rva00575674(reinterpret_cast<Object*>(state));
    xfer->XferSnapshot(current.get());
    xfer->EndBlock();
   }
  } else {
   AsciiString name=*current->record4;
   int difficulty=current->argument8;
   xfer->xferAsciiString(&name);
   XferGameDifficulty(xfer,&difficulty);
   xfer->BeginBlock("CurrentCampaign");
   xfer->XferSnapshot(current.get());
   xfer->EndBlock();
  }
 }
}
