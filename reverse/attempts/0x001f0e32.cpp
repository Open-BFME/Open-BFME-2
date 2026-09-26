// ??0GenericObjectCreationNugget@@QAE@XZ
// partial score=0.99 date=2026-09-26
// cl: /O1 /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GenericObjectCreationNugget@@QAE@XZ, retail 0x001F0E32, 478 bytes.
// GenericObjectCreationNugget default ctor: installs vtable 0x00BE1160
// (slot0 is the rowed ??_G at 0x001F31AA), builds the two 16-byte-element
// vectors (+0x04/+0x14) and the two tail vectors (+0x114/+0x120) through
// the rowed E16 Vector_base at 0x00211E58, initializes the two name
// strings (+0x10/+0x24) from the empty-string global through the pinned
// StringBase<char> copy ctor at 0x000365F0, zeroes the offset in the body
// via RetailCoord3D::zero (the three late movss stores), and constructs
// the +0xB4 condition member through the rowed Rva0042526Member at
// 0x00042526. Total size 0x12C matches the parseObject `push 0x12C` and
// the sibling dtor TU's static assert.
//
// Identity: symbols.csv pin (BFME1-attested QAE mangling, called by
// parseObject new at 0x1F311B); the sibling dtor TU
// (GenericObjectCreationNuggetDtor.cpp) proves the member map
// (AsciiString vectors at +0x04/+0x114/+0x120, AnimSet vector at +0x14,
// AsciiStrings at +0x10/+0x24/+0x108/+0x10C, pool handle at +0x7C, B4
// memset region, m_nameAreObjects at +0xA8). Scalar names follow the
// Open-BFME-1 donor
// (Code/GameEngine/Source/GameLogic/Object/
// GenericObjectCreationNuggetConstructor.cpp) where offsets and values
// agree; BFME2-only tail fields keep descriptive TU-local names.
//
// Schedule (all probe-proven in build/probe_nug, P7): the dtorful,
// trivially-constructed ObjectCreationNugget base shifts the EH states to
// retail's 0/1/3 (a baseless probe numbers them 0/2); the vector base
// calls stay out-of-line and arm no states; the Rva member (trivial dtor)
// arms none; the string constructions arm states 1 and 3 through an
// inline AsciiString forwarder so the member-inits call the pinned base
// copy directly. The allocator temp is the shared one-byte stack slot.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

template <class T>
class StringBase
{
	friend class AsciiString;

protected:
	StringBase() {}

private:
	StringBase(const StringBase<T> &);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();

private:
	char *m_text;
};

extern const AsciiString TheEmptyString;

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

