// cl: /O2 /arch:SSE2 /MD
//
// LineGroupClass default ctor, retail 0x001B3490, 114 bytes.
// Dedicated TU so linegrp.cpp keeps its other bodies.

class ShaderClass
{
public:
	static ShaderClass _PresetAdditiveSpriteShader;
	unsigned ShaderBits;
};

class LineGroupClass
{
public:
	LineGroupClass();
	virtual ~LineGroupClass();

private:
	void *StartLineLoc;
	void *EndLineLoc;
	void *LineDiffuse;
	void *TailDiffuse;
	void *ALT;
	void *LineSize;
	void *LineUCoord;
	int LineCount;
	void *Texture;
	unsigned ShaderBits;
	unsigned Flags;
	float DefaultLineSize;
	float DefaultLineColorX;
	float DefaultLineColorY;
	float DefaultLineColorZ;
	float DefaultLineAlpha;
	float DefaultLineUCoord;
	float DefaultTailDiffuseX;
	float DefaultTailDiffuseY;
	float DefaultTailDiffuseZ;
	float DefaultTailDiffuseW;
	int LineMode;
};

LineGroupClass::LineGroupClass() :
	StartLineLoc(0),
	EndLineLoc(0),
	LineDiffuse(0),
	TailDiffuse(0),
	ALT(0),
	LineSize(0),
	LineUCoord(0),
	LineCount(0),
	Texture(0),
	ShaderBits(ShaderClass::_PresetAdditiveSpriteShader.ShaderBits),
	Flags(0),
	DefaultLineSize(0.0f),
	DefaultLineColorX(1.0f),
	DefaultLineColorY(1.0f),
	DefaultLineColorZ(1.0f),
	DefaultLineAlpha(1.0f),
	DefaultLineUCoord(0.0f),
	DefaultTailDiffuseX(0.0f),
	DefaultTailDiffuseY(0.0f),
	DefaultTailDiffuseZ(0.0f),
	DefaultTailDiffuseW(0.0f),
	LineMode(0)
{
}
