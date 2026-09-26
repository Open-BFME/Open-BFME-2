// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00534E13@@QAE@XZ, RVA 0x00534E13, size 134.
// Dtor destroying two AsciiStrings at +0x20/+0x24, Coord3D[8] at +0x3C,
// two Coord3D lists at +0xA8/+0xAC and PlayerPosition[8] at +0xB0.
// Evidence: EH states 4..0 plus tail string, PlayerPosition dtor 0x22D920,
// List_base dtors 0x4EC395, StringBase<D> dtor 0x36410, caller 0x5353E3.
#include <list>

struct AsciiString
{
    void *m_data;
    ~AsciiString();
};

struct Coord3D
{
    float x, y, z;
    ~Coord3D();
};

struct PlayerPosition
{
    char m_pad[0x14];
    ~PlayerPosition();
};

struct MapPlayers
{
    PlayerPosition items[8];
};

class Rva00534E13
{
    char m_pad0[0x20];
    AsciiString m_s20;
    AsciiString m_s24;
    char m_pad28[0x14];
    Coord3D m_arr3C[8];
    char m_pad9C[0x0C];
    _STL::list<Coord3D, _STL::allocator<Coord3D> > m_listA8;
    _STL::list<Coord3D, _STL::allocator<Coord3D> > m_listAC;
    MapPlayers m_playersB0;
public:
    ~Rva00534E13();
};

typedef char SizeCheck_AsciiString[sizeof(AsciiString) == 4 ? 1 : -1];
typedef char SizeCheck_Coord3D[sizeof(Coord3D) == 12 ? 1 : -1];
typedef char SizeCheck_PlayerPosition[sizeof(PlayerPosition) == 0x14 ? 1 : -1];
typedef char SizeCheck_List[sizeof(_STL::list<Coord3D, _STL::allocator<Coord3D> >) == 4 ? 1 : -1];
typedef char SizeCheck_Class[sizeof(Rva00534E13) == 0x150 ? 1 : -1];

Rva00534E13::~Rva00534E13()
{
}
