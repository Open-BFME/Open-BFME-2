// ?getPosition@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@@MMHH@Z
// Retail 0x0055DDD1, 1295 bytes, with its EH handler 0x007999A7. The two inline copies of
// Zero Hour's Matrix3D::Inverse_Transform_Vector keep ZH's left-deep X/Y rows; only the Z rows
// are regrouped. The second copy's Z row parenthesizes its first product: a parenthesized
// float term is a paren node in c2 3077's IL and reaches FactCanonSort as a hash-var temporary
// keyed above the plain products, so A02*dx leads the sum and the second diff colours
// dx/dy/dz xmm0/1/2 as retail (traced; reverse/attempt_support/fp-paren-nodes-20261020.md).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
#include "matrix3d.h"
#include "wwmath.h"

// Select-any copies of the rowed coord3d.cpp bodies 0x00003571 and 0x000035B6: with both visible,
// cl knows normalize does not leak its object, so the direction shares the end point's frame slot.
__declspec(noinline) inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}


__forceinline void ITR1(const Matrix3D & matrix3D,const Vector3 & in,Vector3 * out)
{
	Vector3 tmp;
	Vector3 * v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}
	out->X = (matrix3D[0][0] * v->X + matrix3D[1][0] * v->Y + matrix3D[2][0] * v->Z);
	out->Y = (matrix3D[0][1] * v->X + matrix3D[1][1] * v->Y + matrix3D[2][1] * v->Z);
	out->Z = (matrix3D[0][2] * v->X + (matrix3D[1][2] * v->Y + matrix3D[2][2] * v->Z));
}
__forceinline void ITV1(const Matrix3D & matrix3D,const Vector3 & in,Vector3 * out)
{
	Vector3 tmp;
	Vector3 * v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}
	Vector3 diff(v->X - matrix3D[0][3], v->Y - matrix3D[1][3], v->Z - matrix3D[2][3]);
	ITR1(matrix3D, diff, out);
}

// A parenthesized float subexpression is a paren IL node: (A[0][2] * v->X) reaches the final
// canonical sort as a temporary keyed above the plain products, so it leads the Z sum and is the
// destination, as in retail's second transform. ITR1's grouped Z sum leads with A[2][2]*z instead.
__forceinline void ITR2(const Matrix3D & matrix3D,const Vector3 & in,Vector3 * out)
{
	Vector3 tmp;
	Vector3 * v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}
	out->X = (matrix3D[0][0] * v->X + matrix3D[1][0] * v->Y + matrix3D[2][0] * v->Z);
	out->Y = (matrix3D[0][1] * v->X + matrix3D[1][1] * v->Y + matrix3D[2][1] * v->Z);
	out->Z = ((matrix3D[0][2] * v->X) + matrix3D[1][2] * v->Y + matrix3D[2][2] * v->Z);
}
__forceinline void ITV2(const Matrix3D & matrix3D,const Vector3 & in,Vector3 * out)
{
	Vector3 tmp;
	Vector3 * v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}
	Vector3 diff(v->X - matrix3D[0][3], v->Y - matrix3D[1][3], v->Z - matrix3D[2][3]);
	ITR2(matrix3D, diff, out);
}
class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class ParticleSystem;
ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	~RvaSmartPtr12() throw()
	{
		if (m_ptr != 0)
			rva0004CBC0();
	}
	ParticleSystem *system() const { return m_ptr == 0 ? Make001FCBD7() : m_ptr; }
	ParticleSystem *m_ptr;
	int m_04;
	int m_08;
};

class Rva0055DDB6SmartField
{
public:
	RvaSmartPtr12 get() const throw();
};

struct ParticleSystemView
{
	char pad[0xBC];
	Matrix3D m_transform;
	char pad2[0x188 - 0xBC - sizeof(Matrix3D)];
	Vector3 m_position;
	bool m_isLocal;
};

namespace FXParticleSystem
{

class __declspec(novtable) ParticleModulePrimary
{
public:
	virtual ~ParticleModulePrimary() = 0;

private:
	unsigned char m_state[0x10];
};

class __declspec(novtable) ParticleModuleClassInterface
{
public:
	virtual void *getModuleClass() const = 0;
};

class __declspec(novtable) EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float, float) = 0;
};

