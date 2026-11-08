// cl: /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// 0x00162290 (18 bytes, padded to 0x001622B0): the pivot index of the first
// captured bone, or -1 when none is captured. Its callers are the BFME 2
// update loops, which seed their sweep with it and continue with the value
// returned by the pinned HTreeClass::Capture_Update (0x001622B0). The
// captured bones are the sorted 36-byte records at +0x1C that
// htree_control.cpp's Control_Bone and Is_Bone_Captured search, held in a
// real STLport vector: retail reloads +0x1C for front() after empty(), which
// only the vector's own inline accessors reproduce. The method name is
// address-derived; no image names it.
//
// 0x001628A0 (769 bytes): HTreeClass::Base_Update, ZH htree.cpp's root-down
// pivot sweep over BFME 2's compact quaternion/translation pivots (0x58-byte
// PivotClass: Parent +0x10, BaseTransform +0x14, Transform +0x30, IsVisible
// +0x50, PivotFade +0x54). Shape from WorldBuilder HTreeClass::Base_Update
// (0x00A164F0, htree.cpp:498): the root goes through the transform's
// Matrix3D assignment (Build_Quaternion, then Get_Translation), the sweep is
// seeded by the first-captured accessor above (WB calls it, retail inlines
// it), and each pivot calls a static cdecl Multiply(parent, base, &result)
// that rotates base's translation by the parent quaternion, adds the parent
// translation, then multiplies the quaternions through WWMath's by-value
// operator* (WB 0x0071C0E0). cl orders the products' commutative operands
// by its own temporaries, so the accessor call and the verbatim WWMath
// operator* grouping are both needed for retail's operand order.
//
// 0x001622B0 (1335 bytes): HTreeClass::Capture_Update(pivot_index), BFME 2's
// captured-pivot step, named after its pin; WorldBuilder calls it
// HTreeClass::UpdateCapturedPivotAndAdvance (0x00A18C60, htree.cpp:1676-1682,
// whose asserts name CapturedPivots and PivotIndex). It finds pivot_index in
// the sorted capture records ({PivotIndex, CompactTransform, world-space
// flag}), post-multiplies the pivot's transform by the captured one (WB
// 0x00A16A90: rotate the captured translation, add it, then quat.h's
// Quaternion::PostMultiply, WB 0x00A16AE0), or for a world-space capture by
// a rotation-only CompactTransform(Q, Vector3(0,0,0)) followed by adding the
// translation unrotated, and returns the next captured pivot index or -1.
// Retail inlines every helper, as WWINLINE's __forceinline does.
//
// 0x00165820 (2277 bytes): HTreeClass::Combo_Update, ZH htree.cpp's combo
// sweep in its own loop shape (a function-scope anim_num for the pivot-count
// MIN, a separate one in the weighting loop that the visibility loop
// reuses) over the compact pivots: each animated pivot accumulates the
// weighted translations, slerps the orientations through BFME 2's
// normalized lerp (an identity when Get_Orientation reports none), then
// post-multiplies CompactTransform(q0, trans) and averages the visited
// animations' fades. WorldBuilder's twin is 0x00A17D10. Captured pivots go
// through the seeded Capture_Update chain above.
//
// 0x001645B0 (4715 bytes): HTreeClass::Blend_Update, BFME 2's two-animation
// blend in WorldBuilder's shape (0x00A173C0, htree.cpp:893-970). A
// compressed motion0 (Get_Class_ID() == 1) with node channels takes the fast
// path: the motion-cache check at 0x00160FC0 (HTreeClass::rva00160FC0),
// the nodes' X/Y/Z/Q/Fade channels read inline through the
// shared channel cache, then return. Any other pair clears the cached motion
// and blends through the HAnimClass virtuals. As in WB, the generic path's
// locals (its CompactTransform after the first-captured seed) follow the fast
// block at function scope; that order alone gives the generic loop retail's
// operand order and the 0xA0 frame. Get_Translation and the Matrix3D
// assignment are __forceinline because cl stops inlining them this deep into
// the body. Vector3::Lerp is a dllimport inline so the unit emits no copy to
// compete with WWMath's out-of-line one (0x0009AA48).
//
// 0x00162BB0 (3785 bytes): HTreeClass::Anim_Update(root, HAnimClass *,
// frame) in WorldBuilder's shape (0x00A16610, htree.cpp:565-610), the same
// two paths as Blend_Update. The compressed fast path hands each node the
// pivot transform through a node method (WB 0x00A16C80: translation scaled
// unconditionally, PostMul of {orientation, translation} or Translate when
// the node has no orientation channel, then the fade) and reads visibility
// from the node's TimeCodedBitChannelClass at the truncated frame. The
// generic path declares its CompactTransform before the root update.
//
// 0x00163A80 (2850 bytes): HTreeClass::Anim_Update(root, HRawAnimClass *,
// frame), WorldBuilder 0x00A16E30 (htree.cpp:766). The frame is truncated
// once by Float_To_Long (WB 0x00A171B0: fld/fistp) and clamped to zero past
// Get_Num_Frames; pointer loop over the pivots and the raw node motions. The
// channel readers (WB 0x00A171D0 Get_Vector, 0x00A17250 set_identity,
// 0x00A172B0 Get_Vector_As_Quat, 0x00A17330 Get_Bit) fill one
// CompactTransform declared before the loop, then PostMul or Translate.
#include <vector>

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 & operator += (const Vector3 & v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	Vector3 & operator *= (float k) { X = X*k; Y = Y*k; Z = Z*k; return *this; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	__declspec(dllimport) __forceinline static void Lerp(const Vector3 & a, const Vector3 & b, float alpha, Vector3 * set_result)
	{
		set_result->X = (a.X + (b.X - a.X)*alpha);
		set_result->Y = (a.Y + (b.Y - a.Y)*alpha);
		set_result->Z = (a.Z + (b.Z - a.Z)*alpha);
	}
	float X, Y, Z;
};
inline Vector3 operator + (const Vector3 & a, const Vector3 & b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}
// Inline-only (dllimport): retail's out-of-line copy is 0x0007DFB3.
__declspec(dllimport) __forceinline Vector3 operator * (float k, const Vector3 & a)
{
	return Vector3(a.X * k, a.Y * k, a.Z * k);
}

class Quaternion
{
public:
	Quaternion() {}
	Quaternion(float a, float b, float c, float d) : X(a), Y(b), Z(c), W(d) {}
	float & operator [](int i) { return (&X)[i]; }
	const float & operator [](int i) const { return (&X)[i]; }
	Quaternion & operator = (const Quaternion & source) { X = source[0]; Y = source[1]; Z = source[2]; W = source[3]; return *this; }
	void Make_Identity() { Set(0, 0, 0, 1); }
	void Set(float a, float b, float c, float d) { X = a; Y = b; Z = c; W = d; }
	void Rotate_Vector(const Vector3 & v, Vector3 * result) const;
	__forceinline void PostMultiply(const Quaternion & quaternion)
	{
		Quaternion a = *this;
		X = a.W*quaternion.X + a.X*quaternion.W + (a.Y*quaternion.Z - a.Z*quaternion.Y);
		Y = a.W*quaternion.Y + a.Y*quaternion.W - (a.X*quaternion.Z - a.Z*quaternion.X);
		Z = a.W*quaternion.Z + a.Z*quaternion.W + (a.X*quaternion.Y - a.Y*quaternion.X);
		W = a.W*quaternion.W - (a.X*quaternion.X + a.Y*quaternion.Y + a.Z*quaternion.Z);
	}
	float X, Y, Z, W;
};

inline Quaternion operator * (const Quaternion & a, const Quaternion & b)
{
	return Quaternion
	(
		a.W*b.X + b.W*a.X + (a.Y*b.Z - b.Y*a.Z),
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		a.W*b.Z + b.W*a.Z + (a.X*b.Y - b.X*a.Y),
		a.W * b.W - (a.X * b.X + a.Y * b.Y + a.Z * b.Z)
	);
}

inline void Quaternion::Rotate_Vector(const Vector3 & v, Vector3 * result) const
{
	float x = W*v.X + (Y*v.Z - v.Y*Z);
	float y = W*v.Y - (X*v.Z - v.X*Z);
	float z = W*v.Z + (X*v.Y - v.X*Y);
	float w = -(X*v.X + Y*v.Y + Z*v.Z);

	result->X = W*x - w*X + (Y*z - y*Z);
	result->Y = W*y - w*Y - (X*z - x*Z);
	result->Z = W*z - w*Z + (X*y - Y*x);
}

#include "../WWMath/Matrix3DData.h"
// WWMath matrix3d.h's inline Get_Translation(Vector3 *), which the canonical header leaves to units.
static inline void matrixGetTranslation(const Matrix3D &m, Vector3 * set)
{ set->X = m.Row[0][3]; set->Y = m.Row[1][3]; set->Z = m.Row[2][3]; }
Quaternion Build_Quaternion(const Matrix3D & mat);

class CompactTransform
{
public:
	CompactTransform() {}
	CompactTransform(const Quaternion & quaternion, const Vector3 & p) : Q(quaternion), Position(p) {}
	__forceinline CompactTransform & operator = (const Matrix3D & m)
	{
		Q = Build_Quaternion(m);
		matrixGetTranslation(m, &Position);
		return *this;
	}
	static void Multiply(const CompactTransform & compactTransform, const CompactTransform & b, CompactTransform * res)
	{
		Vector3 tmp;
		compactTransform.Q.Rotate_Vector(b.Position, &tmp);
		res->Position = tmp + compactTransform.Position;
		res->Q = compactTransform.Q * b.Q;
	}
	__forceinline void PostMul(const CompactTransform & compactTransform)
	{
		Vector3 tmp;
		Q.Rotate_Vector(compactTransform.Position, &tmp);
		Position += tmp;
		Q.PostMultiply(compactTransform.Q);
	}
	void Translate(const Vector3 & v)
	{
		Vector3 tmp;
		Q.Rotate_Vector(v, &tmp);
		Position += tmp;
	}
	Quaternion Q;
	Vector3 Position;
};

class PivotClass
{
public:
	char Name[16];
	PivotClass * Parent;
	CompactTransform BaseTransform;
	CompactTransform Transform;
	int Index;
	bool IsVisible;
	float PivotFade;
};

class RefCountClass
{
public:
	virtual void Delete_This();
	// Inline-only (dllimport): retail's out-of-line copy is 0x005D1A7D.
	__declspec(dllimport) __forceinline void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
	int NumRefs;
};

class HAnimClass : public RefCountClass
{
public:
	virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual int Get_Num_Frames(); virtual void slot6(); virtual void slot7();
	virtual void Get_Translation(Vector3 & trans, int pividx, float frame);
	virtual bool Get_Orientation(Quaternion & q, int pividx, float frame);
	virtual void slot10();
	virtual bool Get_Visibility(int pividx, float frame);
	virtual float Get_Fade(int pividx, float frame);
	virtual int Get_Num_Pivots();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual int Get_Class_ID() const;
};

class BFME2MotionChannel
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void Get_Value(float frame, float * out, unsigned char ** cache);
	virtual void slot4();
	virtual void Get_Quaternion(float frame, Quaternion * out, unsigned char ** cache);
};

