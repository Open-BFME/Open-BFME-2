// cl: /O1 /G7 /arch:SSE /MD
// ?rva0027D1A4@TerrainLogic@@QAEXPBUCoord3D@@MH@Z retail 0x0027D1A4 (34
// bytes ret 0xC). Null-guarded forwarder via global 0x009FF080 to its slot
// 16 (0x40) with (pos radius int). Both callers (0x004C4A03 in
// TaintSpecialPower 0x004C49AE and 0x004C3B6C in the ElvenWood sibling) load
// TheTerrainLogic into ecx and the WorldBuilder twin 0x00C477B0 takes ecx
// as this: a TerrainLogic member that replaces ecx with the manager. Same
// manager family as Rva0027D3CBForward/Rva00306769Forward.
struct Coord3D;
extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager0027D1A4
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
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16(void *a, float b, int c);
};

#define TheRva009FF080Manager0027D1A4 (*(Rva009FF080Manager0027D1A4 **)&g_00DFF080)

class TerrainLogic
{
public:
	void rva0027D1A4(const Coord3D *pos, float radius, int arg);
};

void TerrainLogic::rva0027D1A4(const Coord3D *pos, float radius, int arg)
{
	Rva009FF080Manager0027D1A4 *manager = TheRva009FF080Manager0027D1A4;
	if (manager == 0)
		return;
	manager->_slot16((void *)pos, radius, arg);
}
