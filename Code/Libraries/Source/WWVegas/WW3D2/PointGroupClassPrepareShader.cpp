// cl: /DNDEBUG /MD /EHsc
// PointGroupClass shader-prep, retail 0x00179180 (108 bytes). BFME1 port of
// PointGroupClassPrepareShader.cpp (their 0x00912E60, 153 bytes, x87): disable
// the extra cull bit, then set primary gradient from the 0.9961 (254/255)
// white-opaque test and texturing from the Texture pointer. Layout matches the
// matched ctor (PointDiffuse +8, Texture +0x24, ShaderBits +0x28,
// DefaultPointColor +0x38, DefaultPointAlpha +0x44).
//
// Codegen notes (all retail-measured): the gradient-clear spells through the
// second byte so MSVC keeps the single read-modify-write `and byte [ecx+29]`;
// the modulate arm reads through a reference so its load stays inside the
// else (`mov eax` + `and ah`/`or ah` + store) instead of hoisting above the
// float compares (which would also spill the bool from al to dl).

class Vector3
{
public:
	float X, Y, Z;
};

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
class PointGroupClass
{
public:
	void prepare_shader(void);

private:
	virtual void abstract_dtor(void);
	void *PointLoc;
	void *PointDiffuse;
	void *APT;
	void *PointSize;
	void *PointOrientation;
	void *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	void *Texture;
	unsigned int ShaderBits;
	int PointMode;
	unsigned int Flags;
	float DefaultPointSize;
	Vector3 DefaultPointColor;
	float DefaultPointAlpha;
};

// ?prepare_shader@PointGroupClass@@QAEXXZ
void PointGroupClass::prepare_shader(void)
{
	ShaderBits &= ~0x100000u;

	float value_255 = 0.9961f;
	bool default_white_opaque = (DefaultPointColor.X > value_255 &&
		DefaultPointColor.Y > value_255 &&
		DefaultPointColor.Z > value_255 &&
		DefaultPointAlpha > value_255);

	if (!PointDiffuse && default_white_opaque && Texture) {
		((unsigned char *)&ShaderBits)[1] &= (unsigned char)~0x1Cu;
	} else {
		unsigned int &shaderBits = ShaderBits;
		shaderBits = (shaderBits & ~0x400u) | 0x1800u;
	}

	if (Texture) {
		ShaderBits |= 0x10000u;
	} else {
		ShaderBits &= ~0x10000u;
	}
}
