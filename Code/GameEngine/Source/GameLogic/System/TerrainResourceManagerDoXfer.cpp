// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Type evidence: retail Xfer vtable BBB910 slot22 names Region3D transfer
// at60B9C9; slot28 is float554C; slot36 is bool54A4. Region3D is24B,
// exactly covering1C..34; list records use4-byte float at4 and bool at8.
// WB E62590 identifies TerrainResourceManager::DoXfer and its vtable context.
// Native35ABE0..35AEBB proves list14, floats18/3C, region1C, dimensions34/38
// and 16-byte cell array40. BF1 ba7ddda and ZH contain no clean matching
// manager unit. Payloads retain the existing providers' provisional names:
// BfmePod12 carries ID/float/bool; BfmePod8 carries int/ObjectID bits.
// Rva0035A18D is the existing array-lifecycle ABI view, whose original
// application type is unknown. Retail cell access and resize35ABC0 prove
// its vector-of-eight-byte-record layout; the earlier string view was only
// an inference from its folded free-first-pointer destructor.
// Array ctor1F81BF and dtor7FAB3 are independently compiled byte/relocation
// twins of existing owners; neither fold asserts ObjectCreationList or
// a string identity for these terrain cells.
#include <list>
// Compare list nodes locally; avoid offering an unrelated iterator-base COMDAT.
namespace _STL {
template<class T,class Traits> static inline bool operator!=(const _List_iterator<T,Traits> &a,const _List_iterator<T,Traits> &b) {return a._M_node!=b._M_node;}
}

#include <vector>
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Region3D.h"
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../Include/Common/BfmeXfer.h"
class Xfer::Version { public: Version(unsigned char low,unsigned char high):version(low),current(high){} unsigned char version,current; };
void XferObjectID(Xfer *, ObjectID *);
struct BfmePod12
{
	int key;
	float value;
	bool flag;
	bool zero;
	char padding[2];
};
struct BfmePod8
{
public:
	int a[2]; // +0x00 +0x00
};
namespace _STL { template<> void list<BfmePod12>::push_back(const BfmePod12 &); }
class Rva0035ABC0 { public: void rva0035ABC0(unsigned int); };
class Rva0035A18D {
public:
    Rva0035A18D();
    ~Rva0035A18D();
    _STL::vector<BfmePod8> values;
    int state;
};
class TerrainResourceManager {
public:
	virtual void DoXfer(Xfer *xfer);
private:
	unsigned char opaque04[0x10];
	_STL::list<BfmePod12> entries; // +0x14
	float maxRadius18;
	Region3D region; // +0x1C
	int width34,height38;
	float cell3C;
	Rva0035A18D *cells40;
};
// ?DoXfer@TerrainResourceManager@@UAEXPAVXfer@@@Z
void TerrainResourceManager::DoXfer(Xfer *xfer)
{
    Xfer::Version version(1,3);
    *xfer == version;
    int count=entries.size();
    *xfer == count;
    if(xfer->IsLoading())
    {
        BfmePod12 entry;
        for(int i=0;i<count;++i)
        {
            XferObjectID(xfer,reinterpret_cast<ObjectID *>(&entry.key));
            *xfer == entry.value;
            if(version.current>=2)*xfer == entry.flag;
            entries.push_back(entry);
        }
    }
    else
    {
        for(_STL::list<BfmePod12>::iterator it=entries.begin();it._M_node!=entries.end()._M_node;++it)
        {
            BfmePod12 *entry=&*it;
            XferObjectID(xfer,reinterpret_cast<ObjectID *>(&entry->key));
            *xfer == entry->value;
            if(version.current>=2)*xfer == entry->flag;
        }
    }
    *xfer == region;
    *xfer == width34;
    *xfer == height38;
    *xfer == cell3C;
    *xfer == maxRadius18;
    int cellCount=width34*height38;
    *xfer == cellCount;
    if(xfer->IsLoading())
    {
        cells40=new Rva0035A18D[cellCount];
        for(int i=0;i<cellCount;++i)
        {
            Rva0035A18D *cell=&cells40[i];
            if(version.current>=3)
            {
                int state;
                *xfer == state;
                cell->state=state;
                int valueCount;
                *xfer == valueCount;
                reinterpret_cast<Rva0035ABC0 *>(cell)->rva0035ABC0(valueCount);
                for(int j=0;j<valueCount;++j)
                {
                    BfmePod8 *value=&cell->values[j];
                    *xfer == value->a[0];
                    XferObjectID(xfer,reinterpret_cast<ObjectID *>(&value->a[1]));
                }
            }
            else
            {
                cell->state=3;
                ObjectID id;
                XferObjectID(xfer,&id);
                reinterpret_cast<Rva0035ABC0 *>(cell)->rva0035ABC0(1);
                BfmePod8 *value=&cell->values[0];
                value->a[1]=id;
                value->a[0]=-1;
            }
        }
    }
    else
    {
        for(int i=0;i<cellCount;++i)
        {
            Rva0035A18D *cell=&cells40[i];
            int state=cell->state;
            *xfer == state;
            int valueCount=cell->values.size();
            *xfer == valueCount;
            for(BfmePod8 *value=cell->values.begin();value!=cell->values.end();++value)
            {
                *xfer == value->a[0];
                XferObjectID(xfer,reinterpret_cast<ObjectID *>(&value->a[1]));
            }
        }
    }
}

// ??0Rva0035A18D@@QAE@XZ
Rva0035A18D::Rva0035A18D() {}
// ??1Rva0035A18D@@QAE@XZ
Rva0035A18D::~Rva0035A18D() {}