class TimeCodedBitChannelClass
{
public:
	int Get_Bit(int frame);
};

struct NodeCompressedMotionStruct
{
	__forceinline void Get_Translation(Vector3 & trans, float frame, unsigned char ** cache)
	{
		if (X) X->Get_Value(frame, &trans.X, cache); else trans.X = 0;
		if (Y) Y->Get_Value(frame, &trans.Y, cache); else trans.Y = 0;
		if (Z) Z->Get_Value(frame, &trans.Z, cache); else trans.Z = 0;
	}
	bool Get_Orientation(Quaternion & quaternion, float frame, unsigned char ** cache)
	{
		if (Q == 0) return false;
		Q->Get_Quaternion(frame, &quaternion, cache);
		return true;
	}
	void Get_Fade(float * fade, float frame, unsigned char ** cache)
	{
		if (Fade == 0) *fade = 1.0f;
		else Fade->Get_Value(frame, fade, cache);
	}
	BFME2MotionChannel * X;
	BFME2MotionChannel * Y;
	BFME2MotionChannel * Z;
	BFME2MotionChannel * Q;
	__forceinline void Apply(CompactTransform & xf, float scale, float * fade, float frame, unsigned char ** cache)
	{
		CompactTransform delta;
		Get_Translation(delta.Position, frame, cache);
		delta.Position *= scale;
		if (Get_Orientation(delta.Q, frame, cache)) xf.PostMul(delta);
		else xf.Translate(delta.Position);
		Get_Fade(fade, frame, cache);
	}
	BFME2MotionChannel * Fade;
	TimeCodedBitChannelClass * Vis;
};

