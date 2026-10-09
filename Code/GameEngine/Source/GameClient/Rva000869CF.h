// Rva000869CF: canonical target layout shared by its reset, history, and tail-jump views.
// Offsets follow the matched retail accessors at 0x000869CF, 0x00086A94, and 0x00088D0A.
#ifndef CANONICAL_RVA000869CF_H
#define CANONICAL_RVA000869CF_H

class Rva00088D0AMember
{
public:
	virtual float v0();
	virtual float v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7(float value);
};

class Rva000869CF
{
public:
	float *rva000869CF();
	void rva00088D0A(float value, int unused, float scale);
	void rva00086A94(int a, int b, float c);

	char m_pad0[0x4c];
	float m_4c;
	char m_pad50[0x58 - 0x50];
	int m_58;
	int m_5c;
	char m_pad60[0x8];
	float m_68;
	char m_pad6c[0x170];
	unsigned char m_1dc;
	char m_pad1dd[0x27];
	unsigned char m_204;
	char m_pad205[0x23];
	unsigned char m_228;
	char m_pad229[0x53];
	unsigned char m_27c;
	unsigned char m_27d;
	char m_pad27e[0x1468 - 0x27e];
	float m_1468;
	float m_146c;
	float m_1470[768];
	int m_2070;
	char m_pad2074[0x2354 - 0x2074];
	int m_2354;
	char m_pad2358[0x70];
	unsigned char m_23c8;
	char m_pad23c9[0x83];
	float m_244cArr[3];
	char m_pad2458[0x24c8 - 0x2458];
	Rva00088D0AMember m_24c8;
};

#endif // CANONICAL_RVA000869CF_H
