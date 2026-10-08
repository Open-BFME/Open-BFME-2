// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <algorithm>

// Native00283CE7..00283D70, 137B, RET4. TerrainLogic receiver from rowed
// sibling query00283D70 and its callers. Pointer range578/57C, child584,
// stamp1910 and record key+C are measured; original member names unknown.
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00283CE7FrameView { char unknown00[0x40]; unsigned int frame; };
class Rva0027D098
{
public:
    void rva0027D098();
};
struct Rva00283CE7RecordView { char unknown00[12]; unsigned int key; };
class Rva002872BA
{
public:
    void rva0028641F(unsigned int key, Rva0027D098 *record);
};
extern Rva002872BA *TheTriggerManager;
class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;
template<int N> class Rva00283CE7Slots : public Rva00283CE7Slots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00283CE7Slots<0> {};
class Rva00283CE7GlobalView : public Rva00283CE7Slots<22>
{
public:
    virtual void slot58(unsigned int key) = 0;
};
// The worker owns pointer vectors at +4 and +10. The element meanings remain
// unresolved. Native283505 destroys the second range and rebuilds it from
// the first via same-this283114; native283CB3 erases a record before rebuild.
class Rva00283CB3
{
public:
    void rva00283CB3(Rva0027D098 *record);
    void rva00283505();
private:
    char unknown00[4];
    _STL::vector<void *> records;
    _STL::vector<void *> holders;
};
class Rva0027CE80 { public: void rva0027CE80(void); };
class Rva0027D5AD { public: void rva0027D5AD(void); };
class Rva00283002 { public: void rva00283002(void); };
class Rva002827F3 { public: void rva002827F3(void) throw(); };
class Rva0062AF7 { public: void Rva0027DA58(void); };
void Rva002E373CClear(void);
class TerrainLogic
{
public:
    virtual void reset(void);
    void rva00283CE7(unsigned int key);
private:
    char unknown00[0x574];
    Rva0027D098 **first, **last, **limit;
    Rva00283CB3 *child;
    char unknown588[0x1910 - 0x588];
    unsigned int stamp;
};

// Target 0x00283567 is the standalone TerrainLogic::reset entry (Ghidra
// boundary, two call xrefs, one vtable pointer). The name is supported by the
// retail callgraph lead and GeneralsMD's virtual TerrainLogic::reset; the
// donor body clears waypoints, bridges, and PolygonTriggers. BFME2 adds the
// cleanup below. Its ECX is the +4 secondary-base view: calls at
// 0x27CE80/0x27D5AD/0x27DA58 use ECX-4, while these fields line up with
// TerrainLogicXfer's full-object +0x568 count, +0x578 vector, +0x584 worker,
// +0x588 2500-word table, and +0x1910 state. Extra field names remain
// provisional; their accessed offsets come from retail bytes.
struct Rva00283567ResetView
{
    void *vftable;
    char pad04[0x44 - 4];
    unsigned int field48;
    char pad48[0x60 - 0x48];
    Rva00283002 triggers;
    char pad61[0x564 - 0x61];
    unsigned int numWaterToUpdate;
    char pad568[0x574 - 0x568];
    _STL::vector<void *> records;
    Rva002827F3 *worker;
    int words[1250];
    unsigned int field190c;
    char pad1910[4];
    float field1914;
};

void TerrainLogic::reset(void)
{
    Rva00283567ResetView *view = (Rva00283567ResetView *)this;
    Rva0027CE80 *fullObject = (Rva0027CE80 *)((char *)this - 4);
    fullObject->rva0027CE80();
    ((Rva0027D5AD *)fullObject)->rva0027D5AD();
    view->triggers.rva00283002();
    Rva002E373CClear();

    void **end = view->records.end();
    for (void **it = view->records.begin(); it != end; ++it)
    {
        if (*it)
            ::operator delete(*it);
    }
    view->records.clear();
    view->worker->rva002827F3();
    for (int i = 0; i < 1250; ++i)
        view->words[i] = -1;
    view->numWaterToUpdate = 0;
    view->field190c = 0;
    view->field48 = 1;
    ((Rva0062AF7 *)((char *)this - 4))->Rva0027DA58();
    view->field1914 = 0.0f;
}

void TerrainLogic::rva00283CE7(unsigned int key)
{
    stamp = reinterpret_cast<Rva00283CE7FrameView *>(TheGameLogic)->frame;
    for (Rva0027D098 **i=first; i!=last; ++i)
    {
        if (reinterpret_cast<Rva00283CE7RecordView *>(*i)->key == key)
        {
            if (TheTriggerManager)
                TheTriggerManager->rva0028641F(key, *i);
            (*i)->rva0027D098();
            break;
        }
    }
    reinterpret_cast<Rva00283CE7GlobalView *>(g_00DFF080)->slot58(key);
    Rva0027D098 **end=last;
    for (Rva0027D098 **i=first; i!=end; ++i)
    {
        if (reinterpret_cast<Rva00283CE7RecordView *>(*i)->key == key)
        {
            child->rva00283CB3(*i);
            break;
        }
    }
}

class CreateAHeroData;
namespace _STL {
template <> CreateAHeroData **find(CreateAHeroData **, CreateAHeroData **, CreateAHeroData *const&);
}
class Rva00281A06 { public: ~Rva00281A06(); };
class Rva00283114 { public: void rva00283114(void *value); };
// The pointer search folds to the existing CreateAHeroData registry provider.
// Only its pointer-equality ABI is reused; this does not identify these records
// as hero data. Reading the vector's measured first-pointer word preserves
// retail's direct memory argument rather than an extra iterator temporary.
void Rva00283CB3::rva00283CB3(Rva0027D098 *record)
{
 void **end=records.end();
 void **found=(void**)_STL::find(*(CreateAHeroData***)&records,(CreateAHeroData**)end,*(CreateAHeroData*const*)&record);
 if(found!=end) {
  records.erase(found);
  rva00283505();
 }
}
void Rva00283CB3::rva00283505()
{
 void **end=holders.end();
 for(void **i=holders.begin();i!=end;++i)
  delete (Rva00281A06*)*i;
 holders.clear();
 if(!records.empty()) {
  void **last=records.end();
  for(void **i=records.begin();i!=last;++i)
   ((Rva00283114*)this)->rva00283114(*i);
 }
}