class HCompressedAnimClass : public HAnimClass
{
public:
	NodeCompressedMotionStruct * Get_Nodes() { return NodeMotions; }
private:
	char pad[0x58 - 8];
	NodeCompressedMotionStruct * NodeMotions;
};

class MotionChannelClass
{
public:
	__forceinline void Get_Vector(int frame, float * setvec)
	{
		if ((frame < FirstFrame) || (frame > LastFrame)) {
			set_identity(setvec);
		} else {
			int vecframe = frame - FirstFrame;
			for (int i = 0; i < VectorLen; i++) {
				setvec[i] = Data[vecframe * VectorLen + i];
			}
		}
	}
	__forceinline void Get_Vector_As_Quat(int frame, Quaternion & quat)
	{
		if ((frame < FirstFrame) || (frame > LastFrame)) {
			quat.Set(0, 0, 0, 1);
		} else {
			float * v = &Data[(frame - FirstFrame) * VectorLen];
			quat.Set(v[0], v[1], v[2], v[3]);
		}
	}
private:
	__forceinline void set_identity(float * setvec)
	{
		if (Type == 15) {
			setvec[0] = 1.0f;
		} else {
			setvec[0] = 0.0f;
			if (Type == 6) {
				setvec[1] = 0.0f;
				setvec[2] = 0.0f;
				setvec[3] = 1.0f;
			}
		}
	}
	unsigned int PivotIdx;
	unsigned int Type;
	int VectorLen;
	float ValueOffset;
	float ValueScale;
	float * Data;
	int FirstFrame;
	int LastFrame;
};

