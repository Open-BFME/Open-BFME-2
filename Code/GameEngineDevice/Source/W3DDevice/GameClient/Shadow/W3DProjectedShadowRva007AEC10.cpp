// cl: /DNDEBUG /MD
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

class W3DShadowTexture
{
public:
	virtual void Delete_This(void) = 0;
	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
	unsigned long m_refs;
};

class RenderObjClass
{
public:
	virtual void Delete_This(void) = 0;
	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
	unsigned long m_refs;
};

// Partial observed view: pool recycling calls retail 0x007AEC10 on the
// unchanged shadow receiver. This is separate from complete destruction
// at 0x007AFF00; retain an address-qualified method until its name is proven.
class W3DProjectedShadow
{
public:
	void rva007AEC10(void);
	void rva00108931(void);
	void rva00108951(void);

private:
	unsigned char m_shadowData00[0x08];
	float m_x, m_y, m_z;		// +0x08
	unsigned char m_shadowData14[0x20 - 0x14];
	float m_localAngle;			// +0x20
	unsigned char m_shadowData24[0x28 - 0x24];
	int m_diffuse;				// +0x28
	unsigned char m_shadowData2C[0x68 - 0x2C];
	W3DShadowTexture *m_shadowTexture[2];
	RenderObjClass *m_robj;
};

void W3DProjectedShadow::rva007AEC10(void)
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_shadowTexture[i] != 0)
		{
			m_shadowTexture[i]->Release_Ref();
			m_shadowTexture[i] = 0;
		}
	}
	if (m_robj != 0)
	{
		m_robj->Release_Ref();
		m_robj = 0;
	}
}

// Retail 0x00108931 (32 bytes), between the two bodies above and below it:
// sets +0x28 to -1, drops the first reference slot without releasing it, and
// zeroes the floats at +0x10, +0x0C, +0x08 and +0x20. No direct call or
// address reference reaches it in retail, so its name stays address-derived.
void W3DProjectedShadow::rva00108931(void)
{
	m_diffuse = -1;
	m_shadowTexture[0] = 0;
	m_z = 0.0f;
	m_y = 0.0f;
	m_x = 0.0f;
	m_localAngle = 0.0f;
}

void W3DProjectedShadow::rva00108951(void)
{
	W3DShadowTexture *texture = m_shadowTexture[0];
	if (texture != 0)
	{
		texture->Release_Ref();
		m_shadowTexture[0] = 0;
	}
}
