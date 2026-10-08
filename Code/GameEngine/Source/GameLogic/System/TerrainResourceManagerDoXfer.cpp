// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB E62590 identifies TerrainResourceManager::DoXfer and its vtable context.
// Native35ABE0..35AEBB proves list14, flags18/3C, origin1C, dimensions34/38
// and 16-byte cell array40. BF1 ba7ddda and ZH contain no clean matching
// manager unit. Payloads retain the existing providers' provisional names:
// BfmePod12 carries ID/bool/float; BfmePod8 carries int/ObjectID bits.
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
enum ObjectID { INVALID_ID = 0 };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct XferVersion { XferVersion(unsigned char low,unsigned char high):version(low),current(high){} unsigned char version,current; };
class Xfer {
public:
virtual void slot00();
virtual bool IsLoading() const;
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void xferVersion(XferVersion *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void xferCoord3D(Coord3D *);
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void xferBool(bool *);
virtual void slot29();
virtual void slot30();
virtual void xferInt(int *);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void xferFloat(float *);
};
void XferObjectID(Xfer *, ObjectID *);
struct BfmePod12 { ObjectID id; bool active; char pad[3]; float value; };
struct BfmePod8 { int a[2]; };
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
    virtual void DoXfer(Xfer *);
    unsigned char opaque04[0x10];
    _STL::list<BfmePod12> entries;
    bool flag18;
    Coord3D origin;
    unsigned char opaque28[0x34-0x28];
    int width,height;
    bool flag3C;
    Rva0035A18D *cells;
};
// ?DoXfer@TerrainResourceManager@@UAEXPAVXfer@@@Z
void TerrainResourceManager::DoXfer(Xfer *xfer)
{
    XferVersion version(1,3);
    xfer->xferVersion(&version);
    int count=entries.size();
    xfer->xferInt(&count);
    if(xfer->IsLoading())
    {
        BfmePod12 entry;
        for(int i=0;i<count;++i)
        {
            XferObjectID(xfer,&entry.id);
            xfer->xferBool(&entry.active);
            if(version.current>=2)xfer->xferFloat(&entry.value);
            entries.push_back(entry);
        }
    }
    else
    {
        for(_STL::list<BfmePod12>::iterator it=entries.begin();it._M_node!=entries.end()._M_node;++it)
        {
            BfmePod12 *entry=&*it;
            XferObjectID(xfer,&entry->id);
            xfer->xferBool(&entry->active);
            if(version.current>=2)xfer->xferFloat(&entry->value);
        }
    }
    xfer->xferCoord3D(&origin);
    xfer->xferInt(&width);
    xfer->xferInt(&height);
    xfer->xferBool(&flag3C);
    xfer->xferBool(&flag18);
    int cellCount=width*height;
    xfer->xferInt(&cellCount);
    if(xfer->IsLoading())
    {
        cells=new Rva0035A18D[cellCount];
        for(int i=0;i<cellCount;++i)
        {
            Rva0035A18D *cell=&cells[i];
            if(version.current>=3)
            {
                int state;
                xfer->xferInt(&state);
                cell->state=state;
                int valueCount;
                xfer->xferInt(&valueCount);
                reinterpret_cast<Rva0035ABC0 *>(cell)->rva0035ABC0(valueCount);
                for(int j=0;j<valueCount;++j)
                {
                    BfmePod8 *value=&cell->values[j];
                    xfer->xferInt(&value->a[0]);
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
            Rva0035A18D *cell=&cells[i];
            int state=cell->state;
            xfer->xferInt(&state);
            int valueCount=cell->values.size();
            xfer->xferInt(&valueCount);
            for(BfmePod8 *value=cell->values.begin();value!=cell->values.end();++value)
            {
                xfer->xferInt(&value->a[0]);
                XferObjectID(xfer,reinterpret_cast<ObjectID *>(&value->a[1]));
            }
        }
    }
}

// ??0Rva0035A18D@@QAE@XZ
Rva0035A18D::Rva0035A18D() {}
// ??1Rva0035A18D@@QAE@XZ
Rva0035A18D::~Rva0035A18D() {}
