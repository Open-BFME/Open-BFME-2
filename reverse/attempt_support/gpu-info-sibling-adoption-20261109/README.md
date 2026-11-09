# GPU info transfer and assignment adoption

GpuDrawModuleInfoDoXfer.cpp and GpuDrawModuleInfoOpAssign.cpp now include the
canonical GpuDrawModuleInfo header instead of defining private class copies.
The field accesses use the header's existing offset names: m_04, m_08, m_0C
and m_10. The old transfer comment incorrectly attached the frame-count roles
to those offsets; it now states only the native transfer types and addresses.
No shared header, method identity, source path, row, pin or alias changes.

Both complete bodies remain native: DoXfer 0056390A is 64 bytes and assignment
003A7EF0 is 45 bytes. Private before/candidate objects and normal build objects
have identical code, data, relocation targets, flags, COMDAT policies, external
definitions/references, weak bindings and linker directives. There are no EH,
string, float or import obligations in these two units. Declaration checks are
clean. Their own ordinary link verdicts remain 2/2 LINKS, 109 authored bytes,
against index 717b70f4ab; no new linked-byte gain is claimed.

header_adopt_lane.py accept retires exactly two queue rows through the owning
tool. Only GpuDrawModuleInfoDtor.cpp remains queued for this class. Its existing
novtable/private-base teardown needs a separately verified solution; this pass
does not add a header switch or alter its destructor.

The served ParticleModuleTemplateClones.cpp has also been drained through a
bounded native/provider investigation. After 8744d4c73b removed its Slot3
strong array, six runtime arrays remain. The factory 0081C608 contains native
3AD03B, while Wind's pure category tables bind 0081C780. Clone-primary 0081CEF8
contains 3AD3F7/3A5572/3AECE6/3A5757, while Wind's independently bound primary
is at 0081C60C with a pure clone slot. Neither is a substitute.

The four GPU runtime ranges and their current native slot words are recorded
in runtime-prerequisites.json. The apparent Rva003ABA4C/Rva003ACEF7 compiler
alternatives in the cached deleting-destructor owners are all four bytes, with
only a deleting helper. Their synthetic constructor emitters are explicitly
absent-from-retail and provide no native placement witness. The two cached
owners lack strict receipts; their shape is a bounded compiler observation,
not proof of recovered runtime classes. GapForwardersSeat8.cpp's two short
Rva003AE94E tables contain only transfer helpers, not native deleting slots.
The canonical info table at 0081C1E8 has different targets and cannot replace
these runtime tables. No declaration-only table suppression or alias is added.

Next prerequisite: establish the real runtime virtual declarations, overrides
and producer bindings while preserving the native constructor's store order
and EH cleanup. Prior attempt82384 records the 00563CAF cleanup constraint;
canonical info adoption does not resolve it. Six current blocked verdicts are
recorded through re_log.py, with no nonmatching source left in Code/.
LINK-004/LINK-627 retain the remaining scope. LINK-584 is held by another
worker, so its relevant follow-up is banked here without editing that claim.

Local reproduction: build/particle-clone-tables-20261109/gpu-siblings-trial.py,
verify-gpu-siblings.py, gpu-runtime-map.py and the gpu-siblings-* logs/objects.
proof.json records final strict receipt state. No donor was used. Source and
native facts do not establish retail's original runtime class names or layout.
No current global image, boot, gameplay or CRC clearance is claimed.

The preceding Wind consumer repair landed as 8744d4c73b on the first attempt
in 42.2 seconds; its post-publication strict/native proof passed. Its broader
audit was INCONCLUSIVE for unchanged AIBuildable.cpp's missing receipt
(index 717b70f4ab, outgoing base a2bc8e58ae). Carry that consumer and the repaired
secondary-table scope into the next maintained census and actual image.
