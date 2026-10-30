# Renderer global: inherited header prerequisite

Control: 7906295d3f8e99862e1b7b005566c1fd7a6b4984.
Data-identity candidate: dx8wrapper.cpp has two registered wrong-name keys at
009F363C (VA 00DF363C), BfmeResetMeshRendererInstance and ShutdownMeshRenderer.
Both reach the ledger's TheDX8MeshRenderer pointer. Three /alternatename
directives cover the two spellings. No other tracked source uses either name.

The diagnostic patch adopts the existing global name without changing
the reset-hook receiver, shutdown receiver, delete or zeroing operations.
It does not compile: the inherited Zero Hour dx8renderer.h already declares
extern DX8MeshRendererClass TheDX8MeshRenderer, an object, while BFME 2's
existing provider DX8TextureCategoryDtor.cpp defines a pointer. The proposed
extern pointer therefore fails C2040 at line 731. The existing renderer-link
shim repeats the object declaration, so selecting it does not solve the issue.

First reconcile the renderer's canonical header/type and consumers under
the normal shared-header gate. Do not hide the incompatible declaration
with a new alias, preprocessor name substitution or a duplicate namespace.
The data ledger's eight-byte provisional extent is not a recovered data-row
claim; this trial establishes no ownership beyond the existing evidence.

The entire source trial is restored. Normal restored verification passes
235 functions, 13 data rows, 79 strings plus one empty string, 26 float
constants and 24 imports. No debt, pin or alias baseline changes are retained.
The original ordinary preview LINKS at 28,658 bytes against ccafe54d1d
(2026-10-30 15:43); no improvement, new census or runtime result is claimed.
The adjacent patch is diagnostic only and must not be applied without the
header prerequisite and complete normal verification.