struct RetailCoord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class Rva0042526Member
{
public:
	Rva0042526Member() throw();

private:
	unsigned char m_pad[0x4C];
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	GenericObjectCreationNugget();

protected:
	virtual ~GenericObjectCreationNugget();

private:
	_STL::vector<BfmeE16> m_names; // +0x04 (dtor TU: AsciiString elements)
	AsciiString m_putInContainer; // +0x10
	_STL::vector<BfmeE16> m_animSets; // +0x14 (dtor TU: AnimSet elements)
	void *m_fxFinal; // +0x20
	AsciiString m_particleSysName; // +0x24
	int m_debrisToGenerate; // +0x28
	float m_mass; // +0x2C
	float m_extraBounciness; // +0x30
	RetailCoord3D m_offset; // +0x34 (body-zeroed)
	int m_disposition; // +0x40
	float m_dispositionIntensity; // +0x44
	float m_spinRate; // +0x48
	float m_yawRate; // +0x4C
	float m_rollRate; // +0x50
	float m_pitchRate; // +0x54
	float m_minPitch; // +0x58
	float m_maxPitch; // +0x5C
	int m_minFrames; // +0x60
	int m_maxFrames; // +0x64
	int m_shadowType; // +0x68
	int m_unk6C; // +0x6C
	float m_minHealth; // +0x70
	float m_maxHealth; // +0x74
	int m_fadeFrames; // +0x78
	void *m_poolHandle; // +0x7C (dtor TU: NullablePoolHandle)
	float m_unk80; // +0x80
	float m_unk84; // +0x84
	float m_unk88; // +0x88
	int m_unk8C; // +0x8C
	bool m_flag90; // +0x90
	bool m_flag91; // +0x91
	bool m_flag92; // +0x92
	bool m_flag93; // +0x93
	bool m_flag94; // +0x94
	int m_unk98; // +0x98
	bool m_flag9C; // +0x9C
	bool m_flag9D; // +0x9D
	bool m_flag9E; // +0x9E
	bool m_flag9F; // +0x9F
	bool m_flagA0; // +0xA0
	int m_unkA4; // +0xA4
	bool m_nameAreObjects; // +0xA8 (parseObject-proven name)
	bool m_flagA9; // +0xA9
	bool m_flagAA; // +0xAA
	bool m_flagAB; // +0xAB
	bool m_flagAC; // +0xAC
	bool m_flagAD; // +0xAD
	bool m_flagAE; // +0xAE
	bool m_flagAF; // +0xAF
	int m_unkB0; // +0xB0
	Rva0042526Member m_condition; // +0xB4
	bool m_flag100; // +0x100
	bool m_flag101; // +0x101
	bool m_flag102; // +0x102
	bool m_flag103; // +0x103
	float m_unk104; // +0x104
	AsciiString m_unk108; // +0x108 (inline-empty default: zero store, no call)
	AsciiString m_unk10C; // +0x10C (inline-empty default: zero store, no call)
	unsigned char m_pad110; // +0x110
	unsigned char m_pad111; // +0x111
	_STL::vector<BfmeE16> m_tailVec114; // +0x114
	_STL::vector<BfmeE16> m_tailVec120; // +0x120
};

// ??0GenericObjectCreationNugget@@QAE@XZ @0x001F0E32
GenericObjectCreationNugget::GenericObjectCreationNugget()
	: m_putInContainer(TheEmptyString)
	, m_fxFinal(0)
	, m_particleSysName(TheEmptyString)
	, m_debrisToGenerate(1)
	, m_mass(0.0f)
	, m_extraBounciness(0.0f)
	, m_disposition(2)
	, m_dispositionIntensity(0.0f)
	, m_spinRate(0.0f)
	, m_yawRate(1.0f)
	, m_rollRate(0.0f)
	, m_pitchRate(0.0f)
	, m_minPitch(0.0f)
	, m_maxPitch(0.0f)
	, m_minFrames(0)
	, m_maxFrames(0)
	, m_shadowType(0)
	, m_unk6C(0)
	, m_minHealth(1.0f)
	, m_maxHealth(1.0f)
	, m_fadeFrames(0)
	, m_poolHandle(0)
	, m_unk80(0.0f)
	, m_unk84(0.0f)
	, m_unk88(0.0f)
	, m_unk8C(0)
	, m_flag90(false)
	, m_flag91(false)
	, m_flag92(false)
	, m_flag93(false)
	, m_flag94(false)
	, m_unk98(1)
	, m_flag9C(false)
	, m_flag9D(true)
	, m_flag9E(false)
	, m_flag9F(false)
	, m_flagA0(false)
	, m_unkA4(0)
	, m_nameAreObjects(true)
	, m_flagA9(false)
	, m_flagAA(false)
	, m_flagAB(false)
	, m_flagAC(false)
	, m_flagAD(false)
	, m_flagAE(false)
	, m_flagAF(false)
	, m_unkB0(0)
	, m_condition()
	, m_flag100(true)
	, m_flag101(false)
	, m_flag102(false)
	, m_flag103(false)
	, m_unk104(0.0f)
	, m_pad110(0)
	, m_pad111(0)
	, m_tailVec114()
	, m_tailVec120()
{
	m_offset.x = 0.0f;
	m_offset.y = 0.0f;
	m_offset.z = 0.0f;
}
