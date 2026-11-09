# Army-upgrade loops need canonical ModuleInfo storage

Status: cleared for Rva0040C351Ctor.cpp (2026-11-09).

The source uses Common/ModuleInfoClass.h and getCount in its two world-map
upgrade loops, removing its private ModuleInfo and record declarations.
All six body rows and both data tables verify. The 549 retained COMDATs and
their policies are unchanged; the count accessor becomes an identical
12-byte canonical copy already supplied by six census objects. External
bindings, weak defaults, aliases and includes are unchanged.

The source's own link verdict remains LINKS, 865 bytes against census
5b5011469d. The owning header lane accepted the source and retired one debt
row, leaving 19 ModuleInfo entries locally and none for this source. This
clears only this header adoption, not the other army/template/module views,
the broader outgoing-batch audit or a game-image exit test. Evidence:
reverse/attempt_support/moduleinfo-army-upgrades-header-adoption-20261109.md.

Publication receipt: 8541635d74, four-commit batch, attempt three. Normal push
checks verified 38 bodies, six data rows and six exact EH graphs. Broader audit
remains INCONCLUSIVE on unchanged AICowerState_onEnter.cpp's missing current
receipt (index 5b5011469d, outgoing base d41f8690fa); all five directly checked
sources retained their own LINKS verdicts. The consumer audit remains open.
