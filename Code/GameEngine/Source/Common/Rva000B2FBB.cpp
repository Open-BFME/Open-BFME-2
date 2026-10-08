// cl: /DNDEBUG /MD
// ?rva000B2FBB@Rva000B2FBB@@QAEXMPBVMatrix3D@@@Z 0x000B2FBB 144B evidence: float to +0x2c0 48B Matrix3D copy +0x290 Thing at +8 setTransformMatrix rowed TheGameClient slot0x7c int to +0x2c4; neighbours 0x000B2F38/0x000B304B
class Matrix3D
{
public:
	int m00; int m01; int m02; int m03;
	int m10; int m11; int m12; int m13;
	int m20; int m21; int m22; int m23;
};

struct M16
{
	int a; int b; int c; int d;
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *m);
};

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
	void rva000B2FBB(float f, const Matrix3D *m);
};

void Rva000B2FBB::rva000B2FBB(float f, const Matrix3D *m)
{
	m_f2c0 = f;
	m_mat.m00 = m->m00;
	m_mat.m01 = m->m01;
	m_mat.m02 = m->m02;
	m_mat.m03 = m->m03;
	int *d1 = &m_mat.m10;
	d1[0] = m->m10;
	d1[1] = m->m11;
	d1[2] = m->m12;
	d1[3] = m->m13;
	int *d2 = &m_mat.m20;
	d2[0] = m->m20;
	d2[1] = m->m21;
	d2[2] = m->m22;
	d2[3] = m->m23;
	m_thing->setTransformMatrix(m);
	m_i2c4 = ((ClientFrameSubsystem *)TheGameClient)->s31();
}
