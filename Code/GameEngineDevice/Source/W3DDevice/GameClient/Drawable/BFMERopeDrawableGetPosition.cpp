// cl: /DNDEBUG /MD /EHsc
// BFME1 donor: reference/open-bfme-1/game/GameEngine/Source/GameClient/BFMERopeDrawableInterpolatedPosition.cpp
// donor revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9. The retail
// getPosition body carries the same interpolation logic but uses BFME2 member
// offsets; the rebuild helper's target identity remains address-derived.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

class GameEngine
{
private:
	char m_unreconstructed_000[0x3c];

public:
	float m_interpolationFactor;
};

extern GameEngine *TheGameEngine;

extern "C" BfmeVector3 *__stdcall D3DXVec3CatmullRom(
	BfmeVector3 *result,
	const Coord3D *position0,
	const Coord3D *tangent0,
	const Coord3D *position1,
	const Coord3D *tangent1,
	float factor);

class Rva002747F9
{
public:
	void rva002747F9(int force);
};

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_D3DXVec3CatmullRom@24=_rva0062AFC8D3DXVec3CatmullRom@24")

// Clean donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/Common/BfmeCalc919G.cpp (BFME1 0x0041CEC0).
// Target identity: exact call sites in Weapon::preFireWeapon and the landed
// LaserUpdate/FX consumers carry Drawable::getTransformMatrix's const pointer ABI.
// Native 0x0027628E..0x002763E6 confirms cached frame, object transform copy,
// Matrix3D::Lerp, Catmull-Rom translation, and every cache/member offset below.
// WWMath matrix3d.h/vector4.h establish three four-float rows; native fast-copy
// blocks corroborate that row assignment shape. Forceinline retains these
// reference assignments inside the proven native 344-byte body.
// The rebuild helper remains address-named; its source identity is unproved.

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

class ClientFrameSubsystem
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C(); virtual void slot70();
    virtual void slot74(); virtual void slot78();
    virtual unsigned int getFrameStamp();
};

class GameClient;
extern GameClient *TheGameClient;

extern GameLogic *TheGameLogic;

class BfmeCacheObject
{
private:
	unsigned char m_unmodelled[ 8 ];

public:
	Matrix3D m_matrix;
};

class Drawable
{
private:
    unsigned char m_pad000[8];
    Matrix3D m_baseMatrix;
    Coord3D m_basePosition;			// +0x38 (Thing's cached position)
    unsigned char m_pad044[0xfc-0x44];
    BfmeCacheObject *m_object;
    unsigned char m_pad100[0x208-0x100];
    mutable Matrix3D m_cachedMatrix;
    mutable Coord3D m_interpolatedPosition;	// +0x238
    mutable unsigned int m_lastFrameStamp;
    unsigned char m_pad248[0x3a4-0x248];
    unsigned int m_updateFrame;
    mutable unsigned char m_ready;
    unsigned char m_pad3a9[3];
    Matrix3D m_matrix0;
    Matrix3D m_matrix1;
    Coord3D m_position0;
    Coord3D m_tangent0;
    Coord3D m_position1;
    Coord3D m_tangent1;
    unsigned char m_pad43c[8];
    unsigned char m_rebuildReady;
public:
    const Matrix3D *getTransformMatrix() const;
    const Coord3D *getPosition() const;
};

// ?getPosition@Drawable@@QBEPBUCoord3D@@XZ retail 0x002763E6 (138B), the
// position twin of getTransformMatrix below (was rowed as
// BFMERopeDrawable::getPosition). Identity (target): it returns Thing's cached
// position (+0x38) without an object and otherwise the Catmull-Rom position
// (+0x40C..+0x438 under the +0x444 ready flag) cached at +0x238, the same
// interpolation state getTransformMatrix (0x0027628E) reads; its callers pass
// Drawable pointers (LaserUpdate::initFromDrawables 0x00363853
// GameClient::iterateDrawablesInRegion).
const Coord3D *Drawable::getPosition() const
{
	if (!m_object)
		return &m_basePosition;

	if (!m_rebuildReady)
		reinterpret_cast<Rva002747F9 *>(const_cast<Drawable *>(this))->rva002747F9(0);

	Coord3D interpolated;
	BfmeVector3 result;
	D3DXVec3CatmullRom(
		&result,
		&m_position0,
		&m_tangent0,
		&m_position1,
		&m_tangent1,
		TheGameEngine->m_interpolationFactor);

	interpolated.x = result.x;
	interpolated.y = result.y;
	interpolated.z = result.z;
	m_interpolatedPosition = interpolated;
	return &m_interpolatedPosition;
}

