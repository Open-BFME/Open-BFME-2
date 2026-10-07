// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000D19F9 129B. Reads the node at +4, calls getPosition on the
// object at +8, forwards both into 0x000D18F8, then tints that object.

struct Coord3D;

struct RGBColor00271779
{
	float m_r;
	float m_g;
	float m_b;
};

class Rva00271779
{
public:
	void rva00271779(RGBColor00271779 color, int mode, int color0, int color1,
		float a, float b);
};

class Drawable
{
public:
	const Coord3D *getPosition() const;

	char m_pad[0x118];
	int m_flags;
};

struct Rva000D19F9Node
{
	char m_pad0[8];
	int m_at8;
	char m_padC[0x2C - 0xC];
	float m_at2C;
	char m_pad30[0x3C - 0x30];
	int m_at3C;
};

class Rva000D19F9
{
public:
	void rva000D18F8(int *at8, float value, const Coord3D *pos, int extra);
	void rva000D19F9();

	char m_pad[4];
	Rva000D19F9Node *m_node;
	Drawable *m_obj;
};

void Rva000D19F9::rva000D19F9()
{
	Drawable *obj = m_obj;
	int *at8 = &m_node->m_at8;
	float value = *(float *)((char *)at8 + 0x24);
	rva000D18F8(at8, value, obj->getPosition(), m_node->m_at3C);
	m_obj->m_flags |= 0x20;
	RGBColor00271779 color = {1.5f, 1.5f, 1.5f};
	((Rva00271779 *)m_obj)->rva00271779(color, 0x1E, 0xFFFFFF, 0xFFFFFF, 0.0f, 0.0f);
}
