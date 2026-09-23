// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.8 date=2026-09-23
// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

inline Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

class Matrix3D
{
public:
	float Row[3][4];
};

class Quaternion
{
public:
	Quaternion() {}
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	float X, Y, Z, W;
};

inline Vector3 Rotate_Vector(const Vector3 &v, const Quaternion &q)
{
	float x = (v.Z*q.Y - q.Z*v.Y) + q.W*v.X;
	float y = q.W*v.Y - (v.Z*q.X - q.Z*v.X);
	float z = (q.X*v.Y - v.X*q.Y) + v.Z*q.W;
	float w = -(v.Y*q.Y + v.Z*q.Z + q.X*v.X);

	return Vector3
	(
		(z*q.Y - q.Z*y) + (q.W*x - q.X*w),
		(q.W*y - w*q.Y) - (q.X*z - q.Z*x),
		(q.X*y - x*q.Y) + (q.W*z - q.Z*w)
	);
}


inline Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
	return Quaternion
	(
		a.W*b.X + b.W*a.X + (a.Y*b.Z - b.Y*a.Z),
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		a.W*b.Z + b.W*a.Z + (a.X*b.Y - b.X*a.Y),
		a.W*b.W - (a.X*b.X + a.Y*b.Y + a.Z*b.Z)
	);
}

Quaternion Build_Quaternion(const Matrix3D &mat);

// BFME 2 pivot transform: rotation quaternion plus translation.
struct PivotTransform
{
	Quaternion Rotation;
	Vector3 Translation;
};

inline PivotTransform operator * (const PivotTransform &parent, const PivotTransform &child)
{
	PivotTransform result;
	result.Translation = Rotate_Vector(child.Translation, parent.Rotation) + parent.Translation;
	result.Rotation = parent.Rotation * child.Rotation;
	return result;
}

struct PivotClass
{
	char Name[16];
	PivotClass *Parent;					// +0x10
	PivotTransform BaseTransform;		// +0x14
	PivotTransform Transform;			// +0x30
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};

class HTreeClass
{
public:
	void Base_Update(const Matrix3D &root);
	int Capture_Update(int pivot_index);

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
	float ScaleFactor;					// +0x18
	int *CapturedBegin;					// +0x1C
	int *CapturedEnd;					// +0x20
};

void HTreeClass::Base_Update(const Matrix3D &root)
{
	Pivot[0].Transform.Rotation = Build_Quaternion(root);
	Pivot[0].Transform.Translation.X = root.Row[0][3];
	Pivot[0].Transform.Translation.Y = root.Row[1][3];
	Pivot[0].Transform.Translation.Z = root.Row[2][3];
	Pivot[0].IsVisible = true;
	Pivot[0].m_bfme54 = 1.0f;

	int captured = (CapturedBegin == CapturedEnd) ? -1 : *CapturedBegin;

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {
		PivotClass *pivot = &Pivot[piv_idx];
		const PivotTransform &parent = pivot->Parent->Transform;
		pivot->Transform.Translation = parent.Translation + Rotate_Vector(pivot->BaseTransform.Translation, parent.Rotation);
		pivot->Transform.Rotation = parent.Rotation * pivot->BaseTransform.Rotation;
		pivot->IsVisible = true;
		pivot->m_bfme54 = 1.0f;

		if (piv_idx == captured)
			captured = Capture_Update(piv_idx);
	}
}
