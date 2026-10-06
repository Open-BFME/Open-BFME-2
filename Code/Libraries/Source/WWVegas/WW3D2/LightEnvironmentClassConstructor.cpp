// cl: /DNDEBUG /MD /EHsc
// Donor: BFME1 LightEnvironmentClassConstructor.cpp at 0x0094AAF0.
// Target: 0x0013F410/523B; layout agrees with matched assignment 0x0014A230
// and DX8Wrapper::Set_Light_Environment at 0x00122EA0. The donor helper
// type names describe the observed initialization; /G7 /arch:SSE matches retail.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

struct LightEnvironmentVector3
{
	float x, y, z;
	LightEnvironmentVector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
};

struct LightEnvironmentZeroFloat
{
	float value;
	LightEnvironmentZeroFloat() : value( 0.0f ) {}
};

struct LightEnvironmentInputLight
{
	LightEnvironmentVector3 direction;
	LightEnvironmentVector3 ambient;
	LightEnvironmentVector3 diffuse;
	bool diffuseRejected;
	bool point;
	LightEnvironmentVector3 center;
	LightEnvironmentZeroFloat innerRadius;
	LightEnvironmentZeroFloat outerRadius;
	LightEnvironmentVector3 pointAmbient;
	LightEnvironmentVector3 pointDiffuse;
	LightEnvironmentInputLight() : diffuseRejected( false ), point( false ) {}
};

struct LightEnvironmentOutputLight
{
	LightEnvironmentVector3 direction;
	LightEnvironmentVector3 diffuse;
};

class LightEnvironmentPrefix
{
protected:
	unsigned char prefix;
	unsigned char padding[3];
	int lightCount;
	LightEnvironmentVector3 objectCenter;
	LightEnvironmentPrefix() : prefix( 0 ), lightCount( 0 ) {}
};

class LightEnvironmentClass : public LightEnvironmentPrefix
{
public:
	LightEnvironmentClass();

private:
	LightEnvironmentInputLight inputLights[4];
	LightEnvironmentVector3 outputAmbient;
	LightEnvironmentOutputLight outputLights[4];
	LightEnvironmentInputLight fillLight;
	float fillIntensity;
};

LightEnvironmentClass::LightEnvironmentClass()
	: LightEnvironmentPrefix(), fillIntensity( 0.0f )
{
}
