# ExperienceLevelSystem cache-tree declaration reconciliation

Base: `7da8bed7e0`; provider index: `5a13f2cd61` (2026-11-04 02:25).

Target/compiler facts: Common/ExperienceLevelSystem.cpp and
Common/Rva00289180Finish.cpp lay out Rva0028881C as a nonvirtual eight-byte
object, with a pointer at +0 and int at +4. The approved GameLogic/System
TU instead embedded a one-byte call-only view at +0x28. The three declarations
now share those fields and their existing destructor/clear declarations.
This is private-view reconciliation; no retail identity or donor name is recovered.
The existing Finish field spellings are reused; no body refers to the renamed fields.

Verification:

- `./build.sh` over the three files: 52/52 function rows, two data rows,
  string and import references pass before and after.
- `find_declared_unmatched.py` over the three files: all definitions matched;
  the existing absent/registered markers remain unchanged.
- `tu_views.py TU --class Rva0028881C --no-merge-check`: already shared (3 files).
- External symbol sets and relocation-aware COMDAT digests are identical before
  and after: GameLogic/System TU 330 symbols / 253 COMDATs; Common destructor
  35 / 22; Finish 20 / 18. Compared with `tu_views.coff_externals` and
  `link_census.comdat_bodies` on the ordinary build objects.
- Ordinary link_check: 3/3 LINKS, 3,162 authored bytes retained. This is a
  prediction against the stated index, not a new census or real-link result.
- No paths, ledger rows, pins, aliases, hatches or protected debt keys moved.

The baseline supported merge dry run accepted zero of 14 donors. This clears
one private-view prerequisite only. ExperienceLevelSystem still has incompatible
base/virtual declarations (see the 0x00289180 handoff in re_attempts.log), while
Rva002894A2 has differing bases/novtable, and list/hash donors have instantiation
and compile-environment conflicts. The private Overridable consumers additionally
need their canonical header; its const/nonconst getFinalOverride overloads must
preserve the original const call. No full TU merge or source-count gain is claimed.
