// ?xferNoName@DynamicAudioEventInfo@@QAEXPAVXfer@@@Z
// partial score=0.97 date=2026-10-08
// Target 0x004331C6/458: DynamicAudioEventInfo::xferNoName.
// ZH DynamicAudioEventInfo.cpp supplies override mask order and save purpose;
// BFME1 donor ba7ddda7 DynamicAudioEventInfo.cpp supplies real/enum setters
// and load-only loop control update. Target accesses prove +C4 mask, +44
// priority, +4C control, +10/+1C volume and +94/+98 ranges. No full class
// layout or original base-setter spellings inferred from donor alone.
// Existing folded real setters are direct qualified calls; their source
// owner types are not asserted as audio inheritance. Priority uses corrected
// enum provider 41FDEE. Its former float alias would resolve to wrong179010.
// Remaining difference: loading mask loop emits AL AND/NEG + SBB EAX rather
// than MOVZX EAX then DWORD AND/NEG + SBB EDX; 457 vs458. The rest aligns
// after the one-byte shift. G5/G6/G7 and integer/Bool helpers did not fix it.
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /arch:SSE /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
class Xfer;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

// BFME 2's Xfer (as GameLogicInit.cpp): MSVC lays the operator== overloads
// out in reverse, so AsciiString is slot 27, unsigned int 30, unsigned
// short 32.
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

	virtual void beginBlock(const char *name) = 0;
	virtual void endBlock() = 0;
	virtual void skip(const char *name) = 0;

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
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class WeaponTemplateSetHead { public: void rva000B3FA5(int,int); };
class Rva001D96FF {public: void rva001D96FF(int);};
class Rva001D9709 {public: void rva001D9709(int);};
class W3DRopeDraw {public: virtual void setRopeCurLen(float);};
class Anim2D {public: void setAlpha(float);};
class Rva001D972BFloatField {public: void set(float);};
class RenderObjClass {public: virtual void _bfme_ro_set_98(float);};
enum AudioPriority {AP_LOWEST,AP_LOW,AP_NORMAL,AP_HIGH,AP_CRITICAL};
class AudioEventInfo {public: void Rva0041FDEE(AudioPriority); private: char p00[0x44]; AudioPriority m_priority;};

class DynamicAudioEventInfo {
public:
 void xferNoName(Xfer *x);
 unsigned char p00[0x10]; float at10;
 unsigned char p14[8]; float at1c;
 unsigned char p20[0x24]; unsigned int priority;
 unsigned char p48[4]; unsigned int control;
 unsigned char p50[0x44]; float at94,at98;
 unsigned char p9c[0x28]; unsigned int flags[1];
 __forceinline bool test(unsigned int bit) const {return (flags[bit>>5] & (1u<<(bit&31)))!=0;}
};
void DynamicAudioEventInfo::xferNoName(Xfer *x) {
 Xfer::Version version(1,1); *x == version;
 if(x->IsLoading()) {
  unsigned char bits; *x == bits;
  for(int i=0;i<8;++i)
   ((WeaponTemplateSetHead *)flags)->rva000B3FA5(i,(bits & (1<<i))!=0);
 } else {
  unsigned char bits=0;
  for(int i=0;i<8;++i) if(test(i)) bits |= 1<<i;
  *x == bits;
 }
 if(test(1)) {
  bool b=(control&1)!=0; *x == b;
  if(x->IsLoading()) {
   if(b) ((Rva001D96FF*)this)->rva001D96FF(1);
   else ((Rva001D9709*)this)->rva001D9709(1);
  }
 }
 if(test(3)){float v=at10; *x == v; ((W3DRopeDraw*)this)->W3DRopeDraw::setRopeCurLen(v);}
 if(test(4)){float v=at1c; *x == v; ((Anim2D*)this)->setAlpha(v);}
 if(test(5)){float v=at94; *x == v; ((Rva001D972BFloatField*)this)->set(v);}
 if(test(6)){float v=at98; *x == v; ((RenderObjClass*)this)->RenderObjClass::_bfme_ro_set_98(v);}
 if(test(7)){unsigned char v=priority; *x == v; ((AudioEventInfo*)this)->Rva0041FDEE((AudioPriority)v);}
}
