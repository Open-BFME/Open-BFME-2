// cl: /DNDEBUG /MD
// ?rva000B2FBB@Rva000B2FBB@@QAEXMPBVMatrix3D@@@Z 0x000B2FBB 144B evidence: float to +0x2c0 48B Matrix3D copy +0x290 Thing at +8 setTransformMatrix rowed TheGameClient slot0x7c int to +0x2c4; neighbours 0x000B2F38/0x000B304B
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

struct M16
{
	int a; int b; int c; int d;
};

#include "Thing/thing.h"

class ClientFrameSubsystem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual int s31();
};

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva000B2FBB
{
	char _p0[8];
	Thing *m_thing;
	char _p1[0x290 - 8 - 4];
	Matrix3D m_mat;
	float m_f2c0;
	int m_i2c4;
public:
	void rva000B2FBB(float scale, const Matrix3D *m);
};

void Rva000B2FBB::rva000B2FBB(float scale, const Matrix3D *matrix3D)
{
	m_f2c0 = scale;
	*(int *)&m_mat.Row[0].X = *(const int *)&matrix3D->Row[0].X;
	*(int *)&m_mat.Row[0].Y = *(const int *)&matrix3D->Row[0].Y;
	*(int *)&m_mat.Row[0].Z = *(const int *)&matrix3D->Row[0].Z;
	*(int *)&m_mat.Row[0].W = *(const int *)&matrix3D->Row[0].W;
	int *row1 = (int *)&m_mat.Row[1].X;
	row1[0] = *(const int *)&matrix3D->Row[1].X;
	row1[1] = *(const int *)&matrix3D->Row[1].Y;
	row1[2] = *(const int *)&matrix3D->Row[1].Z;
	row1[3] = *(const int *)&matrix3D->Row[1].W;
	int *row2 = (int *)&m_mat.Row[2].X;
	row2[0] = *(const int *)&matrix3D->Row[2].X;
	row2[1] = *(const int *)&matrix3D->Row[2].Y;
	row2[2] = *(const int *)&matrix3D->Row[2].Z;
	row2[3] = *(const int *)&matrix3D->Row[2].W;
	m_thing->setTransformMatrix(matrix3D);
	m_i2c4 = ((ClientFrameSubsystem *)TheGameClient)->s31();
}
