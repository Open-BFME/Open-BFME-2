// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB1380A80 names AIWallBuilder::DoXfer; native4E9EA1..4E9F52 proves
// version1/1, pointer vector+C and each wall's ID at+44. Save captures the
// range and writes IDs; load resolves each ID through rowed4E99B1 and keeps
// only nonnull results. No donor source identity is asserted. The native
// append is independently rowed49B4DFCB0; its shared pointer-storage ABI is
// consumed below without identifying wall objects as ModuleData.
#include <vector>
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
namespace _STL {template<>void vector<const ModuleData*>::push_back(const ModuleData *const&);}
void *rva004E99B1(void *key);
struct AIWallIDView { unsigned char unknown[0x44]; unsigned int id; };
class AIWallBuilder {
public: void DoXfer(Xfer *);
private: unsigned char m_prefix[0x0c]; _STL::vector<AIWallIDView*> m_walls;
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

// ?Rva004E98B4Get@@YGMH@Z @0x004E98B4 42B free stdcall float Get(int unused) wraps rowed GetGameLogicRandomValueReal 0x00234092 with globals file-line 180 caller 0x004E9DA8
float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
extern float g_00C62800;
// g_00C62800: matched references place it at VA 0xc62800 (retail .rdata value 1.1e+02f).
float g_00C62800 = 1.1e+02f;
extern float g_00C62804;
// g_00C62804: matched references place it at VA 0xc62804 (retail .rdata value 7e+01f).
float g_00C62804 = 7e+01f;
// Retail filename at RVA862808 is preserved in full below.

float __stdcall Rva004E98B4Get(int unused)
{
    return GetGameLogicRandomValueReal(g_00C62804, g_00C62800, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIWallBuilder\\AIWallBuilder.cpp", 0xB4);
}
