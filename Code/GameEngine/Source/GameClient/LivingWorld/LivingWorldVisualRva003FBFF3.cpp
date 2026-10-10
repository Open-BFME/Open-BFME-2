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
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void Set_ObjectScale(float);
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
	void rva003FC291(float scale);
private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;										// +0x08
	unsigned char m_pad0C[0x14 - 0x0C];
	RenderObjClass *m_secondaryRObj;
	unsigned char unknown18[0x7C-0x18]; Real m_requestedScale;									// +0x14
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

// Native3FC291..3FC3E4 RET4,339B and WB10715C0 copy primary transform,
// scale its3x3 by requested/object scale and set both render-object scales.
// Named createRenderObject and this helper receive the SAME unchanged this
// in native5C4DE0 and WB LivingWorldIconSubObject ctor1566710. This proves
// LivingWorldVisual ownership; the original method name remains unknown.
// The const reference materializes the genuine computed float temporary:
// native stores it at frame-4 and reloads it after the first multiply.
// TU-local established row/transform views reproduce the donor copy/Scale
// structure without defining duplicate canonical Matrix3D/Vector4 bodies.
void LivingWorldVisual::rva003FC291(float scale) {
 RenderObjClass *p=m_primaryRObj;
 if(!p)return;
 m_requestedScale=scale;
 LivingWorldVisualTransform tm=p->Get_Transform();
 const Real &extra=scale / m_primaryRObj->Get_ObjectScale();
 tm.Scale(extra);
 m_primaryRObj->Set_ObjectScale(scale);
 m_primaryRObj->Set_Transform(tm);
 if(m_secondaryRObj){m_secondaryRObj->Set_ObjectScale(scale);m_secondaryRObj->Set_Transform(tm);}
}
