// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z, retail 0x002711C6, 605 bytes.
// Identity: the two-argument BFME setInstanceMatrix. Callers pass a Drawable
// from Object::getDrawable (0x005508E2): FloatUpdate::update with false,
// StructureCollapseUpdate (0x004A47FA and siblings) with true and
// SwayClientUpdate (0x004C94CE), the same callers BFME 1 shows. Donor: BFME 1's
// matched reference/open-bfme-1/game/GameEngine/Source/GameClient/
// DrawableSetInstanceMatrixBFME.cpp, over Zero Hour's one-argument
// Drawable::setInstanceMatrix (the instance copy or identity plus the identity
// flag). BFME 2 offsets measured from retail: previous instance +0x170,
// instance +0x1A0 (the pair the rowed interpolator 0x00271423 lerps), the
// interpolation stamp +0x204, the instance frame +0x378, the identity flag
// +0x43F; TheGameEngine's frame int is at +0x38 and the client time is
// TheGameClient slot 0x7C (as in 0x00271423). The Matrix3D and Vector4
// members are WWMath's WWINLINE (__forceinline); plain inline leaves the
// assignment out of line at /O1.

typedef unsigned int UnsignedInt;
typedef float Real;

class Matrix3D
{
public:
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}

	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

private:
	class Vector4
	{
	public:
		__forceinline void Set(Real x, Real y, Real z, Real w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		__forceinline Vector4 &operator=(const Vector4 &v)
		{
			X = v.X;
			Y = v.Y;
			Z = v.Z;
			W = v.W;
			return *this;
		}

		Real X;
		Real Y;
		Real Z;
		Real W;
	};

	Vector4 Row[3];
};

class GameEngine
{
public:
	unsigned char m_pad000[0x38];
	int m_frame; // +0x38
};
extern GameEngine *TheGameEngine;

class GameClient
{
public:
#define CLIENT_SLOT(n) virtual void slot##n();
	CLIENT_SLOT(00) CLIENT_SLOT(01) CLIENT_SLOT(02) CLIENT_SLOT(03) CLIENT_SLOT(04)
	CLIENT_SLOT(05) CLIENT_SLOT(06) CLIENT_SLOT(07) CLIENT_SLOT(08) CLIENT_SLOT(09)
	CLIENT_SLOT(10) CLIENT_SLOT(11) CLIENT_SLOT(12) CLIENT_SLOT(13) CLIENT_SLOT(14)
	CLIENT_SLOT(15) CLIENT_SLOT(16) CLIENT_SLOT(17) CLIENT_SLOT(18) CLIENT_SLOT(19)
	CLIENT_SLOT(20) CLIENT_SLOT(21) CLIENT_SLOT(22) CLIENT_SLOT(23) CLIENT_SLOT(24)
	CLIENT_SLOT(25) CLIENT_SLOT(26) CLIENT_SLOT(27) CLIENT_SLOT(28) CLIENT_SLOT(29)
	CLIENT_SLOT(30)
#undef CLIENT_SLOT
	virtual UnsignedInt getFrame(); // slot 0x7C
};
extern GameClient *TheGameClient;

class Drawable
{
public:
	void setInstanceMatrix(const Matrix3D *instance, bool preservePrevious);

private:
	unsigned char m_pad000[0x170];
	Matrix3D m_previousInstance; // +0x170
	Matrix3D m_instance; // +0x1A0
	unsigned char m_pad1d0[0x204 - 0x1D0];
	UnsignedInt m_expirationDate; // +0x204
	unsigned char m_pad208[0x378 - 0x208];
	UnsignedInt m_frame; // +0x378
	unsigned char m_pad37c[0x43F - 0x37C];
	bool m_instanceIsIdentity; // +0x43F
};

// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z
void Drawable::setInstanceMatrix(const Matrix3D *instance, bool preservePrevious)
{
	m_previousInstance = m_instance;
	if (instance)
	{
		m_instance = *instance;
		m_instanceIsIdentity = false;
	}
	else
	{
		m_instance.Make_Identity();
		m_instanceIsIdentity = true;
	}

	if (preservePrevious)
		m_previousInstance = m_instance;

	Real frame = (Real)TheGameEngine->m_frame;
	frame += (Real)TheGameClient->getFrame();
	m_frame = (UnsignedInt)frame;
	m_expirationDate = 0xffffffff;
}
