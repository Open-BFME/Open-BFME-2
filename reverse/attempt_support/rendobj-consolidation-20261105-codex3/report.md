# RenderObj constructor consolidation prerequisite

Inspected revision: `85b46a09f34220f2b5c6b55bdbac33a595d943b5`.

The fresh in-memory TU map approves the default constructor at RVA 0x0013BF00 for `Code/Libraries/Source/WWVegas/WW3D2/rendobj.cpp`. The scoped evidence planner reports compiler/include and duplicate anchor context prerequisites. The other seven mixed files remain outside this merge.

The original dry run accepted no donors: the default constructor would select a non-retail `RefCountClass` deleting destructor; Intersect would introduce a duplicate RayCollisionTestClass constructor; copy and filename donors fail bytes. See before-merge.txt.

Move the existing size-optimization/refcount include block before rendobj.h first includes refcount.h. No pragma or other hatch is added. This changes declaration compilation context, not class layout. All 25 existing rows pass the scoped builder and declared-unmatched check. Both before and after previews LINKS for the seed's same 2,008 authored bytes, against census c95fcfcfcd (2026-11-05 05:17). These are predictions, not a census gain.

The second dry run accepts the seed and RenderObjCtor.cpp, with 26 exact rows and the current link guard passing. Three other donors remain refused for their original byte/link prerequisites. The planned merge removes one file. Merge and path-consumer audit follow in a separate commit.
