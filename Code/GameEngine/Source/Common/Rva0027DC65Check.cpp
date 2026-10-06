// cl: /MD
// ?Rva0027DC65Check@@YAEPAM@Z, retail 0x0027DC65, 141 bytes.
// Free __cdecl check on 3-float point: null TerrainLogic -> 0; getExtent
// bounds (lo.x<p.x<hi.x, lo.y<p.y<hi.y) else refresh via slot13 copy;
// then slot19 with (p.x,p.y,0,0,0) and return inverted unsigned char.
// Evidence: TheTerrainLogic 0x009FEC50, slots 0x20/0x34/0x4c, callers huge.
struct Region3D
{
	float loX;
	float loY;
	float loZ;
	float hiX;
	float hiY;
	float hiZ;
};

struct Triple
{
	float x;
	float y;
	float z;
};

class TerrainLogic
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void getExtent(Region3D *r);
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual Triple *slot13(Triple *tmp, float *p);
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual bool slot19(float x, float y, float *a, float *b, bool *c);
};

extern TerrainLogic *TheTerrainLogic;

unsigned char __cdecl Rva0027DC65Check(float *p)
{
	if (TheTerrainLogic != 0) {
		Region3D r;
		TheTerrainLogic->getExtent(&r);
		if (p[0] > r.loX && r.hiX > p[0] && p[1] > r.loY && r.hiY > p[1])
			goto done;
		{
			Triple tmp;
			Triple *res = TheTerrainLogic->slot13(&tmp, p);
			*(Triple *)p = *res;
		}
	done:
		return !TheTerrainLogic->slot19(p[0], p[1], 0, 0, 0);
	}
	return 0;
}
