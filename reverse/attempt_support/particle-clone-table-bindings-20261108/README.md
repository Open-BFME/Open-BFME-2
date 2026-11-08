# Particle clone uses existing table providers, 2026-11-08

Rva003AF27BClone.cpp removes its two unowned one-byte table stand-ins and
directly binds the existing Rva003AD1CAModule compiler tables at native RVAs
0x0081CFB0 (+0) and 0x0081C030 (+0x14). Both are independently established by
the rowed constructor at 0x003AD1CA: its named DIR32 operands read those exact
table VAs in retail. provider-proof.json records the sites and cached emitter
hash. This establishes data-address identity, not original class hierarchy,
template identity or a BFME2 donor path; placeholder class names stay unchanged.

Neither char has a data_rows or data_converged owner. Current source search
and the d171e84869 index (2026-11-08 15:35) touch both names only in this
source. The only removed definitions are those two chars; none is added.
No row, pin, alias, compiler flag or source path changes. All code COMDAT
facts and flags remain equal after normalizing only the two data referents to
their independently proved native addresses.

The complete 81-byte clone and its parent EH graph pass normal verification;
the source is unfrozen, private verification passes 1/1, and LinkGuard reports
no new obstacle. Strict preparation passes. Ordinary current-object preview
conserves LINKS/81 authored bytes.

A bounded replay contains this source, the cached constructor emitter and
native slot owners for these two tables. Strong-definition refusals drop from
two to zero; the same two bridges/six slots remain necessary. This is cached
provider evidence, not a new full image or a bridge-retirement claim.

The +0x18 Rva003AF208_v18 reference remains. Its one-byte provider lives in
ParticleModuleTemplateCopyCtors.cpp and is shared by two of that file's nine
matched copy constructors. Recover/rebind that containing cohort separately,
preserving its complete file and consumers. Complete class/header recovery
and automated real-link/runtime confirmation remain open under LINK-636 and
LINK-619. No generated queue is edited or pass test declared cleared.

Published as4f82f0c3ee; first attempt landed in35.3 seconds. Required
byte/EH/scoped-DIR32 checks pass after rebase. Broader audit remains
INCONCLUSIVE: index d171e84869 versus base
155a1d23107357e01c7bc8836ac37840e5c75e53, affected Common/AIBaseBuilder.cpp
lacks a current receipt. The earlier CreateAHero receipt gap was prepared
locally; this is the next recorded consumer gap, not broader link clearance.
