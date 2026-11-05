# ShareExperience module-data declaration prerequisite

Base: 8e71f74bd8, 2026-11-05. Scope: the claimed approved
ShareExperienceBehavior.cpp TU and its two constructor fragments.

The constructor fragment now spells its five fields and its initializer as
the existing TU does: pad at +4, radius at +8, drop-off at +0xC,
percentage at +0x10 and object filter at +0x14. These are existing source
spellings, not newly established donor names. Layout, explicit virtual
destructor declaration, compiler flags and bodies are preserved.
The mechanical view tool refuses a token rename through an out-of-class
initializer, so the declaration and initializer were reconciled together.

Verification: ./build.sh passes all four fragment rows; declared-unmatched
passes; eh_verify reports one EXACT graph; data_check reports zero findings.
link_census.read_facts compared the original object copied before editing
with the rebuilt object: all 14 COMDAT digest/retail verdict records, one
strong definition, 11 undefined names and three weak aliases are identical.
The local link preview remains LINKS, 93 -> 93 authored bytes, against the
2026-11-05 05:17 census at c95fcfcfcd. This is not a new census measurement.

The supported tu_skeleton dry-run now accepts the module-data constructor
fragment into ShareExperienceBehavior.cpp, preserving 19 rows. It still
rejects the behavior constructor on unresolved slot00/slot01/slot02 of
Rva00480093Iface20 (and further slots). Its three link-wide aliases are
unchanged. The two mixed files remain outside this pass. The actual merge,
its full consumer audit and census confirmation remain separate work.
