// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// ?compose@RigidTransform@@QAEXABU1@@Z, retail 0x0015FC20 (607 bytes, RET 4):
// a rotation+translation prefix (16-byte quaternion at +0x00, position at +0x10) composed
// with another: the other position is rotated by this rotation and added, then this
// rotation is multiplied incrementally by the other's. Target facts: the whole body and
// its offsets; nothing in the image calls or references it. Carried from donor/siblings:
// the expansion is WWMath quat.h's result-pointer Rotate_Vector (as the rowed out-of-line
// copy at 0x0015F6D0, QuaternionRotateVector.cpp) and the incremental product of the
// rowed neighbour 0x0015F810 (Rva0015F810QuaternionPrefixMultiply.cpp), term order as
// those bodies read from retail. The owner class and its original names are unknown.
struct Rva0015FC20Vector
{
	__forceinline Rva0015FC20Vector &operator+=(const Rva0015FC20Vector &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	float X, Y, Z;
};

struct Rva0015FC20Rotation
{
	__forceinline void Rotate_Vector(const Rva0015FC20Vector &v, Rva0015FC20Vector *result) const
	{
		float productX = W*v.X + (Y*v.Z - v.Y*Z);
		float productY = W*v.Y - (X*v.Z - v.X*Z);
		float productZ = W*v.Z + (X*v.Y - v.X*Y);
		float productW = -(X*v.X + Y*v.Y + Z*v.Z);

		result->X = W*productX - productW*X + (Y*productZ - productY*Z);
		result->Y = W*productY - productW*Y - (X*productZ - productX*Z);
		result->Z = W*productZ - productW*Z + (X*productY - Y*productX);
	}
	__forceinline void multiply(const Rva0015FC20Rotation &other)
	{
		Rva0015FC20Rotation saved = *this;
		X = other.W*saved.X + (saved.Y*other.Z - other.Y*saved.Z) + saved.W*other.X;
		Y = other.W*saved.Y + saved.W*other.Y - (saved.X*other.Z - other.X*saved.Z);
		Z = (saved.X*other.Y - other.X*saved.Y) + other.W*saved.Z + saved.W*other.Z;
		W = other.W*saved.W - (other.Z*saved.Z + other.Y*saved.Y + other.X*saved.X);
	}
	float X, Y, Z, W;
};

struct RigidTransform
{
	void compose(const RigidTransform &other);
	Rva0015FC20Rotation Rotation;		// +0x00
	Rva0015FC20Vector Position;		// +0x10
};

void RigidTransform::compose(const RigidTransform &other)
{
	Rva0015FC20Vector rotatedPosition;
	Rotation.Rotate_Vector(other.Position, &rotatedPosition);
	Position += rotatedPosition;
	Rotation.multiply(other.Rotation);
}
