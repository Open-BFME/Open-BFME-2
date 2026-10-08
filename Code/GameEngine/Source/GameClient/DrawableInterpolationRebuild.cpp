// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
// ?rva002747F9@Rva002747F9@@QAEXH@Z, native 0x002747F9..0x00274C62, 1129B.
// Clean donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameClient/BFMERopeDrawableInterpolatedPosition.cpp.
// Target linkage: the native position and transform-cache bodies call this
// same receiver with force=0. WB 0x00CB7440 corroborates the interpolation
// cache update, but supplies no source name; keep an address-derived owner.
// Native evidence proves every field offset, null/force/normal branch,
// all matrix and position copies, five existing helper call targets, and
// the three-argument virtual slot0 notification over [drawBegin,drawEnd).
// BFME2 deltas from the donor: 76-byte condition masks, a bounded pointer
// range for draw interfaces, +0x208/+0x244 cached matrix/frame, endpoint
// matrices +0x3AC/+0x3DC, position knots +0x40C..+0x430, flags +0x443/+0x444,
// and rowed Object-view queries instead of donor-specific inline fields.
// WWMath's three Vector4 rows preserve the verified matrix-copy shape.
// Concrete object/interface source names and complete layouts remain unknown.
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Vector4
{
public:
    float X, Y, Z, W;
    __forceinline Vector4 &operator=(const Vector4 &v)
    {
        X=v.X; Y=v.Y; Z=v.Z; W=v.W;
        return *this;
    }
};
class Matrix3D
{
public:
    Vector4 Row[3];
    __forceinline Matrix3D &operator=(const Matrix3D &other)
    {
        Row[0]=other.Row[0];
        Row[1]=other.Row[1];
        Row[2]=other.Row[2];
        return *this;
    }
    static void Lerp(const Matrix3D &, const Matrix3D &, float, Matrix3D &);
};

class Rva00271C8A { public: void rva00271C8A(const int *, const int *); };
class Rva002722AA { public: void *get() const; };
class Rva002722BD { public: void *get() const; };
class Rva0028E8D4 { public: void rva0028E8D4(float *) const; };
class Rva001E434A { public: void *rva001E434A(); };
class ModelConditionFlags
{
public:
    int m_bits[19];
    void clearAndSet(const ModelConditionFlags &clear, const ModelConditionFlags &set)
    {
        reinterpret_cast<Rva00271C8A *>(this)->rva00271C8A(clear.m_bits,set.m_bits);
    }
};
class Rva002747F9DrawInterface
{
public:
    virtual void v00(const ModelConditionFlags &, bool, unsigned int);
};
class Rva002747F9ObjectView
{
public:
    char m_pad000[8];
    Matrix3D m_transform;
    Coord3D m_position;
    const Matrix3D *getTransform() const { return reinterpret_cast<const Matrix3D *>(reinterpret_cast<const Rva002722AA *>(this)->get()); }
    const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const Rva002722BD *>(this)->get()); }
    void getTranslation(Coord3D *out) const { reinterpret_cast<const Rva0028E8D4 *>(this)->rva0028E8D4(&out->x); }
    const Coord3D *getRow() { return reinterpret_cast<const Coord3D *>(reinterpret_cast<Rva001E434A *>(this)->rva001E434A()); }
};
class Rva002747F9
{
private:
    char m_pad000[8];
    Matrix3D m_transform;
    Coord3D m_basePosition;
    char m_pad044[0xfc-0x44];
    Rva002747F9ObjectView *m_object;
    char m_pad100[0x158-0x100];
    Rva002747F9DrawInterface **m_drawBegin;
    Rva002747F9DrawInterface **m_drawEnd;
    char m_pad160[0x208-0x160];
    Matrix3D m_cachedMatrix;
    Coord3D m_interpolatedPosition;
    int m_lastFrameStamp;
    char m_pad248[0x258-0x248];
    ModelConditionFlags m_conditionState, m_clearMask, m_setMask;
    char m_pad33C[0x3ac-0x33c];
    Matrix3D m_transformCache;
    Matrix3D m_currentTransform;
    Coord3D m_position0, m_tangent0, m_position1, m_tangent1;
    char m_pad43C[7];
    bool m_isModelDirty;
    bool m_interpolationReady;
public:
    void rva002747F9(int force);
};
void Rva002747F9::rva002747F9(int force)
{
	m_interpolationReady = true;
    Rva002747F9ObjectView *object = m_object;
    m_lastFrameStamp = -1;
	if (object == 0)
	{
		m_currentTransform = m_transform;
		m_transformCache = m_currentTransform;
		m_tangent1 = m_basePosition;
		m_position1 = m_basePosition;
		m_tangent0 = m_basePosition;
		m_position0 = m_basePosition;
		return;
	}

	if ((unsigned char)force)
	{
        // Both copies are present in the native force branch and the donor.
		m_transformCache = object->m_transform;
		m_transformCache = object->m_transform;
		m_currentTransform = object->m_transform;
		m_position0 = object->m_position;
		m_tangent0 = object->m_position;
		m_cachedMatrix = object->m_transform;
		m_interpolatedPosition = object->m_position;

		if (m_isModelDirty)
		{
			m_conditionState.clearAndSet(m_clearMask, m_setMask);
            Rva002747F9DrawInterface **end = m_drawEnd;
            for (Rva002747F9DrawInterface **module=m_drawBegin; module!=end; ++module)
                (*module)->v00(m_conditionState,false,0);
			m_isModelDirty = false;
		}
		goto finish;
	}

	const Matrix3D *transform = object->getTransform();
	m_transformCache = *transform;
	m_currentTransform = object->m_transform;

	const Coord3D *position = object->getPosition();
	m_position0 = *position;
	object->getTranslation(&m_tangent0);

finish:
	m_position1 = object->m_position;
	m_tangent1 = *object->getRow();
}