class BitChannelClass
{
public:
	// Inline-only (dllimport): BitChannelGetBit.cpp owns the out-of-line copy.
	__declspec(dllimport) __forceinline int Get_Bit(int frame)
	{
		if ((frame < FirstFrame) || (frame > LastFrame)) {
			return DefaultVal;
		} else {
			int bit = frame - FirstFrame;
			unsigned char mask = (unsigned char)(1 << (bit & 7));
			return (Bits[bit >> 3] & mask) != 0;
		}
	}
private:
	unsigned int PivotIdx;
	unsigned int Type;
	int DefaultVal;
	int FirstFrame;
	int LastFrame;
	unsigned char * Bits;
};

struct NodeMotionStruct
{
	MotionChannelClass * X;
	MotionChannelClass * Y;
	MotionChannelClass * Z;
	MotionChannelClass * XR;
	MotionChannelClass * YR;
	MotionChannelClass * ZR;
	MotionChannelClass * Q;
	MotionChannelClass * Fade;
	BitChannelClass * Vis;
};

class HRawAnimClass : public HAnimClass
{
public:
	NodeMotionStruct * Get_Node_Motion_Array() { return NodeMotions; }
private:
	char pad[0x50 - 8];
	NodeMotionStruct * NodeMotions;
};

__forceinline long Float_To_Long(float f)
{
	long retval;
	__asm fld dword ptr [f]
	__asm fistp dword ptr [retval]
	return retval;
}

class Rva00160FC0Input;

inline float Lerp(float a, float b, float lerp) { return (a + (b - a)*lerp); }
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

class PivotMapVector
{
public:
	virtual void slot0();
	float *Values;
	char rest[0x10];
};

class PivotMapClass : public PivotMapVector, public RefCountClass
{
public:
	float & operator [](int i) { return Values[i]; }
};

class HAnimComboClass
{
public:
	int Get_Num_Anims() const { return NumAnims; }
	HAnimClass * Get_Motion(int indx);
	HAnimClass * Peek_Motion(int indx);
	float Get_Frame(int indx);
	float Get_Weight(int indx);
	PivotMapClass * Get_Pivot_Weight_Map(int indx);
private:
	char pad[0x10];
	int NumAnims;
};

void BFME2_Nlerp(Quaternion & res, const Quaternion & a, const Quaternion & b, float t);

class HTreeClass {
public:
	void Combo_Update(const Matrix3D & root, HAnimComboClass * anim);
	int rva00162290() const;
	int Capture_Update(int pivot_index);
	void Base_Update(const Matrix3D & root);
	void Anim_Update(const Matrix3D & root, HAnimClass * motion, float frame);
	void Anim_Update(const Matrix3D & root, HRawAnimClass * motion, float frame);
	void Blend_Update(const Matrix3D & root, HAnimClass * motion0, float frame0, HAnimClass * motion1, float frame1, float percentage);
	void rva00160FC0(Rva00160FC0Input * next);	// motion/channel cache refresh 0x00160FC0
private:
	struct CapturedPivot { int PivotIndex; CompactTransform Transform; bool WorldSpaceTranslation; };
	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
	std::vector<CapturedPivot> CapturedPivots;
	HAnimClass * CachedMotion;
	unsigned char * ChannelCache;
};

