// ?Rva001E40D9Get@@YGMMM@Z
// cl: /O1 /MD /arch:SSE
//
// ?Rva001E40D9Get@@YGMMM@Z @0x001E40D9 89B
// __stdcall terrain height at x,y via TheTerrainLogic: try slot 0x4c with out
// local then return it else slot 0x18; original helper name unresolved; callers 0x001E811F 0x001E8351 in 0x001E7ECA.
class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual float Method06(float x, float y, int z);
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual bool Method19(float x, float y, float *out, int a, int b);
};
extern TerrainLogic *TheTerrainLogic;
float __stdcall Rva001E40D9Get(float x, float y)
{
	float out;
	if (TheTerrainLogic->Method19(x, y, &out, 0, 0))
	{
        // Preserve the native SSE copy to the parameter home before its x87 load.
        y = TheTerrainLogic != 0 ? *(volatile float *)&out : *(volatile float *)&out;
        return y;
	}
	return TheTerrainLogic->Method06(x, y, 0);
}
