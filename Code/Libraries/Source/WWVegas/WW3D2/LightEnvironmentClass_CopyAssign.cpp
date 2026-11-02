// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// ??4LightEnvironmentClass@@QAEAAV0@ABV0@@Z
// BFME adds a leading byte before the Zero Hour light-environment layout.

#include "../WWMath/Vector3Data.h"
static __forceinline Vector3 &copyStorageVector3(Vector3 &out,const Vector3 &in) {out.X=in.X;out.Y=in.Y;out.Z=in.Z;return out;}



class LightEnvironmentClass
{
public:
	LightEnvironmentClass &operator=(const LightEnvironmentClass &that);

private:
	struct InputLightStruct
	{
		InputLightStruct &operator=(const InputLightStruct &that);

		Vector3 Direction;
		Vector3 Ambient;
		Vector3 Diffuse;
		bool DiffuseRejected;
		bool Point;
		Vector3 Center;
		float InnerRadius;
		float OuterRadius;
		Vector3 PointAmbient;
		Vector3 PointDiffuse;
	};

	struct OutputLightStruct
	{
		Vector3 Direction;
		Vector3 Diffuse;
	};

	unsigned char BfmeLeadingByte;
	int LightCount;
	Vector3 ObjectCenter;
	InputLightStruct InputLights[4];
	Vector3 OutputAmbient;
	OutputLightStruct OutputLights[4];
	InputLightStruct FillLight;
	float FillIntensity;
};

typedef char VerifyLightEnvironmentSize[
	(sizeof(LightEnvironmentClass) == 0x228) ? 1 : -1];

LightEnvironmentClass &LightEnvironmentClass::operator=(
	const LightEnvironmentClass &that)
{
	BfmeLeadingByte = that.BfmeLeadingByte;
	LightCount = that.LightCount;
	copyStorageVector3(ObjectCenter,that.ObjectCenter);
	for (int i = 0; i < 4; ++i) {
		InputLights[i] = that.InputLights[i];
	}
	copyStorageVector3(OutputAmbient,that.OutputAmbient);
	for (int i = 0; i < 4; ++i) {
		copyStorageVector3(OutputLights[i].Direction,that.OutputLights[i].Direction);
		copyStorageVector3(OutputLights[i].Diffuse,that.OutputLights[i].Diffuse);
	}
	FillLight = that.FillLight;
	FillIntensity = that.FillIntensity;
	return *this;
}
