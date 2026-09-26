// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??1W3DLaserDrawModuleData@@UAE@XZ, retail 0x000C9AE7, 54 bytes.
// ModuleData dtor: reinstalls the vtable 0x00BCB960, tears down the Texture
// vector at +0x2C through the rowed vector<AsciiString> dtor at 0x0002CC70,
// then restores the Snapshot base vtable 0x00BBB554 through the TU-local
// inline base dtor. Single EH state for the one vector member; frameless
// companion ctor at 0x000C9A6F proves the layout (vptr +0, vector +0x2C,
// size 0x74 per the factory at 0x00064962). Table 0x00BCB840 names the
// members; the ??_G caller at 0x000C9CC9 is the slot-0 deleting dtor. Shape
// follows the landed W3DLightDrawModuleDataDtor and W3DStreakDrawModuleDataDtor
// TUs; the own vtable resolves through the ??_7 pin at 0x00BCB960.

#include <vector>

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class W3DLaserDrawModuleData : public Snapshot
{
public:
	virtual ~W3DLaserDrawModuleData();

private:
	unsigned char m_pad04[0x2C - 4]; // +0x04
	_STL::vector<AsciiString> m_textureName; // +0x2C Texture
	unsigned char m_tail38[0x74 - 0x38]; // +0x38..+0x73
};

typedef char AsciiExtent[sizeof(AsciiString) == 4 ? 1 : -1];

W3DLaserDrawModuleData::~W3DLaserDrawModuleData()
{
}
