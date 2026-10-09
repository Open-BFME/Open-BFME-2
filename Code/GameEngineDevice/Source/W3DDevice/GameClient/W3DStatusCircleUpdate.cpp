// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 f98983a7d W3DStatusCircle::updateScreenVB supplies the quad layout.
// Native 8E335..8E436 RET4 and W3DStatusCircle render caller 8E7A4 agree;
// target screen VB is +E4 and the shared dirty byte is VA DE207C. Earlier
// bank called this TerrainTracksRenderObjClass; the semantic donor identifies
// the status-circle subsystem. -1/+1 are compiler literals, independently
// verified in target .rdata; declaring them extern globals hoisted the load.
class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *b, int flags);
		~WriteLockClass();
		VertexBufferClass *m_buf;
		void *Vertices;
		char m_lock;
	};
};

struct StatusVert
{
	float x, y, z;
	unsigned int color;
	float u, v;
};




class W3DStatusCircle { public: int updateScreenVB(int); char head[0xE4]; VertexBufferClass *m_vb2; };
extern unsigned char g_trackDirty;
int W3DStatusCircle::updateScreenVB(int color)
{
	VertexBufferClass *vb = (VertexBufferClass *)m_vb2;
	if (vb != 0)
	{
		g_trackDirty = false;
		VertexBufferClass::WriteLockClass lock(vb, 0);
		StatusVert *v = (StatusVert *)lock.Vertices;
		unsigned c = color;
		float a = -1.0f;
		v->color = c;
		float b = 1.0f;
		v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f;
		return 0;
	}
	return -1;
}
