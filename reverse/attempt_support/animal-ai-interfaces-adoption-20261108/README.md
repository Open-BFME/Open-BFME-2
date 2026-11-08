# Animal AI canonical interfaces, 2026-11-08

AnimalAIUpdate.cpp now includes the existing AIUpdate.h definitions for
AICommandInterface and AIUpdateInterface. This removes its two private
interface classes and the recursive 142-slot placeholder hierarchy. The
partial Animal class is unchanged and remains a separate header debt.

Target receiver facts: the update body receives whole-object +0x10. Its
command calls use whole-object +0x20, while chooseLocomotorSet and the state
query use the primary object. The existing animalPrimary bridge still
subtracts 0x10. The qualified parent update now goes through that primary
pointer, allowing the canonical inherited-interface adjustment to supply
the original secondary receiver exactly once. The command bridge retains
its existing secondary-relative +0x10 expression. The full 2,916-byte body,
including the parent-call setup and bindings, remains identical.

The first trial expressed the command-base conversion through a C++
reference. Although the receiver was correct, register allocation changed
and the update grew to 2,953 bytes (14/15 rows). Keeping the established
command bridge restores all 15 rows. The other 14 rows passed both trials.
The stale source table comment is also corrected: retail VA 0x00C47B8C
slot 0 contains VA 0x0087EDC9. These are target facts, not donor name recovery.

Normal build.sh verifies all 15 rows, 28 string literals and one float;
all three parent EH graphs are exact. Frozen-source checking passes.
Owning-tool acceptance retires the two interface queue rows. Paired
new-variant checking passes; preview preserves LINKS/3,167 bytes against
c885072a48 (2026-11-08 19:18), without establishing a current image link.

All 63 code COMDAT bodies, relocation identities, flags and selection
policies are identical. All 30 named data allocations, external definitions
and undefined references are also identical. No provider is added or
removed. The public-build object and the privately verified final candidate
agree on all these facts. final-proof.json records their source hash and
the unchanged parent call at update+0x3C; final strict preparation is also
required before publication.

No shared header, source path, function row, pin, alias, hatch or coverage
claim changes. Full Animal class adoption, constructor/destructor/table
reconciliation and TU consolidation remain open. Preview and retained
provider checks do not establish a new census or runtime result.