template <int Category>
class DefaultParticleModule
	: public ParticleModulePrimary,
	  public ParticleModuleClassInterface,
	  public EmissionVolumeModuleInterface
{
};

class __declspec(novtable) EmissionVolumeInfo
{
public:
	virtual ~EmissionVolumeInfo() = 0;

protected:
	bool m_is_hollow;
	unsigned char m_alignment[3];
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
protected:
	Coord3D m_start;
	Coord3D m_end;
	GameClientRandomVariable m_amplitude1;
	GameClientRandomVariable m_frequency1;
	GameClientRandomVariable m_phase1;
	GameClientRandomVariable m_amplitude2;
	GameClientRandomVariable m_frequency2;
	GameClientRandomVariable m_phase2;
	GameClientRandomVariable m_amplitude3;
	GameClientRandomVariable m_frequency3;
	GameClientRandomVariable m_phase3;
};

class LightningEmissionModule
	: public DefaultParticleModule<5>, public LightningEmissionInfo
{
public:
	virtual Coord3D getPosition(float, float, int, int);
};

// Index 0 rebuilds the static path: count points from start to end (in the system's local space
// when it is local), displaced along cross(up, direction) by three enveloped sine waves.
Coord3D LightningEmissionModule::getPosition(float, float, int index, int count)
{
	Coord3D result;
	if (count > 1 && count < 30)
	{
		static Coord3D s_points[30];
		if (index == 0)
		{
			Coord3D start;
			Coord3D end;
			start = m_start;
			end = m_end;
			RvaSmartPtr12 handle = ((const Rva0055DDB6SmartField *)this)->get();
			if (((ParticleSystemView *)handle.system())->m_isLocal)
			{
				const Matrix3D &matrix3D = ((ParticleSystemView *)handle.system())->m_transform;
				Vector3 localStart;
				ITV1(matrix3D, matrix3D.Get_Translation(), &localStart);
				start = *(Coord3D *)&localStart;
				const Vector3 *p = &((ParticleSystemView *)handle.system())->m_position;
				Vector3 localEnd;
				ITV2(matrix3D, Vector3(p->X, p->Y, p->Z), &localEnd);
				end = *(Coord3D *)&localEnd;
			}
			Coord3D delta;
			delta.x = end.x - start.x;
			delta.y = end.y - start.y;
			delta.z = end.z - start.z;
			float amplitude1 = m_amplitude1.getValue();
			float frequency1 = m_frequency1.getValue();
			float phase1 = m_phase1.getValue();
			float amplitude2 = m_amplitude2.getValue();
			float frequency2 = m_frequency2.getValue();
			float phase2 = m_phase2.getValue();
			float amplitude3 = m_amplitude3.getValue();
			float frequency3 = m_frequency3.getValue();
			float phase3 = m_phase3.getValue();
			Coord3D dir = delta;
			dir.normalize();
			Coord3D up(0.0f, 0.0f, 1.0f);
			Coord3D perp(up.y * dir.z - up.z * dir.y,
				up.z * dir.x - up.x * dir.z,
				up.x * dir.y - up.y * dir.x);
			float step = 1.0f / (float)(count - 1);
			float t = 0.0f;
			for (int i = 0; i < count; ++i)
			{
				Coord3D *pt = &s_points[i];
				float envelope = 0.5f - WWMath::Fabs(0.5f - t);
				float s1 = WWMath::Sin(t * frequency1 + phase1) * envelope * amplitude1;
				float s2 = WWMath::Sin(t * frequency2 + phase2) * envelope * amplitude2;
				float s3 = WWMath::Sin(t * frequency3 + phase3) * envelope * amplitude3;
				float x = t * delta.x + start.x;
				x += perp.x * s1;
				x += perp.x * s2;
				x += perp.x * s3;
				pt->x = x;
				float y = t * delta.y + start.y;
				y += perp.y * s1;
				y += perp.y * s2;
				y += perp.y * s3;
				pt->y = y;
				float z = t * delta.z + start.z;
				z += perp.z * s1;
				z += perp.z * s2;
				z += perp.z * s3;
				pt->z = z;
				t += step;
			}
		}
		result.x = s_points[index].x;
		result.y = s_points[index].y;
		result.z = s_points[index].z;
	}
	return result;
}

}
