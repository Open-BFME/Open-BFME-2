// cl: /DNDEBUG /MD /EHsc
// ?rva000D0091@W3DStreakDraw@@QAEXXZ @0x000D0091 534B
// W3DStreakDraw streak body. Reference: BFME1
// reference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawBody.cpp
// (streakBody0077D6B0). Same shape: null-guarded streak, rope position,
// count-driven Add/Get/Set/Delete point flow with length/segment pruning,
// then color/opacity tail. BFME2 differences measured from retail: tail uses
// Drawable::rva00272C9E(0) opacity with Additive-gated color scaling and the
// Rva00167EF8 vector plus Rva00167F15FloatField opacity stores; callees are
// the rowed BFME2 names.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct Rva00167EF8Rec
{
	float x;
	float y;
	float z;
};


class Drawable
{
public:
	float rva00272C9E(int key);
public:
	const Coord3D *getPosition() const;
};

class SidesList
{
public:
	int getNumSkirmishSides();
};

class Rva00168690
{
public:
	void rva00168690(const Vector3 &v, float f);
	void rva001686BA(int index);
};

class Rva001680A6
{
public:
	void rva001680A6(int index, void *src, float f);
	void rva001680ED(int index, void *dst, float *out);
};

class Rva00167EF8
{
public:
	void rva00167EF8(const Rva00167EF8Rec &src);
};

class Rva00167F15FloatField
{
public:
	void set(float newValue);
};

class W3DStreakDrawModuleData
{
public:
	unsigned char m_pad00[8];
	float m_length;
	float m_width;
	bool m_additive;
	unsigned char m_pad11[3];
	float m_colorX;
	float m_colorY;
	float m_colorZ;
	int m_numSegments;
};

class W3DStreakDraw
{
public:
	void rva000D0091();
	void rva000D0459(void *a, void *b, void *c);
	void rva000D0461(void *a);

private:
	void *m_vtable;
	const W3DStreakDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	void *m_streak;
};

void W3DStreakDraw::rva000D0091()
{
	const W3DStreakDrawModuleData *data = m_moduleData;
	if (m_streak == 0)
		return;
	const Vector3 *position = (const Vector3 *)m_drawable->getPosition();
	Vector3 point;
	float pointWidth;
	if (((SidesList *)m_streak)->getNumSkirmishSides() == 0)
	{
		((Rva00168690 *)m_streak)->rva00168690(*position, 0.0f);
	}
	else
	{
		if (((SidesList *)m_streak)->getNumSkirmishSides() == 1)
		{
			((Rva001680A6 *)m_streak)->rva001680ED(0, &point, &pointWidth);
			float x = position->X - point.X;
			float y = position->Y - point.Y;
			float z = position->Z - point.Z;
			float square = x * x + y * y + z * z;
			float distance;
			__asm
			{
				fld square
				fsqrt
				fstp distance
			}
			pointWidth = distance + pointWidth;
			((Rva00168690 *)m_streak)->rva00168690(*position, pointWidth);
		}
		else
		{
			((Rva001680A6 *)m_streak)->rva001680ED(((SidesList *)m_streak)->getNumSkirmishSides() - 2, &point, &pointWidth);
			float x = position->X - point.X;
			float y = position->Y - point.Y;
			float z = position->Z - point.Z;
			float square = x * x + y * y + z * z;
			float distance;
			__asm
			{
				fld square
				fsqrt
				fstp distance
			}
			pointWidth = distance + pointWidth;
			((Rva001680A6 *)m_streak)->rva001680A6(((SidesList *)m_streak)->getNumSkirmishSides() - 1, (void *)position, pointWidth);
			float limit = data->m_length / (float)(unsigned int)data->m_numSegments;
			if (limit < distance)
				((Rva00168690 *)m_streak)->rva00168690(*position, pointWidth);
			while (((SidesList *)m_streak)->getNumSkirmishSides() >= 2)
			{
				float pruneWidth;
				((Rva001680A6 *)m_streak)->rva001680ED(1, &point, &pruneWidth);
				if (!(pointWidth - data->m_length > pruneWidth))
					break;
				((Rva00168690 *)m_streak)->rva001686BA(0);
			}
		}
	}
	pointWidth = ((Drawable *)m_drawable)->rva00272C9E(0);
	if (data->m_additive)
	{
		point.X = pointWidth * data->m_colorX;
		point.Y = pointWidth * data->m_colorY;
		point.Z = pointWidth * data->m_colorZ;
		((Rva00167EF8 *)m_streak)->rva00167EF8((Rva00167EF8Rec &)point);
		((Rva00167F15FloatField *)m_streak)->set(1.0f);
	}
	else
	{
		point.X = data->m_colorX;
		point.Y = data->m_colorY;
		point.Z = data->m_colorZ;
		((Rva00167EF8 *)m_streak)->rva00167EF8((Rva00167EF8Rec &)point);
		((Rva00167F15FloatField *)m_streak)->set(pointWidth);
	}
}

// ?rva000D0459@W3DStreakDraw@@QAEXPAX00@Z @0x000D0459 8B and
// ?rva000D0461@W3DStreakDraw@@QAEXPAX@Z @0x000D0461 8B, right after the
// class's scalar deleting destructor: slots 38 (three stack arguments) and 11
// (one) of the W3DStreakDraw vtable. Both ignore their arguments and rebuild
// the streak through the body above. Address-named; argument types unknown.
void W3DStreakDraw::rva000D0459(void *, void *, void *)
{
	rva000D0091();
}

void W3DStreakDraw::rva000D0461(void *)
{
	rva000D0091();
}
