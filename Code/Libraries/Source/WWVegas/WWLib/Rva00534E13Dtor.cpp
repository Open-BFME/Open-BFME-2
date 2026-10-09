// cl: /O1 /G7 /arch:SSE /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Constructor534ECF..534FB3 (228B): BF1 f98983a7d MapMetaDataReader_ctor
// is the semantic donor; target parser5350BA/tableC68AE8 and dtor prove
// this150B reader layout. Volatile POD extent stores and a scoped last-field
// reference preserve native store order before the camera-address LEA.
// Coord3D callbacks47A6A9/B3FD0, list280A8D and MapPlayers302C81 are owned.
// ??1Rva00534E13@@QAE@XZ, RVA 0x00534E13, size 134.
// Dtor destroying two AsciiStrings at +0x20/+0x24, Coord3D[8] at +0x3C,
// two Coord3D lists at +0xA8/+0xAC and PlayerPosition[8] at +0xB0.
// Evidence: EH states 4..0 plus tail string, PlayerPosition dtor 0x22D920,
// List_base dtors 0x4EC395, StringBase<D> dtor 0x36410, caller 0x5353E3.
#include <list>

template <class T> class StringBase
{
	friend struct AsciiString;
	void releaseBuffer();
public:
	void *m_data;
};
struct AsciiString : public StringBase<char>
{
public:
    AsciiString(){m_data=0;}
	~AsciiString() { releaseBuffer(); }
};

struct Coord3D
{
    float x, y, z;
    Coord3D();
    ~Coord3D();
};

struct PlayerPosition
{
    char m_pad[0x14];
    ~PlayerPosition();
};

struct MapPlayers
{
    MapPlayers();
    PlayerPosition items[8];
};

struct ReaderPoint {float x,y,z;};
struct ReaderRegion {ReaderPoint lo,hi;};
class Rva00534E13
{
    volatile ReaderRegion extent;
    int numPlayers;
    unsigned char multiplayer,scenarioMP;
    AsciiString m_s20;
    AsciiString m_s24;
    unsigned char official;
    unsigned timestampLo,timestampHi,filesize,crc;
    Coord3D m_arr3C[8];
    ReaderPoint camera;
    _STL::list<Coord3D, _STL::allocator<Coord3D> > m_listA8;
    _STL::list<Coord3D, _STL::allocator<Coord3D> > m_listAC;
    MapPlayers m_playersB0;
public:
    Rva00534E13();
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

Rva00534E13::Rva00534E13()
 : numPlayers(0),multiplayer(0),scenarioMP(0),official(0),filesize(0),crc(0)
{
 extent.lo.x=0.0f;extent.lo.y=0.0f;extent.lo.z=0.0f;
 extent.hi.x=0.0f;extent.hi.y=0.0f;{volatile ReaderPoint &hi=extent.hi;hi.z=0.0f;}
 timestampHi=0;timestampLo=0;
 ReaderPoint *cam=&camera;cam->x=0.0f;cam->y=0.0f;cam->z=0.0f;
 for(int i=0;i<8;++i){Coord3D &p=m_arr3C[i];p.x=0.0f;p.y=0.0f;p.z=0.0f;}
}
