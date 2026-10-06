// cl: /DNDEBUG /MD /EHsc
//
// ?Scale@HTreeClass@@QAEXM@Z,
// retail 0x00160C00 (108 bytes). Dedicated TU.
//
// Pivot-translation scaler: no-op for a 1.0 factor, otherwise multiplies
// every pivot's translation triple by the factor and folds it into
// ScaleFactor. Ported from Open-BFME-1 (Code/Libraries/Source/WWVegas/
// WW3D2/htree.cpp), whose body is the same shape including the
// `factor == 1.0f` early-out; the BFME2 adaptation is the data path:
// BFME1 round-trips each translation through Get_Translation /
// Set_Translation calls while retail scales the three floats at pivot
// +0x24 in place with SSE (the second half of the +0x14 28-byte block,
// matching the landed 0x58-byte PivotClass model: Name[16], Parent at
// +0x10, rotation-plus-translation blocks at +0x14/+0x30, Index at +0x4C).
// The loop homes the pivot address through a float pointer: spelling the
// three stores through trans[0..2] folds the +0x24 into one leading lea
// with [eax+0/4/8] stores, while three member stores (or a reference
// alone) keep the +0x24 on every memory operand.
// HTree layout repeats the BoneLookup unit: Name[16], NumPivots at +0x10,
// Pivot at +0x14, ScaleFactor at +0x18.

struct PivotClass
{
public:
	char Name[16];
	PivotClass *Parent; // +0x10
	float m_rot[4]; // +0x14
	float m_tx; // +0x24
	float m_ty; // +0x28
	float m_tz; // +0x2C
	unsigned char m_bfme30[0x58 - 0x30];
};

class HTreeClass
{
public:
	void Scale(float factor);

private:
	char Name[16];
	int NumPivots; // +0x10
	PivotClass *Pivot; // +0x14
	float ScaleFactor; // +0x18
};

// ?Scale@HTreeClass@@QAEXM@Z
void HTreeClass::Scale(float factor)
{
	if (factor == 1.0f) {
		return;
	}

	for (int i = 0; i < NumPivots; i++) {
		PivotClass &piv = Pivot[i];
		float *trans = &piv.m_tx;
		trans[0] *= factor;
		trans[1] *= factor;
		trans[2] *= factor;
	}

	ScaleFactor *= factor;
}
