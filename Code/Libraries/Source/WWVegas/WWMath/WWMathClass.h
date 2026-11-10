// WWMath: canonical declarations for the members 28 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_WWMATH_H
#define CANONICAL_WWMATH_H

class WWMath
{
public:
	static float Cos(float);
	static float Fast_Sin(float);
	static int Float_To_Int_Floor(const float &);
	static void Init();
	static float __fastcall Inv_Sqrt(float val);
	static float Max(float a, float b);
	static float Min(float a, float b);
	static float Random_Float();
	static void Shutdown();
	static float Sin(float);
};

#endif // CANONICAL_WWMATH_H
