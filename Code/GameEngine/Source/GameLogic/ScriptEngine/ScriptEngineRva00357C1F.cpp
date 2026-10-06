// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00357C1F@ScriptEngine@@QAEXPAX0@Z, retail 0x00357C1F 75B chain.
// Evidence: calls ScriptEngine 0x00357340 just landed; EBP frame with 12B
// Coord3D temp; movss x/y spill and restore needs /arch:SSE.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Coord3D : public Coord3DBase
{
public:
	void normalize();
};

struct Vec2XY
{
	float x;
	float y;
};

class ScriptEngine
{
public:
	void rva00357340(void *p, Coord3D *dst);
	void rva00357C1F(void *p, void *v);
};

void ScriptEngine::rva00357C1F(void *p, void *v)
{
	if (!p)
		return;
	Vec2XY *dst2 = (Vec2XY *)v;
	if (!dst2)
		return;
	Coord3D tmp;
	tmp.x = dst2->x;
	tmp.y = dst2->y;
	rva00357340(p, &tmp);
	dst2->x = tmp.x;
	dst2->y = tmp.y;
}
