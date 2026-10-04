// cl: /O1 /MD
// ?rva00271423@Rva00271423@@QAEPAVMatrix3D@@XZ retail 0x00271423 115B.
// Time-gated Matrix3D interpolate: if m_378 <= GetTime return m_1a0, if m_204 == GetTime return m_1d0,
// else Lerp(m_170, m_1a0, TheGameEngine+0x3c, m_1d0), cache time, return m_1d0.
// Evidence: callers 0x0027BF32 in 0x0027BED0, callee Lerp rowed 0x00713AB0, TheGameClient slot 0x7c GetTime, TheGameEngine float +0x3c.

class Matrix3D
{
public:
	static void Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result);
	float m[12];
};

class ClientFrameSubsystem
{
public:
	virtual void f00();
	virtual void f04();
	virtual void f08();
	virtual void f0C();
	virtual void f10();
	virtual void f14();
	virtual void f18();
	virtual void f1C();
	virtual void f20();
	virtual void f24();
	virtual void f28();
	virtual void f2C();
	virtual void f30();
	virtual void f34();
	virtual void f38();
	virtual void f3C();
	virtual void f40();
	virtual void f44();
	virtual void f48();
	virtual void f4C();
	virtual void f50();
	virtual void f54();
	virtual void f58();
	virtual void f5C();
	virtual void f60();
	virtual void f64();
	virtual void f68();
	virtual void f6C();
	virtual void f70();
	virtual void f74();
	virtual void f78();
	virtual unsigned int GetTime();
};

extern ClientFrameSubsystem *TheGameClient;

class GameEngine
{
public:
	char m_pad[0x3c];
	float m_3c;
};

extern GameEngine *TheGameEngine;

class Rva00271423
{
public:
	Matrix3D *rva00271423();

private:
	char m_pre[0x170];
	Matrix3D m_170;
	Matrix3D m_1a0;
	Matrix3D m_1d0;
	char m_pad200[0x4];
	unsigned int m_204;
	char m_pad208[0x170];
	unsigned int m_378;
};

Matrix3D *Rva00271423::rva00271423()
{
	if (m_378 <= TheGameClient->GetTime())
		return &m_1a0;
	if (m_204 != TheGameClient->GetTime()) {
		Matrix3D::Lerp(m_170, m_1a0, TheGameEngine->m_3c, m_1d0);
		m_204 = TheGameClient->GetTime();
	}
	return &m_1d0;
}
