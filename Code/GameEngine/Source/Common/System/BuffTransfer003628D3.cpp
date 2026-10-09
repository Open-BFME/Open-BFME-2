// BF1 donor BuffTransfer0040A260.cpp at 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Donor carries control flow and snapshot semantics; target independently proves
// version5 and TBUFF block plus the fields at04..30 and its template name at64.
// BuffManager::xfer362702 iterates nine44B entries and publishes g_Va00E01E74;
// target3628D3 is the entry transfer through that virtual slot. Owner name stays
// address-derived. Existing rowed lookup2D06CA and BuffLogic::addBuff30682A
// resolve the target providers. The Xfer slot view follows SnapshotXfersBfme.
// Full482B body and EH exact with BFME2's canonical AsciiString header.
// cl: /MD /O1 /Oy- /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
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
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
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
	Version() {}
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException {public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
struct BlockView003628D3 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
 virtual void begin(const char*); virtual void end(); virtual void skip(const char*);
};
struct Snapshot003628D3 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void transfer(Xfer*);
};
class ThingTemplate;
// Callable view of the rowed template lookup; its argument is a string pointer.
class ThingFactory;
class Rva002D06CA {public:void *rva002D06CA(const AsciiString*);};
extern ThingFactory *TheThingFactory;
class BuffLogic {public:void *addBuff(void*,void*);};
extern BuffLogic *TheBuffLogic;
extern void *g_Va00E01E74;
struct RGBColor { float red,green,blue; };
struct BuffTransfer003628D3 {
 int field00; bool field04; char bytes05[3]; int field08,field0c,field10,field14;
 Snapshot003628D3 *field18; const ThingTemplate *field1c; RGBColor field20; float field2c;
 Snapshot003628D3 field30;
 void transfer(Xfer*);
};
struct VersionStorage { Xfer::Version value; unsigned short padding; };
void BuffTransfer003628D3::transfer(Xfer *xfer) {
 { VersionStorage storage; Xfer::Version &version=storage.value; version.m_current=1; version.m_minimum=5;
 *xfer == version;
 if(xfer->IsCRC()) return;
 if(version.m_minimum<5) throw XferException(2,0); }
 *xfer == field04;
 xfer->XferRawBytes(&field08,4);
 xfer->XferRawBytes(&field0c,4);
 *xfer == field10; *xfer == field14;
 bool hasTemplate=field1c!=0;
 *xfer == hasTemplate;
 AsciiString name;
 if(xfer->IsLoading()) {
  if(hasTemplate) {
   *xfer == name;
   field1c=(const ThingTemplate*)((Rva002D06CA*)TheThingFactory)->rva002D06CA(&name);
   if(!field1c) throw XferException(4,0);
  } else field1c=0;
 } else if(hasTemplate) {
  name=*(const AsciiString*)((const char*)field1c+0x64);
  *xfer == name;
 }
 bool hasEffect=field18!=0;
 *xfer == hasEffect;
 if(xfer->IsLoading()) {
  if(hasEffect) {
   if(field1c && g_Va00E01E74) {
    field18=(Snapshot003628D3*)TheBuffLogic->addBuff((void*)field1c,g_Va00E01E74);
    ((BlockView003628D3*)xfer)->begin("TBUFF");
    field18->transfer(xfer);
    ((BlockView003628D3*)xfer)->end();
   } else ((BlockView003628D3*)xfer)->skip("TBUFF");
  } else field18=0;
 } else if(hasEffect) {
  ((BlockView003628D3*)xfer)->begin("TBUFF");
    field18->transfer(xfer);
    ((BlockView003628D3*)xfer)->end();
 }

 *xfer == field20;
 *xfer == field2c;
 field30.transfer(xfer);
}