const Matrix3D *Drawable::getTransformMatrix() const
{
	BfmeCacheObject *object = m_object;
	if( object == 0 )
		return &m_baseMatrix;

	float factor;
	unsigned int frameStamp =
		reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->getFrameStamp();
	if( m_lastFrameStamp == frameStamp )
		goto return_cached;

	unsigned int updateFrame = m_updateFrame;
	unsigned int logicFrame = TheGameLogic->getFrame();
	if( updateFrame < logicFrame - 2 )
	{
		if( m_ready == 0 )
		{
			m_ready = 1;
			m_cachedMatrix = object->m_matrix;
		}
		goto return_cached;
	}

	if( m_rebuildReady == 0 )
		(reinterpret_cast<Rva002747F9 *>(const_cast<Drawable *>(this)))->rva002747F9( 0 );

	factor = TheGameEngine->m_interpolationFactor;
	Matrix3D *cachedMatrix = &m_cachedMatrix;
	Matrix3D::Lerp( m_matrix0, m_matrix1, factor, *cachedMatrix );

	m_lastFrameStamp = frameStamp;
	BfmeVector3 interpolated;
	D3DXVec3CatmullRom( &interpolated, &m_position0, &m_tangent0,
		&m_position1, &m_tangent1, factor );
	cachedMatrix->Row[0].W = interpolated.x;
	cachedMatrix->Row[1].W = interpolated.y;
	cachedMatrix->Row[2].W = interpolated.z;

return_cached:
	return &m_cachedMatrix;
}

// BFME1 clean linear-position donor at 0x0041D150, revision
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Target native 0x00276470..0x0027653A
// and WB 0x00CB0270 corroborate the null-object return, lazy rebuild, and
// axis interpolation. Receiver +0xFC and returned +0x38/+0x238 are independently
// witnessed by GameClient's frustum walk. Preserve its existing address-derived
// method name: the target original name is unproved. The scalar 1.0f matches
// retail's compiler-literal reference; no address-named global is required.

class Rva00276470Drawable
{
private:
	unsigned char m_unknown000[0x38];
	Coord3D m_basePosition;
	unsigned char m_unknown044[0x0FC - 0x44];
	void *m_object;
	unsigned char m_unknown100[0x238 - 0x100];
	Coord3D m_interpolatedPosition;
	unsigned char m_unknown244[0x418 - 0x244];
	Coord3D m_position0;
	Coord3D m_position1;
	unsigned char m_unknown430[0x444 - 0x430];
	bool m_interpolationReady;

public:
	const Coord3D *rva00276470() const;
};

const Coord3D *Rva00276470Drawable::rva00276470() const
{
	if (!m_object)
		return &m_basePosition;

	Rva00276470Drawable *self =
		const_cast<Rva00276470Drawable *>(this);
	if (!m_interpolationReady)
		reinterpret_cast<Rva002747F9 *>(self)->rva002747F9(0);

	float factor = TheGameEngine->m_interpolationFactor;
	if (m_position0.x == m_position1.x)
		self->m_interpolatedPosition.x = m_position0.x;
	else
		self->m_interpolatedPosition.x =
			(1.0f - factor) * m_position0.x + factor * m_position1.x;

	float oneMinusFactor = 1.0f - factor;
	self->m_interpolatedPosition.y =
		oneMinusFactor * m_position0.y + factor * m_position1.y;
	self->m_interpolatedPosition.z =
		oneMinusFactor * m_position0.z + factor * m_position1.z;
	return &m_interpolatedPosition;
}
