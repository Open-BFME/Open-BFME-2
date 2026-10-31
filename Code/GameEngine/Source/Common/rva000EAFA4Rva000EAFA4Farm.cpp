// ?rva000EAFA4@W3DTreeBuffer@@QAE_NHPAURva000EAFA4Coord3@@PAMPAURva000EAFA4Coord2@@2@Z
// ?rva000EAFA4@W3DTreeBuffer@@QAE_NHPAURva000EAFA4Coord3@@PAMPAURva000EAFA4Coord2@@2@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h"
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeTypeRecord.h"

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class TextureClass;

template <class T> class RefCountPtr;

template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

struct TTree;

class Xfer;
struct Rva000EAFA4Coord3;
struct Rva000EAFA4Coord2;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
	virtual void xfer(Xfer *xfer);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_anythingChanged;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_changed;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_initialized;
private:
	unsigned char m_44555;
private:
	unsigned char m_needUpdate;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
	char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);
	bool rva000EAFA4(int index, Rva000EAFA4Coord3 *position, float *radius, Rva000EAFA4Coord2 *primary,
		Rva000EAFA4Coord2 *secondary);
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
};
// This method's native record and type views over the canonical tree records.
struct Rva000EAFA4BufferView {
    char pad000[0x5c0];
    Rva000EAFA4Record records[1200];
    int count;
    char pad44544[0x44558 - 0x44544];
    Rva000EAFA4Type types[64];
};
bool W3DTreeBuffer::rva000EAFA4(int index, Rva000EAFA4Coord3 *position,
    float *radius, Rva000EAFA4Coord2 *primary, Rva000EAFA4Coord2 *secondary)
{
    if (index >= m_count) {
        return false;
    }
    int typeIndex = ((Rva000EAFA4BufferView *)this)->records[index].type;
    if (typeIndex < 0 || !((Rva000EAFA4BufferView *)this)->records[index].visible ||
        !((Rva000EAFA4BufferView *)this)->types[typeIndex].mesh || !((Rva000EAFA4BufferView *)this)->types[typeIndex].textureFlags[0] ||
        ((Rva000EAFA4BufferView *)this)->records[index].state) {
        return false;
    }
    float *pos = &((Rva000EAFA4BufferView *)this)->records[index].position.x;
    position->x = pos[0];
    position->y = pos[1];
    position->z = pos[2];
    float value = ((Rva000EAFA4BufferView *)this)->records[index].radius * ((Rva000EAFA4BufferView *)this)->records[index].scale * 0.9f;
    if (60.0f < value) value = 60.0f;
    *radius = value;
    *primary = ((Rva000EAFA4BufferView *)this)->types[typeIndex].primary[1];
    _ReadWriteBarrier();
    *secondary = ((Rva000EAFA4BufferView *)this)->types[typeIndex].secondary[1];
    return true;
}
