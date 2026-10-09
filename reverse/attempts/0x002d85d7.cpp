// ?xfer@Radar@@MAEXPAVXfer@@@Z
// partial score=0.88 date=2026-10-09
// ZH Radar.cpp xferRadarObjectList primary semantic spine, currentBF1 2f243e26d.
// WB110A280/1109E60 and native2D84F6/2D85D7 prove helper225/caller482 boundaries.
// Complete compound reconstruction. Native EDI=Xfer,EAX=head; TU compiler picks
// EDI=head, stack Xfer and caller ESI=Xfer. vtable/new RadarObject and slot flow
// from native. G6/reordered args unchanged; Og/O2 worse.
// cl: /I. /O1 /G7 /MD /EHsc /DNDEBUG
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data,unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


struct BfmeFormattedText {char *text; int tag;};
extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result,int tag,const char *format,...);
extern int g_guardTargetTypeThrowInfo;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *, const _s__ThrowInfo *);
class Object {public: char unknown[0x94]; unsigned int destroyed;};
class RadarObject {
public:
 RadarObject():color(-1),object(0),next(0){}
 virtual ~RadarObject() {}
 virtual void loadPostProcess() {}
 virtual const char*GetSnapshotName()const;
 virtual void xfer(Xfer*);
 Object*object;RadarObject*next;int color;
};
static __declspec(noinline) void xferRadarObjectList(Xfer*xfer,RadarObject**head) {
 xfer->Version1(); unsigned short count=0;
 RadarObject*r;
 for(r=*head;r;r=r->next)++count;
 *xfer==count;
 if(xfer->IsStoring()) {
  for(r=*head;r;r=r->next) *xfer==*reinterpret_cast<Snapshot *>(r);
 }else {
  for(r=*head;r;r=r->next) {
   if(!(r->object->destroyed&1)) {
    BfmeFormattedText e;bfmeFormatText(&e,5,0);
    _CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_guardTargetTypeThrowInfo));
   }
  }
  unsigned short i=0;
  if(count>i) do {
   r=new RadarObject;
   if(!*head)*head=r;
   else {RadarObject*other=*head;while(other->next)other=other->next;other->next=r;}
   *xfer==*reinterpret_cast<Snapshot *>(r);
   ++i;
  }while(i<count);
 }
}

class Radar {
public: virtual void slot00();virtual void slot01();virtual void slot02();
protected: virtual void xfer(Xfer*xfer);
private: char pad04[0xc];bool hidden,forceOn; char pad12[2];
 RadarObject*objects,*localObjects; char region1C[0x10];
 struct Event {int type;bool active;unsigned int createFrame,dieFrame,fadeFrame;char color1[16],color2[16],world[12];int radar[2];bool soundPlayed;void*ref;} events[64];
 int nextFree;char pad1430[0x1c];float f144C;char pad1450[0xc];bool b145C;char pad145D[3];unsigned int word1460;
};
void XferRadarEventType(Xfer*,int*);
class RadarEventRefSlot {public:void clearRef();};
void Radar::xfer(Xfer*xfer) {
 if(xfer->IsLightCRC())return;
 Xfer::Version version(1,3); *xfer==version;
 *xfer==hidden;*xfer==forceOn;
 xferRadarObjectList(xfer,&localObjects);xferRadarObjectList(xfer,&objects);
 unsigned short count=64;*xfer==count;
 if(count!=64){BfmeFormattedText e;bfmeFormatText(&e,5,0);_CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_guardTargetTypeThrowInfo));}
 unsigned short i=0;
 do {
  Event &e=events[i]; XferRadarEventType(xfer,&e.type);
  *xfer==e.active;*xfer==e.createFrame;*xfer==e.dieFrame;*xfer==e.fadeFrame;
  *xfer==*reinterpret_cast<RGBAColorInt*>(e.color1);*xfer==*reinterpret_cast<RGBAColorInt*>(e.color2);
  *xfer==*reinterpret_cast<Coord3DBase*>(e.world);*xfer==*reinterpret_cast<ICoord2D*>(e.radar);
  *xfer==e.soundPlayed;
  if(!xfer->IsStoring())reinterpret_cast<RadarEventRefSlot*>(&e.ref)->clearRef();
  ++i;
 }while(i<count);
 *xfer==nextFree;
 if(version.m_minimum<3){int oldIndex=0;*xfer==oldIndex;}
 *xfer==*reinterpret_cast<PooledString*>(region1C);
 *xfer==*reinterpret_cast<PooledString*>(region1C+4);
 *xfer==*reinterpret_cast<PooledString*>(region1C+8);
 *xfer==*reinterpret_cast<PooledString*>(region1C+12);
 *xfer==f144C;*xfer==b145C;*xfer==f144C;*xfer==word1460;
 if(version.m_minimum==2){int old;unsigned int old2;*xfer==old;*xfer==old2;}
}
