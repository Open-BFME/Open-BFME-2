// ?rva000EAFA4@W3DTreeBuffer@@QAE_NHPAURva000EAFA4Coord3@@PAMPAURva000EAFA4Coord2@@2@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DTreeBuffer method at retail 0x000EAFA4 (232 bytes, ret 0x14). Open-BFME-1 twin: W3DTreeBufferRva00733E30.cpp
// (0x00733E30). BFME2 layout read from retail: 1200 records of 0xE8 at +0x5C0 (count +0x44540), 64 types of
// 0x5C at +0x44558. Address-derived identity: no semantic method name is asserted. The output copies are
// component-wise; struct assignment adds an address temporary and changes register allocation.
struct Rva000EAFA4Coord3 { float x,y,z; };
struct Rva000EAFA4Coord2 { float x,y; };
struct Rva000EAFA4Record {
    Rva000EAFA4Coord3 position;
    float scale;
    char pad10[0x30];
    int type;
    unsigned char visible;
    char pad45[0x0f];
    float radius;
    char pad58[0x28];
    int state;
    char pad84[0x64];
};
struct Rva000EAFA4Type {
    void *mesh;
    char pad04[0x20];
    Rva000EAFA4Coord2 primary[2];
    Rva000EAFA4Coord2 secondary[2];
    unsigned char textureFlags[4];
    char pad48[0x14];
};
class W3DTreeBuffer {
public:
    bool rva000EAFA4(int index, Rva000EAFA4Coord3 *position, float *radius,
        Rva000EAFA4Coord2 *primary, Rva000EAFA4Coord2 *secondary);
    char pad000[0x5c0];
    Rva000EAFA4Record records[1200];
    int count;
    char pad44544[0x44558 - 0x44544];
    Rva000EAFA4Type types[64];
};
bool W3DTreeBuffer::rva000EAFA4(int index, Rva000EAFA4Coord3 *position,
    float *radius, Rva000EAFA4Coord2 *primary, Rva000EAFA4Coord2 *secondary)
{
    if (index < count) {
        int typeIndex = records[index].type;
        if (typeIndex >= 0 && records[index].visible &&
            types[typeIndex].mesh && types[typeIndex].textureFlags[0] &&
            !records[index].state) {
            position->x = records[index].position.x;
            position->y = records[index].position.y;
            position->z = records[index].position.z;
            float value = records[index].radius * records[index].scale * 0.9f;
            if (60.0f < value) value = 60.0f;
            *radius = value;
            *primary = types[typeIndex].primary[1];
            *secondary = types[typeIndex].secondary[1];
            return true;
        }
    }
    return false;
}
