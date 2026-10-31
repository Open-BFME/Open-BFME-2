// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// W3DTreeBuffer method at retail 0x000EA327 (358 bytes, ret 0x14): moves the tree record of a drawable key to a new
// position and transform and rebuilds its bounding sphere from the type. Open-BFME-1 twin:
// W3DTreeBufferRva00733000.cpp (0x00733000). BFME2 layout read from retail: 1200 records of 0xE8 at +0x5C0
// (count +0x44540, changed byte +0x44544), 64 types of 0x5C at +0x44558. Opaque identity.
#include "matrix3d.h"
#include "sphere.h"

#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"

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

typedef int Int;
typedef float Real;

struct Rva000EA327Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    void *key;
    unsigned char reserved5c[0x8c];
};

struct Rva000EA327Type
{
    unsigned char reserved00[0x10];
    SphereClass bounds;
    unsigned char reserved20[0x3c];
};

// This method's native record and type views over the canonical tree records.
struct Rva000EA327BufferView
{
    unsigned char reserved000[0x5c0];
    Rva000EA327Record records[1200];
    Int count;
    unsigned char reserved44544[0x44558 - 0x44544];
    Rva000EA327Type types[64];
};

char W3DTreeBuffer::rva000EA327(void *key, Vector3 position,
    const Matrix3D *transform)
{
    for (Int index = 0; index < m_count; ++index)
    {
        if (((Rva000EA327BufferView *)this)->records[index].key == key)
        {
            ((Rva000EA327BufferView *)this)->records[index].position = position;
            ((Rva000EA327BufferView *)this)->records[index].transform = *transform;

            Rva000EA327Type *type = ((Rva000EA327BufferView *)this)->types + ((Rva000EA327BufferView *)this)->records[index].type;
            ((Rva000EA327BufferView *)this)->records[index].bounds = type->bounds;
            Real scale = ((Rva000EA327BufferView *)this)->records[index].scale;
            ((Rva000EA327BufferView *)this)->records[index].bounds.Center *= scale;
            ((Rva000EA327BufferView *)this)->records[index].bounds.Radius *= ((Rva000EA327BufferView *)this)->records[index].scale;
            ((Rva000EA327BufferView *)this)->records[index].bounds.Center += ((Rva000EA327BufferView *)this)->records[index].position;

            m_anythingChanged = 1;
            return 1;
        }
    }
    return 0;
}
