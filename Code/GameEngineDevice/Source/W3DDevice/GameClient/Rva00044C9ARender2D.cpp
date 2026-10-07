// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient

class RectClass
{
public:
	float left;
	float top;
	float right;
	float bottom;
};

class Render2DClass
{
public:
	char m_padToFlag[0x48];
	char m_flag;
	void Add_Quad(const RectClass &, unsigned long);
};

// ?rva00044C9A@Rva00044C9A@@UAEXMMMMK@Z @0x00044C9A 229B
// Target evidence: central table slot 57 at 0x007C3C80; target calls the
// rowed Render2DClass::Add_Quad. Class identity is address-derived; field
// roles and the clip rectangle layout are structural inference from offsets.
class Rva00044C9A
{
public:
	virtual void rva00044C9A(float, float, float, float, unsigned long);

private:
	char m_padToRenderer[0x164];
	Render2DClass *m_renderer;
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
	unsigned char m_clipEnabled;
};

void Rva00044C9A::rva00044C9A(float x, float y, float width, float height, unsigned long color)
{
	m_renderer->m_flag = 0;
	if (m_clipEnabled != 0)
	{
		float right = x + width - 1.0f;
		float bottom = y + height - 1.0f;
		float leftLimit = (float)m_left;
		if (leftLimit > x)
			x = leftLimit;
		float topLimit = (float)m_top;
		if (topLimit > y)
			y = topLimit;
		float rightLimit = (float)m_right;
		if (right > rightLimit)
			right = rightLimit;
		float bottomLimit = (float)m_bottom;
		if (bottom > bottomLimit)
			bottom = bottomLimit;
		if (x > right || y > bottom)
			return;
		RectClass rect = { x, y, right, bottom };
		m_renderer->Add_Quad(rect, color);
	}
	else
	{
		RectClass rect = { x, y, x + width, y + height };
		m_renderer->Add_Quad(rect, color);
	}
}
