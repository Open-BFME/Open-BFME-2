// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva003FBFF3@LivingWorldVisual@@QAEXABVMatrix3D@@@Z retail
// 0x003FBFF3..0x003FC149 (342 bytes RET 4). It sits among the LivingWorldVisual
// bodies (setHouseColor 0x003FB602 / createPickboxObject 0x003FC74A) and works
// on the same +0x08 primary render object. The WB twin 0x010702E0 (unnamed)
// has the same inline shape. No direct caller or table reference was found,
// so the name stays address-qualified.
// Body: when the primary render object exists, take the rotation of the
// given transform (rowed Matrix3 ctor 0x00716890). Copy the object's
// transform (Get_Transform: Validate_Transform slot 20 then the +0x18 matrix)
// and put the rotation in it (rowed Matrix3D::Set_Rotation 0x00711EF0).
// Re-apply the object's +0x48 scale to the 3x3 columns. Then Set_Transform
// (slot 21) on the primary and, when present, the +0x14 render object.
// The row / matrix helpers use TU-local names so the object emits no COMDAT
// copies of the ledger's Vector4 / Matrix3D inline bodies.
typedef float Real;

class Matrix3D;

class Matrix3
{
public:
	Matrix3(const Matrix3D &m);
private:
	Real m_rows[9];
};

class Matrix3D
{
public:
	void Set_Rotation(const Matrix3 &m);
};

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
	void rva003FBFF3(const Matrix3D &transform);
private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;										// +0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	RenderObjClass *m_secondaryRObj;									// +0x14
};

void LivingWorldVisual::rva003FBFF3(const Matrix3D &transform)
{
	if (m_primaryRObj)
	{
		Matrix3 rotation(transform);
		LivingWorldVisualTransform tm = m_primaryRObj->Get_Transform();
		reinterpret_cast<Matrix3D *>(&tm)->Set_Rotation(rotation);
		tm.Scale(m_primaryRObj->Get_ObjectScale());
		m_primaryRObj->Set_Transform(tm);
		if (m_secondaryRObj)
			m_secondaryRObj->Set_Transform(tm);
	}
}
