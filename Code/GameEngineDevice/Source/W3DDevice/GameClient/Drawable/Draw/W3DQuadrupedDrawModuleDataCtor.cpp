// cl: /O1 /GX /DNDEBUG /MD
//
// ??0W3DQuadrupedDrawModuleData@@QAE@XZ, retail 0x000651C2, 73 bytes.
// W3DQuadrupedDraw ModuleData ctor: runs the pinned W3DModelDrawModuleData
// base ctor (0xC8EEF), installs vtable 0xBC5A80, default-constructs the four
// foot-bone AsciiStrings at +0x188..+0x197 via ehvec (ctor 0x326BE6,
// dtor 0x48BA39). Layout is base 0x188 bytes plus AsciiString[4]; the table
// at 0xBCBB28 (LeftFront/RightFront/LeftRear/RightRearFootBone) proves the
// members; the factory at 0x65218 news 0x198 and is the sole caller.

class AsciiString
{
public:
	AsciiString();
	~AsciiString();

private:
	const char *m_data;
};

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();
};

class W3DQuadrupedDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DQuadrupedDrawModuleData();
	virtual ~W3DQuadrupedDrawModuleData();

private:
	// Base (shared vptr at +0x00) occupies +0x00..+0x03; its real members
	// fill +0x04..+0x187 through the pinned base ctor.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_footBones[4]; // +0x188
};

// ??0W3DQuadrupedDrawModuleData@@QAE@XZ @0x651C2
W3DQuadrupedDrawModuleData::W3DQuadrupedDrawModuleData()
{
}
