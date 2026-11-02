# Connected dynamic-mesh / shatter closure boundary

No Code or shared-header edit was made. Normal original baselines pass all
four dynamesh rows (113 B) and the one shatter Matrix3D::Scale row (133 B).
Immutable source/object snapshots are hash-bound to the recorded commit.

The dynamic-mesh constructor and Set_Vertex_Material are sole providers
called by current unrowed ShatterSystem::Process_Clip_Pools (REL32 offsets
122 and 392). Removing them alone would strand that emitter. Shatter's
primary donor functions have no outside indexed touches or alias routes;
its 78 outside-touched shared providers all have alternatives. A connected
closure reduction is a supported lead, subject to native/consumer checks.

Two prerequisites prevent applying that reduction now. First, the canonical
Matrix3DData storage header lacks a Scale(float) declaration. Using the
existing native body with that header requires adding its already-rowed
nonvirtual declaration; class:Matrix3D is held by another contributor. The
separately acquired header-file claim was released without editing it.
Do not add a second private canonical Matrix3D class or an emission anchor.

Second, dynamesh's native Peek_Single_Material body reads indexed +0xA4,
while the canonical MeshMatDesc Material array starts at +0xA8. The masked
body's exact bytes do not prove its donor API identity or index convention.
Do not invent pass-1 semantics or change the canonical layout to match it.
Next work is native caller/index and provider-identity evidence, alongside
the canonical matrix API owner, then a connected whole-emission trial.

This is a blocked cleanup lead, not a new regression or partial matching
reconstruction. No native rows, pins, hatches or debt keys were changed.