int HTreeClass::rva00162290() const
{
	if (CapturedPivots.empty())
		return -1;
	return CapturedPivots.front().PivotIndex;
}

void HTreeClass::Base_Update(const Matrix3D & root)
{
	PivotClass *pivot;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int captured = rva00162290();

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

		pivot = &Pivot[piv_idx];

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));
		pivot->IsVisible = 1;
		pivot->PivotFade = 1.0f;

		if (piv_idx == captured) captured = Capture_Update(captured);
	}
}

int HTreeClass::Capture_Update(int pivot_index)
{
	std::vector<CapturedPivot>::iterator i;
	for (i = CapturedPivots.begin(); i != CapturedPivots.end() && i->PivotIndex < pivot_index; ++i) {
	}

	if (i == CapturedPivots.end() || i->PivotIndex != pivot_index)
		return -1;

	if (i->WorldSpaceTranslation) {
		CompactTransform rotation(i->Transform.Q, Vector3(0, 0, 0));
		Pivot[pivot_index].Transform.PostMul(rotation);
		Pivot[pivot_index].Transform.Position += i->Transform.Position;
	} else {
		Pivot[pivot_index].Transform.PostMul(i->Transform);
	}

	++i;
	if (i == CapturedPivots.end())
		return -1;
	return i->PivotIndex;
}

void HTreeClass::Combo_Update(const Matrix3D & root, HAnimComboClass * anim)
{
	PivotClass *pivot;
	// Never read and emit nothing: cl breaks ties between commutative
	// operands by symbol number, and retail's operand order needs this body
	// to number 23 (or 31) more initialized locals than it otherwise has.
	int unused0 = 0, unused1 = 0, unused2 = 0, unused3 = 0, unused4 = 0,
		unused5 = 0, unused6 = 0, unused7 = 0, unused8 = 0, unused9 = 0,
		unused10 = 0, unused11 = 0, unused12 = 0, unused13 = 0, unused14 = 0,
		unused15 = 0, unused16 = 0, unused17 = 0, unused18 = 0, unused19 = 0,
		unused20 = 0, unused21 = 0, unused22 = 0;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int num_anim_pivots = 100000;
	for (int anim_num = 0; anim_num < anim->Get_Num_Anims(); anim_num++) {
		num_anim_pivots = num_anim_pivots < anim->Peek_Motion(anim_num)->Get_Num_Pivots() ? num_anim_pivots : anim->Peek_Motion(anim_num)->Get_Num_Pivots();
	}
	if (num_anim_pivots == 100000) num_anim_pivots = 0;

	int captured = rva00162290();

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

		pivot = &Pivot[piv_idx];

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

		if (piv_idx < num_anim_pivots) {

			Vector3 trans(0, 0, 0);
			Quaternion q0;
			Quaternion q1;
			float weight_total = 0;
			int wcount = 0;

			for (int anim_num = 0; anim_num < anim->Get_Num_Anims(); anim_num++) {
				HAnimClass *motion = anim->Get_Motion(anim_num);
				if (motion) {
					float frame_num = anim->Get_Frame(anim_num);
					PivotMapClass *pivot_map = anim->Get_Pivot_Weight_Map(anim_num);
					float weight = anim->Get_Weight(anim_num);
					if (pivot_map) {
						weight *= (*pivot_map)[piv_idx];
						pivot_map->Release_Ref();
					}
					if (weight != 0.0) {
						wcount++;
						Vector3 temp_trans;
						motion->Get_Translation(temp_trans, piv_idx, frame_num);
						trans += weight * ScaleFactor * temp_trans;
						weight_total += weight;
						if (!motion->Get_Orientation(q1, piv_idx, frame_num)) q1.Make_Identity();
						if (wcount == 1) {
							q0 = q1;
						} else {
							BFME2_Nlerp(q0, q0, q1, weight / weight_total);
						}
					}
					motion->Release_Ref();
				}
			}

			if (weight_total != 0.0f) {
				pivot->Transform.PostMul(CompactTransform(q0, trans));
			}

			pivot->IsVisible = false;
			pivot->PivotFade = 0;
			float fade_count = 0;
			for (anim_num = 0; anim_num < anim->Get_Num_Anims() && !pivot->IsVisible; anim_num++) {
				HAnimClass *motion = anim->Get_Motion(anim_num);
				if (motion) {
					float frame_num = anim->Get_Frame(anim_num);
					pivot->IsVisible |= motion->Get_Visibility(piv_idx, frame_num);
					pivot->PivotFade += motion->Get_Fade(piv_idx, frame_num);
					fade_count += 1.0f;
					motion->Release_Ref();
				}
			}
			if (fade_count > 0.0f) pivot->PivotFade /= fade_count;
		}

		if (piv_idx == captured) captured = Capture_Update(captured);
	}
}

