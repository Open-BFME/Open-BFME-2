// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// SpawnArmy: native 88-byte record, named by WB LivingWorldCampaignObjects.cpp
// constructor 128AFA0 and retail virtual name "SpawnArmy" at 4E30C6.
// Retain the existing address-class binding used by its verified callers.
// Native C61F28 has four Snapshot slots: deleting destructor, loadPostProcess,
// GetSnapshotName and xfer. The real STLport vector supplies the constructor's
// allocator lifetime; a three-pointer declaration alone emits an extra byte.
// Constructor 4E30D5/175B, copy 4E2F9F/295B, destructor 4E3184/201B and
// xfer 4E3991/221B each match their complete retail bodies; all three emitted
// constructor/destructor exception tables are exact. Target field offsets and
// defaults are independent of the BFME1 9cbfb551fe20 semantic parser lead.
// stlport
#include <memory>
#include <vector>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class LivingWorldManager;
struct SpawnManagerCostView{unsigned char opaque[0xf0];float revivalCost;};
extern LivingWorldManager *TheLivingWorldManager;
class Rva004E3184:public Snapshot{public:Rva004E3184(int);virtual ~Rva004E3184();
 Rva004E3184(const Rva004E3184&);
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName()const;
 virtual void xfer(Xfer*);
 AsciiString m_04,m_08,m_0c,m_10,m_14,m_18,m_1c;
 float m_20,m_24;
 AsciiString m_28,m_2c,m_30,m_34;
 _STL::vector<AsciiString> m_38;
 float m_44;int m_48,m_4c;AsciiString m_50;bool m_54,m_55;
};
Rva004E3184::Rva004E3184(int index):m_20(0.0f),m_24(0.0f),m_2c(AsciiString::TheEmptyString),m_48(1),m_4c(index),m_54(false),m_55(true){
 if(TheLivingWorldManager) m_44=((const SpawnManagerCostView *)TheLivingWorldManager)->revivalCost;
 else m_44=5.0f;
}

Rva004E3184::~Rva004E3184() {}
void Rva004E3184::loadPostProcess() {}
const char *Rva004E3184::GetSnapshotName()const{return "SpawnArmy";}
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
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "Coord2D.h"

void Rva004E12D7Parse(void *a, void *b);
Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void Rva004E3184::xfer(Xfer *stream)
{
 Xfer &xfer=*stream;
	Xfer::Version version(1, 3);
	xfer == version;
	Rva004E12D7Parse(&xfer, &m_4c);
	xfer == m_04;
	xfer == m_08;
	xfer == *(Coord2D *)&m_20;
	xfer == m_2c;
	xfer == m_30;
	xfer == m_34;
	xferAsciiStringVector(&xfer, &m_38);
	xfer == m_54;
	xfer == m_50;
	xfer == m_44;
	xfer == m_55;
	if (version.m_minimum >= 2) {
		xfer == m_18;
	}
	if (version.m_minimum >= 3) {
		xfer == m_28;
		xfer == m_1c;
	}
}
