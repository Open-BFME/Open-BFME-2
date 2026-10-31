# Drawable Vector4 retirement blocked by an existing dependency

Base 6e7a2b6c2. Scope: `Code/GameEngine/Source/GameClient/DrawableConstructor.cpp`.
The source already uses canonical Vector4 transitively through Matrix3DData.
An explicit registered-header include preserves all fifteen native rows, all
external code bodies/relocations and all 62 non-debug sections, including the
positions of compiler-local relocation targets. EH and strict preparation pass.

Owning acceptance correctly refuses its census preservation guard: the ordinary
e78b61f1b2 preview reports LINKED 2120 -> 0 with unresolved
`?Release_Ref@OpaqueRefCounted@@QAEXXZ`. Rebuilding the ORIGINAL source produces
the same result. The row exists at 0x00050ED3 in
`Code/Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.cpp`; neither substituting
RefCountClass nor inventing another identity is justified. The declaration in
Drawable points to that existing native atomic-release worker.

The original source is restored, and the header queue is unchanged. This is a
blocked prerequisite, not a completed task or evidence of an include regression.
Next: a provider/current-selection owner must establish a strict current
OpaqueRefCounted provider and repeat the ordinary retirement guard. Do not use
an older index or hand-retire the key. Controls are the ignored run's b2-02
before/direct-include files, original-link-control, byte/EH and section logs.
No census, full-image or runtime claim. No Qwen; shared pool ten.
