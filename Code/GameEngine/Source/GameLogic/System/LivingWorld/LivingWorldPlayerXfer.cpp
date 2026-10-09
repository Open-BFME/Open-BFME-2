// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <set>
// Native2E07FA..2E0856 RET0 and WBDE9400 establish the four-value
// unsigned transfer; exception identity is independently recovered at CFFD18.
// Native2E30C8..2E3442 RET4 supplies the complete player transfer sequence.
// WBDE7920 and the missing-player-template error independently identify the
// receiver. BF1 f98983a7 LivingWorldPlayerArmyXfer.cpp is a serialization guide;
// target vslots, version1..5, offsets, snapshot receivers and revival strideD8
// come from BF2. 1C8 uses the float slot70; 18/258/274/2C8 use Snapshot slot30.
// The original player transfer method name and those snapshot classes are unknown.
// ?Rva002E07FAXfer@@YAPAVXfer@@PAV1@PAI@Z
class AsciiString; class UnicodeString; class PooledString; class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D; class Coord2D; class ICoord2D; class Region2D; class IRegion2D; class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot; class XferUnknown11;
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


class XferException {
public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
Xfer *Rva002E07FAXfer(Xfer *xfer, unsigned int *values) {
 unsigned int count=4;
 *xfer == count;
 if(count != 4) throw XferException(0,0);
 for(unsigned int i=0;i<4;++i) *xfer == values[i];
 return xfer;
}

class INIException {public: INIException(int,const char*,...); INIException(const INIException&); ~INIException(); char *text; int tag;};
class Rva002E18C3Lookup {public: AsciiString *find(const AsciiString&);};
extern Rva002E18C3Lookup *Va00DFF0B0Lookup;
class ModuleData;
class Rva00291440;
void XferLivingWorldPlayerID(Xfer*,int*);
void XferOwningLivingWorldArmyVec(Xfer*,std::vector<const ModuleData*>*);
Xfer *Rva001ECA2DXfer(Xfer*,void*);
void rva003064CB(Xfer*,Rva00291440*);
class Rva002E15E6 {public: void rva002E15E6();};
Xfer *Rva002E208AXfer(Xfer*,std::set<int>*);
enum ScienceType {SCIENCE_INVALID=-1};
struct Rva002E2690Element { char unknown[0xD8]; };
struct Rva002E26E1Record { char unknown[0xD8]; };
struct Rva002E2D10Record { char unknown[0xD8]; };
class UnitRevivalEntry { public: UnitRevivalEntry(); ~UnitRevivalEntry(); void rva0037E473(Xfer*); char unknown[0xD8]; };
namespace _STL {
 template<> ScienceType *vector<ScienceType>::erase(ScienceType*,ScienceType*);
 template<> Rva002E2690Element *vector<Rva002E2690Element>::erase(Rva002E2690Element*,Rva002E2690Element*);
 template<> void vector<Rva002E26E1Record>::reserve(unsigned int);
 template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record&);
}
class RGBColor { public: float r,g,b; };
class LivingWorldPlayer {
public: void rva002E30C8(Xfer*);
 char unknown00[0x14]; int id;
 char unknown18[0x40-0x18]; AsciiString *playerTemplate; int state; AsciiString text48;
 char unknown4C[0x180-0x4C]; int colorIndex; RGBColor colors[3];
 std::vector<UnitRevivalEntry> revivalEntries;
 AsciiString text1B4; std::vector<const ModuleData*> armies; int count1C4; float value1C8;
 std::vector<ScienceType> sciences; char upgrades[0x80];
 char unknown258[0x290-0x258]; int value290,value294,queuedPoints; std::set<int> set29C,set2A8;
 unsigned int values2B4[4],value2C4; char unknown2C8[0x3C4-0x2C8]; bool flag3C4;
};
// ?rva002E30C8@LivingWorldPlayer@@QAEXPAVXfer@@@Z
void LivingWorldPlayer::rva002E30C8(Xfer *xfer) {
 Xfer::Version version(1,5); *xfer == version;
 XferLivingWorldPlayerID(xfer,&id);
 *xfer == *reinterpret_cast<Snapshot*>(unknown18);
 if(xfer->IsLoading()) {
  AsciiString name;
  *xfer == name;
  playerTemplate=Va00DFF0B0Lookup->find(name);
  if(!playerTemplate) throw INIException(3,"A Player template for this LivingWorldPlayer could not be found (was it removed from an INI?)");
 } else {
  AsciiString name=*playerTemplate;
  *xfer == name;
 }
 *xfer == flag3C4;
 int stateValue=state; *xfer == stateValue; state=stateValue;
 *xfer == text48;
 XferOwningLivingWorldArmyVec(xfer,&armies);
 {
  std::vector<ScienceType> &scienceVec=sciences;
  Xfer::Version sv(1,1); *xfer == sv;
  if(xfer->IsLoading()) scienceVec.erase(scienceVec.begin(),scienceVec.end());
  Rva001ECA2DXfer(xfer,&scienceVec);
 }
 *xfer == text1B4; *xfer == value1C8; *xfer == count1C4;
 rva003064CB(xfer,reinterpret_cast<Rva00291440*>(upgrades));
 *xfer == value290; *xfer == value294;
 *xfer == *reinterpret_cast<Snapshot*>(unknown258);
 *xfer == *reinterpret_cast<Snapshot*>(unknown258+0x1C);
 if(version.m_minimum>=4) *xfer == queuedPoints;
 *xfer == colorIndex;
 *xfer == colors[0]; *xfer == colors[1]; *xfer == colors[2];
 if(version.m_minimum>=2) {
  *xfer == *reinterpret_cast<Snapshot*>(unknown2C8);
  if(version.m_minimum>=3) {
   *xfer == value2C4;
   if(xfer->IsLoading() && state==1) value2C4=0;
  }
 }
 if(xfer->IsLoading()) {
  int count=0; *xfer == count;
  std::vector<Rva002E2690Element> &eraseView=*reinterpret_cast<std::vector<Rva002E2690Element>*>(&revivalEntries);
  eraseView.erase(eraseView.begin(),eraseView.end());
  reinterpret_cast<std::vector<Rva002E26E1Record>*>(&revivalEntries)->reserve(count);
  for(int i=0;i<count;++i) {
   UnitRevivalEntry entry;
   entry.rva0037E473(xfer);
   reinterpret_cast<std::vector<Rva002E2D10Record>*>(&revivalEntries)->push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
  }
 } else {
  int count=revivalEntries.size(); *xfer == count;
  for(int i=0;i<count;++i) revivalEntries[i].rva0037E473(xfer);
 }
 Rva002E07FAXfer(xfer,values2B4);
 if(version.m_minimum>=5) {
  if(xfer->IsLoading()) {
   reinterpret_cast<Rva002E15E6*>(&set29C)->rva002E15E6();
   reinterpret_cast<Rva002E15E6*>(&set2A8)->rva002E15E6();
  }
  Rva002E208AXfer(xfer,&set29C); Rva002E208AXfer(xfer,&set2A8);
 }
}
