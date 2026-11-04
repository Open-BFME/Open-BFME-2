# RefCountClass adoption blocked by an existing RenderObj projection

Source `Code/GameEngineDevice/Source/W3DDevice/GameClient/RTS3DSceneRenderOneObject.cpp`, primary renderOneObject RVA6FB59/2550.
The original source, all owning header keys and its native current object are
retained. No failed reconstruction is left in Code/. The rejected minimal
canonical-include transformation is saved in `refcount-renderobj-rejected-20261104-1410.patch`.

Adding the established RefCountClass destructor slot1 shifts the source's
extra private RenderObjClass slot declarations. Canonical RenderingMethod
alone repairs related pass-call consumers but not this hierarchy. The same
2550-byte parent differs at offsets76/125/521/591/1558/1574/1954/2095/2237/
2275/2440/2482; each dispatch displacement increases by4. Relocation/call
destinations otherwise remain at the same positions in the printed native
comparison. The source also reports its scoped child funclet without an exact
same-source parent when that parent differs; the parent must be repaired first.

The private RenderObjClass currently has RENDEROBJ_SLOT(01), while the actual
registered RefCountClass already owns deleting slot1. Existing rendobj.h and
its constructor/copy witnesses establish the real parent and virtual destructor.
Removing the redundant placeholder is a narrow hypothesis for a future private
trial; it has NOT been tested or accepted. A complete canonical RenderObj
adoption would additionally need its 0xC4 full-owner layout versus this file's
short receiver projection reconciled. Neither guessed patch is shipped.

The native class:RenderObjClass claim request was refused because another
contributor holds it. Their reservation is preserved. There is no further
attempt here. Earlier direct-base attempts were followed by the justified
derived-interface repair: six related rendering consumers now pass separately.
The local comparator's initial locally-introduced destructor spelling and
ordered-section assumptions were diagnostic limitations, not native game-code
failure; those were corrected without editing a repository gate.

Run evidence: b2-r14-normal/restored logs, rows, source snapshots,
r14-mismatch-summary.json and the native class-claim refusal. This is a blocked
twentieth source, not completed work, new byte coverage or runtime/crash proof.
