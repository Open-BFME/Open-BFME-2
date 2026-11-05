### LINK-198: QuadStrip2D insert 0x00538944 carries the donor name W3DAnimationInfo for the float4 record
Status: Blocked on a naming decision. Updated: 2026-11-04; inspected revision: 3d9f2fc655.
Evidence / affected units: `W3DAnimationInfoVectorInsert.cpp` (real-link blocker: `??0W3DAnimationInfo@@QAE@ABV0@@Z`, its Construct, overflow, `_M_clear`, `allocate`, uninitialized copy/fill are unresolved or non-retail); `QuadStrip2D.cpp` (`insertStrip`), `Rva0030BE41.cpp` (`rva0030BC2B`); retail calls the rowed `BfmeFloat4Record00469C61` helpers 0x00469C61/0x0047008E, and `QuadStrip2D::m_vec` is used as `vector<BfmeFloat4Record00469C61>` elsewhere, while the real W3DAnimationInfo (W3DModelDraw) has a destructor. Evidence: reverse/attempt_support/w3danimationinfo-insert-538944-20261104/readme.md
Completed: none kept. An ICF-twin provider in `stlport_vector_float4_469c61.cpp` previewed both units as LINKS but gives two classes one name (`_Destroy<W3DAnimationInfo*>` collides with W3DModelDraw's), so it was reverted.
Remaining / next check: decide the element's name (docs/naming.md; the readable donor spelling cannot be folded into the placeholder by `rename.py class --fold`), respell the three rows onto it, then `link_check` the insert unit, `QuadStrip2D.cpp` and `W3DModelDraw.cpp`.
Clearance: pending.
Census confirmation: not claimed.

2026-11-05: [Consolidation prerequisite trial](../../reverse/attempt_support/quadstrip-merge-noinline-20261105.md) rejects the insert donor on bytes even with explicit noinline copy declarations; all 19 separate rows pass, edits reverted. Do not retry that isolated knob before identity/provider reconciliation.
