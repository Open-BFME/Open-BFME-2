// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva003FBC4D@LivingWorldVisual@@QAEXM@Z retail
// 0x003FBC4D..0x003FBD9F (338 bytes RET 4). It sits among the LivingWorldVisual
// bodies just before rva003FBFF3 (LivingWorldVisualRva003FBFF3.cpp) and works
// on the same +0x08 primary and +0x14 secondary render objects. The WB twin
// 0x01071340 (unnamed) has the same statements. No direct caller or table
// reference was found so the name stays address-qualified.
// Body: when the primary render object exists, copy its transform
// (Get_Transform: Validate_Transform slot 20 then the +0x18 matrix), take its
// +0x48 object scale times the given factor into +0x7C, scale the 3x3 columns
// of the copy by the factor, and give the new object scale (slot 93) and the
// scaled transform (Set_Transform slot 21) to the primary and, when present,
// the secondary render object.
// The row / matrix helpers use TU-local names (as in the sibling) so the
// object emits no COMDAT copies of the ledger's Vector4 / Matrix3D inline
// bodies.
typedef float Real;

class LivingWorldVisualRow
{
public:
	__forceinline LivingWorldVisualRow(const LivingWorldVisualRow &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	Real &operator[](int i) { return (&X)[i]; }
	Real X;
	Real Y;
	Real Z;
	Real W;
};

class LivingWorldVisualTransform
{
public:
	__forceinline LivingWorldVisualTransform(const LivingWorldVisualTransform &m)
		: Row0(m.Row0), Row1(m.Row1), Row2(m.Row2) {}
	LivingWorldVisualRow &operator[](int i) { return (&Row0)[i]; }
	void Scale(Real scale)
	{
		(*this)[0][0] *= scale; (*this)[1][0] *= scale; (*this)[2][0] *= scale;
		(*this)[0][1] *= scale; (*this)[1][1] *= scale; (*this)[2][1] *= scale;
		(*this)[0][2] *= scale; (*this)[1][2] *= scale; (*this)[2][2] *= scale;
	}
	LivingWorldVisualRow Row0;
	LivingWorldVisualRow Row1;
	LivingWorldVisualRow Row2;
};

class RenderObjClass
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
#undef V
	virtual void Validate_Transform() const;							// slot 20
	virtual void Set_Transform(const LivingWorldVisualTransform &m);	// slot 21
#define V(n) virtual void slot##n();
	V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92)
#undef V
	virtual void Set_ObjectScale(Real scale);							// slot 93
	const LivingWorldVisualTransform &Get_Transform() const { Validate_Transform(); return Transform; }
	const Real Get_ObjectScale() const { return ObjectScale; }
private:
	unsigned char m_pad04[0x18 - 0x04];
	LivingWorldVisualTransform Transform;								// +0x18
	Real ObjectScale;													// +0x48
};

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);
	void rva003FBC4D(Real scale);
private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;										// +0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	RenderObjClass *m_secondaryRObj;									// +0x14
	unsigned char m_pad18[0x7C - 0x18];
	Real m_scale;														// +0x7C
};

void LivingWorldVisual::rva003FBC4D(Real scale)
{
	if (m_primaryRObj)
	{
		LivingWorldVisualTransform tm = m_primaryRObj->Get_Transform();
		Real objectScale = m_primaryRObj->Get_ObjectScale() * scale;
		m_scale = objectScale;
		tm.Scale(scale);
		m_primaryRObj->Set_ObjectScale(objectScale);
		m_primaryRObj->Set_Transform(tm);
		if (m_secondaryRObj)
		{
			m_secondaryRObj->Set_ObjectScale(objectScale);
			m_secondaryRObj->Set_Transform(tm);
		}
	}
}
