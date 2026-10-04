// ?rva000854F9@Rva000854F9HeightView@@QBEHXZ
// partial score=0.75 date=2026-10-05
// Boundary-review draft only: inferred complete854F9/22 between priorRET854F8
// and next rowed method8550F/7. Internal JBE85506 reaches the old zero arm8550C.
// No independently witnessed parent-entry reference; cannot assert recovery.
// Native call resolves to rowed Thing::getHeightAboveTerrainOrWater30A4D0/88;
// only that established const-thiscall declaration is used, with no layout,
// vtable, lifetime or ownership inference. Raw receiver address remains unchanged.
// cl: /O1 /Ob1 /G6
class Thing {public:float getHeightAboveTerrainOrWater() const;};
class Rva000854F9HeightView {public:int rva000854F9() const;};
int Rva000854F9HeightView::rva000854F9() const {return reinterpret_cast<const Thing *>(this)->getHeightAboveTerrainOrWater()>0.0f ? 1 : 0;}
