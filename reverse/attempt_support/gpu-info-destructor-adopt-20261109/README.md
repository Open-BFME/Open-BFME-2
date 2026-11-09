# Canonical GPU info teardown

GpuDrawModuleInfoDtor.cpp adopts the canonical GpuDrawModuleInfo header and
its real Snapshot base. It removes the private class body and fictitious
GpuDrawModuleInfoBase. The unit retains its existing novtable code-generation
property on a forward declaration; the shared header supplies the complete
class and layout. No shared header or compiler flag changes.

An ordinary include emits a derived vptr store absent from retail. Keeping
novtable on the local forward declaration preserves the native 48-byte
destructor at 003A9D43 and its exact EH graph. This retains an existing
property, rather than adding a new class view, a header mode or an escape
hatch. No nonmatching trial is left in Code/.

The two newly emitted real Snapshot helpers are independently native:
destructor 0049B47C (7B) and scalar-deleting destructor 000053AF (29B).
All retained code, relocation positions, flags and COMDAT policies agree
after the exact old-base-to-Snapshot family mapping. External definitions,
references and weak bindings change only by that mapping and the three
pure slots' existing __purecall reference; linker directives are unchanged.
Every other data definition is identical. The former four-byte fake-base
table becomes Snapshot's complete sixteen-byte table at 007BB554, with all
four native slots and zero relocation addends. The weak E helper resolves
to the verified G helper; no new pin or alias is added.

Normal build, frozen checks and EH verification pass. The unit's own ordinary
link verdict remains LINKS48. The five current GPU info users together are
5/5 LINKS820 against index 717b70f4ab. These are conserved scoped previews,
not a new census or image gain. header_adopt_lane.py accept retires exactly
one row through its owning path: no GpuDrawModuleInfo users remain queued.
No function row, data owner or source path changes.

The six runtime arrays investigated in the preceding sibling packet remain
unchanged. Their complete virtual declarations, native producer bindings
and constructor/EH constraint still need recovery. This repair does not
establish retail's original runtime class names, an image, boot, gameplay
or CRC parity. No donor was used.

Local reproduction: build/particle-clone-tables-20261109/gpu-dtor-trial.py,
verify-gpu-dtor.py and the gpu-dtor-* logs/objects. The private regular and
novtable-forward trials share one explanation; only the latter matches.
proof.json records the normal object's native helpers and strict receipt.

The preceding sibling package landed as 6ee9f727d7 on the first attempt in
46.4 seconds; post-publication strict/native proof passed. Its broader
audit was INCONCLUSIVE for unchanged AIBuildable.cpp's missing receipt
(index 717b70f4ab, outgoing base e9e9c137ed). Carry that consumer and the
current five-source family into the next maintained census and actual image.
