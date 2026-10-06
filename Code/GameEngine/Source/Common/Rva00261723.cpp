// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00261723@Rva00261723@@QAE_NPAVArg00261723@@@Z, retail 0x00261723, 45 bytes.
// Float-to-ICoord helper: cvttss2si arg +0x38/+0x3C floats to ICoord x/y with
// z 0, then PolygonTrigger::pointInTrigger (pin 0x002E3A13) on this +0x08.
// Evidence: arg float offsets match Rva000CBA20 +0x38 layout Sumatra-side;
// this +0x08 pointer and ICoord x/y/z layout match retail immediates;
// neighbours 0x002615E3 (Rva000CBA20DistSq /O2) and 0x0026185B (Rva0026185B
// /O1 /G7) frame the 00261xxx Common page; donor pointInTrigger in BFME1
// PolygonTrigger_pointInTrigger.cpp and ZH PolygonTrigger.cpp.

typedef bool Bool;

class ICoord3D
{
public:
	int x;
	int y;
	int z;
};

class PolygonTrigger
{
public:
	Bool pointInTrigger(const ICoord3D &pt);
};

class Arg00261723
{
public:
	unsigned char m_pad[0x38];
	float m_fx38;
	float m_fy3C;
};

class Rva00261723
{
public:
	Bool rva00261723(Arg00261723 *arg);

private:
	unsigned char m_pad00[8];
	PolygonTrigger *m_trig08;
};

Bool Rva00261723::rva00261723(Arg00261723 *arg)
{
	ICoord3D pt;
	pt.x = (int)arg->m_fx38;
	pt.y = (int)arg->m_fy3C;
	pt.z = 0;
	return m_trig08->pointInTrigger(pt);
}
