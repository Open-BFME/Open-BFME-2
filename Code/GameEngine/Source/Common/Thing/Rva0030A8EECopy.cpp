// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0030A8EE@Rva0030A8EE@@QAEXPAVCoord3D@@@Z @0x0030A8EE 62B
// Unlock 5: builds Coord3D from this+8/+0x18/+0x28 via movss, block-copies
// to out via 3x movsd, normalizes out via rowed 0x00005A70. Callers UNCLAIMED.
// Evidence: movss/movsd/fstp shape; SSE flags from next Rva0030A92C.
struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord3D : public Coord3DBase
{
public:
    float Normalize();
};

struct Rva0030A8EE
{
    void rva0030A8EE(Coord3D *out);
private:
    unsigned char m_pad00[8];
    float m_08;
    unsigned char m_pad0C[12];
    float m_18;
    unsigned char m_pad1C[12];
    float m_28;
};

void Rva0030A8EE::rva0030A8EE(Coord3D *out)
{
    Coord3D tmp;
    tmp.x = m_08;
    tmp.y = m_18;
    tmp.z = m_28;
    *out = tmp;
    out->Normalize();
}