void HTreeClass::Blend_Update(const Matrix3D & root, HAnimClass * motion0, float frame0, HAnimClass * motion1, float frame1, float percentage)
{
	if (motion0->Get_Class_ID() == 1) {

		HCompressedAnimClass *cmotion = (HCompressedAnimClass *)motion0;
		NodeCompressedMotionStruct *nodes = cmotion->Get_Nodes();

		if (nodes != 0) {

			rva00160FC0((Rva00160FC0Input *)cmotion);

			Pivot[0].Transform = root;
			Pivot[0].IsVisible = true;
			Pivot[0].PivotFade = 1.0f;

			unsigned char *cache = ChannelCache;

			int num_anim_pivots = MIN(motion0->Get_Num_Pivots(), motion1->Get_Num_Pivots());

			int captured = rva00162290();

			for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

				PivotClass *pivot = &Pivot[piv_idx];

				CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

				if (piv_idx < num_anim_pivots) {

					NodeCompressedMotionStruct *node = &nodes[piv_idx];
					CompactTransform xform;

					Vector3 trans0;
					node->Get_Translation(trans0, frame0, &cache);
					Vector3 trans1;
					motion1->Get_Translation(trans1, piv_idx, frame1);
					Vector3::Lerp(trans0, trans1, percentage, &xform.Position);
					xform.Position *= ScaleFactor;

					Quaternion q0;
					bool has0 = node->Get_Orientation(q0, frame0, &cache);
					Quaternion q1;
					bool has1 = motion1->Get_Orientation(q1, piv_idx, frame1);

					if (has0 || has1) {
						if (!has0) q0.Make_Identity();
						if (!has1) q1.Make_Identity();
						BFME2_Nlerp(xform.Q, q0, q1, percentage);
						pivot->Transform.PostMul(xform);
					} else {
						pivot->Transform.Translate(xform.Position);
					}

					float fade0;
					node->Get_Fade(&fade0, frame0, &cache);
					pivot->PivotFade = Lerp(fade0, motion1->Get_Fade(piv_idx, frame1), percentage);
					pivot->IsVisible = motion0->Get_Visibility(piv_idx, frame0) || motion1->Get_Visibility(piv_idx, frame1);
				}

				if (piv_idx == captured) captured = Capture_Update(captured);
			}
			return;
		}
	}

	CachedMotion = 0;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int num_anim_pivots = MIN(motion0->Get_Num_Pivots(), motion1->Get_Num_Pivots());

	int captured = rva00162290();
	CompactTransform xform;

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

		PivotClass *pivot = &Pivot[piv_idx];

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

		if (piv_idx < num_anim_pivots) {

			Vector3 trans0;
			motion0->Get_Translation(trans0, piv_idx, frame0);
			Vector3 trans1;
			motion1->Get_Translation(trans1, piv_idx, frame1);
			Vector3::Lerp(trans0, trans1, percentage, &xform.Position);
			if (ScaleFactor != 1.0f) xform.Position *= ScaleFactor;

			Quaternion q0;
			bool has0 = motion0->Get_Orientation(q0, piv_idx, frame0);
			Quaternion q1;
			bool has1 = motion1->Get_Orientation(q1, piv_idx, frame1);

			if (has0 || has1) {
				if (!has0) q0.Make_Identity();
				if (!has1) q1.Make_Identity();
				BFME2_Nlerp(xform.Q, q0, q1, percentage);
				pivot->Transform.PostMul(xform);
			} else {
				pivot->Transform.Translate(xform.Position);
			}

			pivot->IsVisible = motion0->Get_Visibility(piv_idx, frame0) || motion1->Get_Visibility(piv_idx, frame1);
			pivot->PivotFade = Lerp(motion0->Get_Fade(piv_idx, frame0), motion1->Get_Fade(piv_idx, frame1), percentage);
		}

		if (piv_idx == captured) captured = Capture_Update(captured);
	}
}

