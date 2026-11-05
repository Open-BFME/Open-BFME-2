# Shared renderer and scene definitions in W3DDisplay initialization

Base cadc5ea134a50939f1a2a93170b1063af8c7e843; model GPT-6.
Scope: existing W3DDisplayInit.cpp; no source or shared header is moved.
Renderer, scene, constructor-view and header scopes are origin-claimed.
LightClass claim was refused by a peer during this pass; its partial header claim is released
immediately, and its original private body stays unchanged.

## Actual definition changes

Replace the padded private Render2DClass with the unchanged4C shared class.
Its constructor and coordinate-range signatures remain the same. Owning
Render2DClass acceptance passes before beginning the scene prerequisite.

Use unchanged RTS3DScene.h, removing the private RTS3DScene and SceneClass
bodies. The interface-scene type is retained only as the existing opaque
global pointer spelling; no semantic name/identity merge is asserted. Its
allocation is the already rowed Rva0006EE6F constructor6EE5D, whose owner
SimpleSceneDerivedDtors.cpp proves the SimpleSceneClass base and declared
Customized_Render override6EE22. The native allocation is108B. The source
now constructs that real view and accesses only its known shared scene prefix.

The other allocation follows RTS2DSceneCtor.cpp: SimpleSceneClass at0,
SubsystemInterface at108, status114 and camera118, total11C. The full shared
subsystem's pure init/reset/update declarations require concrete overrides;
native secondary tableBC6264 slots1/9/10 are the no-op bodyB3FD0. Only their
declarations are needed here; no implementation, pin or row is invented.
Compile-time extent checks preserve108/11C; shared RTS3DScene stays818.
RTS2DScene's full type/name recovery remains separate from this used protocol.

There are four fewer private bodies: Render2DClass, RTS3DScene, SceneClass
and the empty RTS3DInterfaceScene. The two existing constructor-only views
are corrected rather than pretending the former four-byte base is complete.
All global pointer spellings and relocation targets remain unchanged.

## Verification

All15 original rows pass normal and strict-current gates: native init1594B,
its funclets/handler, one string and six float literals. Its complete EH graph
is EXACT. All21 original code/data COMDAT definition and relocation digests
remain identical; nothing is added or removed and no vtable is emitted before
or after. Thus this does not merely substitute a compatible wrong table.
The read-only audit also captures the native interface/2D tables and confirms
the concrete secondary slots. No shared header, flag, ledger row, signature,
hatch or pin changes. Ordinary preview retains LINKS1599->1599B against
indexc95fcfcfcd (2026-11-05 05:17), and new-variant checking returns0.

Both owning accept verdicts retire one queue row each, two total. No manual
queue edit. LightClass was peer-held during this pass and remains pending in this source. Other
scene/global consumers, full real-link selection and runtime remain unproved;
carry this source and affected consumers into the next scheduled census.
No new matched or census-linked bytes are claimed.

Initialization family: t=18 model=gpt-6 lane=R budget=30m.

## Rebase and outgoing-batch boundary

Successfully rebased the source commit onto60cc40eb3a289822e9e31e0c4957c3bea6ed3d9d;
resulting source commit4aa32ca6e244819ecb76df7a1ad337eafcb79b77.
Upstream changed Vector3Data.h to inline its assignment operator. Repeated
strict-current verification still passes15/15, one string and six floats;
read-only object audit preserves21/21 definitions and relocations, no vtables,
and EXACT parent EH. The repeated ordinary link preview retains1599->1599B.
The outgoing header-dependency check returns0 (empty header-check.log).

The batch audit is INCONCLUSIVE: indexc95fcfcfcd predates the outgoing base,
and affected consumer Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
lacks a current receipt. Its full diagnostic is retained in batch-audit.log.
The audit process finished; its terminal session was no longer available when
recovering the final output, so no independently observed terminal exit code
is claimed here. This is not global link clearance; the source and affected
consumers remain scheduled-census follow-up work. No audit was relaunched.
