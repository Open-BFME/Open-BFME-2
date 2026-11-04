# ExperienceLevelSystem find consumer: canonical Overridable

Base: `c46e7f148c`; provider index: `5a13f2cd61` (2026-11-04 02:25).

Common/Rva00288940Find.cpp now includes the existing canonical Overridable
header instead of a private view. The private view exposed only the const
friend_getFinalOverride; the canonical header also exposes the nonconst
overload. Making the existing pointer cast const preserves the target's call
to the const owner at 0x00288609 rather than selecting 0x001E35DF.

The removed view's data members were unused. Node's two pointer offsets and
the explicit +8 adjustment are unchanged; the function does not allocate,
instantiate, or take sizeof Node or Overridable. This adopts an existing
contract, without inferring a retail class name or donor layout.

The automatic adoption codemod could not map the unused m_v0 field to the
canonical virtual pointer. The direct include replacement and const cast
passed the ordinary acceptance tool; no verifier was changed or bypassed.

Verification:

- `./build.sh` baseline: 1/1 function row, strings, floats and imports pass.
- `header_adopt_lane.py accept --class Overridable FILE`: PASS; retired exactly
  this consumer's header_queue.tsv row through its owning tool after byte/link
  verification.
- `find_declared_unmatched.py FILE`: all definitions already matched.
- External symbol set (four symbols) and relocation-aware COMDAT digest
  (one body) are identical before and after, using tu_views.coff_externals and
  link_census.comdat_bodies on ordinary build objects.
- Ordinary link_check: LINKS, LINKED 56 -> 56 authored bytes against the stated
  index. This is a prediction, not a new census or real-link result.

No paths, function rows, pins, aliases or hatches changed. Other Overridable
consumers and the previously documented base/virtual and container composition
conflicts remain. The full merge was not rerun after the prerequisite repairs;
no source-count gain is claimed. The supported baseline merge failure and the
two completed prerequisites are recorded through re_log.py.
