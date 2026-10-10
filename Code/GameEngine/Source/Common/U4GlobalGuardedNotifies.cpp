// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native3FC149..3FC291 RET4,328B; WB10705B0 has the same transform
// copy, Set_Rotation711EF0, scale and virtual21 calls. Sole known direct
// native caller is the existing guarded wrapper3F935A,20B. Retain its
// established neutral U4Target0060C2C0::hand(void*) ABI/name; original class
// and method identity remain unknown. Payload is read as the evidenced
// Matrix3 reference; render-object views use target slots20/21 and offsets.
// Genuine row/transform copy and column Scale structure are shared with
// the verified LivingWorldVisual transform-family source. Scalar factor
// by value reproduces full328B including retail's first MOVSS/MULSS pair.
// No aliases, extra pins, canonical math definitions or assembly added.
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

class U4Target0060C2C0
{
public:
	void hand( void *payload );
private:
 unsigned char unknown0[8]; RenderObjClass *primary; unsigned char unknownC[8]; RenderObjClass *secondary;
};

void __stdcall u4Guarded0060C2C0( U4Target0060C2C0 *target, void *payload )
{
	if ( target != 0 )
		target->hand( payload );
}

void U4Target0060C2C0::hand(void *payload) {
 if(primary){
 LivingWorldVisualTransform tm=primary->Get_Transform();
 reinterpret_cast<Matrix3D*>(&tm)->Set_Rotation(*static_cast<const Matrix3*>(payload));
 Real factor=primary->Get_ObjectScale();
 tm.Scale(factor);
 primary->Set_Transform(tm);
 if(secondary)secondary->Set_Transform(tm);
 }
}