void HTreeClass::Anim_Update(const Matrix3D & root, HAnimClass * motion, float frame)
{
	if (motion->Get_Class_ID() == 1) {

		HCompressedAnimClass *cmotion = (HCompressedAnimClass *)motion;
		NodeCompressedMotionStruct *nodes = cmotion->Get_Nodes();

		if (nodes != 0) {

			rva00160FC0((Rva00160FC0Input *)cmotion);

			Pivot[0].Transform = root;
			Pivot[0].IsVisible = true;
			Pivot[0].PivotFade = 1.0f;

			unsigned char *cache = ChannelCache;

			int num_anim_pivots = motion->Get_Num_Pivots();

			int captured = rva00162290();

			for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

				PivotClass *pivot = &Pivot[piv_idx];

				CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

				if (piv_idx < num_anim_pivots) {

					NodeCompressedMotionStruct *node = &nodes[piv_idx];
					node->Apply(pivot->Transform, ScaleFactor, &pivot->PivotFade, frame, &cache);
					if (node->Vis) {
						pivot->IsVisible = node->Vis->Get_Bit((int)frame) != 0;
					} else {
						pivot->IsVisible = true;
					}
				}

				if (piv_idx == captured) captured = Capture_Update(captured);
			}
			return;
		}
	}

	CachedMotion = 0;

	CompactTransform xform;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int num_anim_pivots = motion->Get_Num_Pivots();

	int captured = rva00162290();

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

		PivotClass *pivot = &Pivot[piv_idx];

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

		if (piv_idx < num_anim_pivots) {

			motion->Get_Translation(xform.Position, piv_idx, frame);
			if (ScaleFactor != 1.0f) xform.Position *= ScaleFactor;

			if (motion->Get_Orientation(xform.Q, piv_idx, frame)) {
				pivot->Transform.PostMul(xform);
			} else {
				pivot->Transform.Translate(xform.Position);
			}

			pivot->IsVisible = motion->Get_Visibility(piv_idx, frame);
			pivot->PivotFade = motion->Get_Fade(piv_idx, frame);
		}

		if (piv_idx == captured) captured = Capture_Update(captured);
	}
}

void HTreeClass::Anim_Update(const Matrix3D & root, HRawAnimClass * motion, float frame)
{
	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int iframe = Float_To_Long(frame);
	if (iframe >= motion->Get_Num_Frames()) iframe = 0;

	NodeMotionStruct * nodemotion = motion->Get_Node_Motion_Array();
	nodemotion++;

	PivotClass * pivot = &Pivot[1];
	PivotClass * endpivot = pivot + NumPivots - 1;
	PivotClass * lastAnimPivot = &Pivot[motion->Get_Num_Pivots()];

	int captured = rva00162290();

	CompactTransform xform;
	for (; pivot < endpivot; pivot++, nodemotion++) {

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));

		if (pivot < lastAnimPivot) {
			xform.Position.Set(0, 0, 0);
			if (nodemotion->X != NULL) nodemotion->X->Get_Vector(iframe, &(xform.Position.X));
			if (nodemotion->Y != NULL) nodemotion->Y->Get_Vector(iframe, &(xform.Position.Y));
			if (nodemotion->Z != NULL) nodemotion->Z->Get_Vector(iframe, &(xform.Position.Z));

			if (ScaleFactor != 1.0f) xform.Position *= ScaleFactor;

			if (nodemotion->Q != NULL) {
				nodemotion->Q->Get_Vector_As_Quat(iframe, xform.Q);
				pivot->Transform.PostMul(xform);
			} else {
				pivot->Transform.Translate(xform.Position);
			}

			if (nodemotion->Fade != NULL) {
				float fade = 1.0f;
				nodemotion->Fade->Get_Vector(iframe, &fade);
				pivot->PivotFade = fade;
			} else {
				pivot->PivotFade = 1.0f;
			}

			if (nodemotion->Vis != NULL) {
				pivot->IsVisible = (nodemotion->Vis->Get_Bit(iframe) == 1);
			} else {
				pivot->IsVisible = true;
			}
		}

		if (pivot->Index == captured) captured = Capture_Update(captured);
	}
}
