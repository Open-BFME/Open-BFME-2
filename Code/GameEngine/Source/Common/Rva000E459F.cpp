// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva000E459F@Rva000E459F@@QAE_NXZ retail 0x000E459F 315B
// Evidence: chain from 0x00272C9E Drawable::rva00272C9E plus pin getTransformMatrix; callers 0x000E5B57; matrix at +0x50 floats +0x84 +0x88 flag +0x98 Drawable +0x2C
class Matrix3D
{
public:
	float m[3][4];
};

class Drawable
{
public:
	float rva00272C9E(int key);
	const Matrix3D *getTransformMatrix() const;
};

#include "ascii_string.h"

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva000E459F
{
public:
	bool rva000E459F();
	void rva000E46DA(Drawable *d, const AsciiString &a1, const AsciiString &a2, bool b82, bool b81);
private:
	char m_pad00[0x2C];
	Drawable *m_2C;
	char m_pad30[0x1C];
	int m_4C;
	Matrix3D m_50;
	bool m_80;
	bool m_81;
	bool m_82;
	char m_pad83[1];
	float m_84;
	float m_88;
	AsciiString m_8C;
	AsciiString m_90;
	char m_pad94[4];
	int m_98;
	bool m_9C;
};

bool Rva000E459F::rva000E459F()
{
	if (!m_2C || m_98 != 1)
		return false;
	bool changed = false;
	float v;
	if (m_88 != 0.0f) {
		v = m_84 + m_88;
		if (v < 0.0f)
			v = 0.0f;
		if (v > 1.0f)
			v = 1.0f;
	} else {
		v = m_2C->rva00272C9E(0);
		const Matrix3D *m1 = m_2C->getTransformMatrix();
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (m_50.m[i][j] != m1->m[i][j])
					goto copy_mat;
			}
		}
		goto have_v;
	copy_mat: {
		const int *s = (const int *)m_2C->getTransformMatrix();
		int *d = (int *)&m_50;
		d[0] = s[0];
		d[1] = s[1];
		d[2] = s[2];
		d[3] = s[3];
		d[4] = s[4];
		d[5] = s[5];
		d[6] = s[6];
		d[7] = s[7];
		d[8] = s[8];
		d[9] = s[9];
		d[10] = s[10];
		d[11] = s[11];
		changed = true;
	}
	have_v:;
	}
	if (m_84 != v) {
		m_84 = v;
		changed = true;
	}
	return changed;
}

void Rva000E459F::rva000E46DA(Drawable *d, const AsciiString &a1, const AsciiString &a2, bool b82, bool b81)
{
	m_2C = d;
	int v;
	if (d)
		v = ((Rva0055A88BDwordField *)d)->get();
	else
		v = 0;
	m_4C = v;
	m_8C = a1;
	m_90 = a2;
	m_80 = (d != 0);
	m_81 = b81;
	m_82 = b82;
	m_9C = 0;
}
