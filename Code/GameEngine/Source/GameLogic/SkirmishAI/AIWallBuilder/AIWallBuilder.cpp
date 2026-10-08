// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB1380A80 names AIWallBuilder::DoXfer; native4E9EA1..4E9F52 proves
// version1/1, pointer vector+C and each wall's ID at+44. Save captures the
// range and writes IDs; load resolves each ID through rowed4E99B1 and keeps
// only nonnull results. No donor source identity is asserted. The native
// append is independently rowed49B4DFCB0; its shared pointer-storage ABI is
// consumed below without identifying wall objects as ModuleData.
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
class AsciiString;
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
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(WallVersion *);
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


class ModuleData;
// Keep the real STL append definition visible: a declaration-only
// specialization changes aliasing spills in tryToStartWallProduction.
void *rva004E99B1(void *key);
struct AIWallIDView { unsigned char unknown[0x44]; unsigned int id; };
class AIWall;
class AIWallBuilder {
public: void DoXfer(Xfer *); float rva004E98B4(AIWall *);
    unsigned char canBuildAnyWall();
    void tryToStartWallProduction();
private: unsigned char m_prefix[8]; void *m_owner;
    _STL::vector<AIWallIDView*> m_walls;
};
void AIWallBuilder::DoXfer(Xfer *xfer) {
    WallVersion version(1,1);
    xfer->xferVersion(&version);
    unsigned int count=m_walls.size();
    xfer->xferUnsignedInt(&count);
    if (xfer->IsStoring()) {
        _STL::vector<AIWallIDView*>::iterator end=m_walls.end();
        for (_STL::vector<AIWallIDView*>::iterator it=m_walls.begin(); it!=end; ++it) {
            unsigned int id=static_cast<AIWallIDView*>(*it)->id;
            xfer->xferUnsignedInt(&id);
        }
    } else if (xfer->IsLoading()) {
        for (unsigned int i=0; i<count; ++i) {
            unsigned int id=-1;
            xfer->xferUnsignedInt(&id);
            void *wall=rva004E99B1(reinterpret_cast<void*>(id));
            if (wall) {
                // Native append uses the canonical pointer-vector provider. Its
                // range is three words and growth copies four-byte pointers;
                // this ABI view does not identify a wall as ModuleData.
                reinterpret_cast<_STL::vector<const ModuleData*>&>(m_walls).push_back(
                    reinterpret_cast<const ModuleData *const&>(wall));
            }
        }
    }
}

// Retail 4E98B4/42 and WB13809B0/44: member float result, unused wall
// argument and ret 4. Caller 4E9DA8 passes its builder in ECX and the selected
// wall on the stack. The prior free-stdcall spelling hid this member ABI.
// The address name remains because the original method name is unknown.
float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
extern float g_00C62800;
// g_00C62800: matched references place it at VA 0xc62800 (retail .rdata value 1.1e+02f).
float g_00C62800 = 1.1e+02f;
extern float g_00C62804;
// g_00C62804: matched references place it at VA 0xc62804 (retail .rdata value 7e+01f).
float g_00C62804 = 7e+01f;
// Retail filename at RVA862808 is preserved in full below.

float AIWallBuilder::rva004E98B4(AIWall *unused)
{
    return GetGameLogicRandomValueReal(g_00C62804, g_00C62800, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIWallBuilder\\AIWallBuilder.cpp", 0xB4);
}

// Native 4E9DA8..4E9EA1 and WB1380720 name this builder member. The
// global at E04484 is a three-word pointer range. The two eligibility calls
// precede append; selection uses inclusive random [0,size-1], file line165.
// Builder owner+8 and walls+C are independently shared with its rowed peers.
// ModuleData is only the canonical pointer-vector storage ABI; these pointers
// are walls, not ModuleData objects. The vector methods must remain visible.
// Preserve the registered data owner's RvaVector type name. Field labels
// describe its three-word storage without asserting the original typedef.
struct RvaVector { void **begin, **end, **capacity; };
extern RvaVector g_00E04484;
class Rva004EABB9 { public: bool rva004EABB9(); };
// Full native 4EB7CC/310 and WB137BE20 prove bool result and ret4 owner
// argument, on the wall selected here. Its original method name is unknown.
// Full native 4EAF18/165 and named WB137BB30 prove activate's three argument
// words and ret12. The last word is a string reference passed to StringBase::set;
// its original type spelling is retained as an opaque caller ABI here.
class AIWall {
public:
    bool rva004EB7CC(void *owner);
    void activate(void *owner, float delay, const void *name);
};
struct Rva002A8B59Data { char unknown[0x28]; };
class Rva002A8F24 { public: Rva002A8B59Data *rva002A8B59(void *); };
extern Rva002A8F24 *g_00DFEEF8;
int __cdecl GetGameLogicRandomValue(int, int, char *, int);

void AIWallBuilder::tryToStartWallProduction()
{
    if (!canBuildAnyWall()) return;
    _STL::vector<const ModuleData *> candidates;
    void **end = g_00E04484.end;
    void **it = g_00E04484.begin;
    if (it != end) do {
        const ModuleData *wall = reinterpret_cast<const ModuleData *>(*it);
        if (reinterpret_cast<Rva004EABB9 *>(const_cast<ModuleData *>(wall))->rva004EABB9()
            && reinterpret_cast<AIWall *>(const_cast<ModuleData *>(wall))->rva004EB7CC(m_owner))
            candidates.push_back(wall);
        ++it;
    } while (it != end);
    if (candidates.empty()) return;
    {
        const ModuleData *wall = candidates.size() > 1
            ? candidates[GetGameLogicRandomValue(0, candidates.size() - 1,
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIWallBuilder\\AIWallBuilder.cpp", 165)]
            : candidates[0];
        Rva002A8B59Data *def = g_00DFEEF8->rva002A8B59(m_owner);
        reinterpret_cast<AIWall *>(const_cast<ModuleData *>(wall))->activate(
            m_owner, rva004E98B4(reinterpret_cast<AIWall *>(const_cast<ModuleData *>(wall))),
            reinterpret_cast<char *>(def) + 0x28);
        reinterpret_cast<_STL::vector<const ModuleData *> &>(m_walls).push_back(wall);
    }
}

// Full native 4E98F7/186 and WB1381340/371 search a four-byte pointer
// range in groups of four, comparing each wall's key+48 through rowed
// Rva004EAB9FCmp. They return the matching iterator or the end in EAX.
// This 27-byte wrapper and WB1381310 pass an unused one-byte category
// object address. The original template/type spellings remain unknown.
void **__cdecl rva004E98F7(void **first, void **last, const void *key, void *category);
void **__cdecl rva004E99D6(void **first, void **last, const void *key)
{
    char category;
    return rva004E98F7(first, last, key, &category);
}
