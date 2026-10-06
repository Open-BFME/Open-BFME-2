// cl: /O1 /Ob1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva000854F9@Rva000854F9HeightView@@QBEHXZ, retail 0x000854F9 (22 bytes).
// Target evidence: the body runs from just after the RET at 0x000854F8 (end
// of 0x000854EC) to the RET before the rowed byte getter 0x0008550F; its JBE
// at 0x00085506 reaches the xor/ret false arm at 0x0008550C (retired as a
// separate row). It calls the rowed Thing::getHeightAboveTerrainOrWater
// (0x0030A4D0) on its own this and returns whether the height is above
// zero; no caller is witnessed, so the class name stays a view.
// /G7 /arch:SSE give retail's fldz/fxch/fcomip compare.
class Thing
{
public:
	float getHeightAboveTerrainOrWater() const;
};

class Rva000854F9HeightView
{
public:
	int rva000854F9() const;
};

int Rva000854F9HeightView::rva000854F9() const
{
	return reinterpret_cast<const Thing *>(this)->getHeightAboveTerrainOrWater() > 0.0f ? 1 : 0;
}
