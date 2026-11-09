# Army upgrade ModuleInfo header adoption (2026-11-09)

Rva0040C351Ctor.cpp now includes Common/ModuleInfoClass.h. It removes the
private 12-byte ModuleInfo class and its 20-byte WorldMapModuleRecordView,
using the canonical getCount accessor in the two complete upgrade loops.
No other function logic, source path, ledger identity or pin changes.

Private before/candidate verification and the normal build pass all six body
rows and both data rows. Every one of the 549 retained COMDAT payloads and
selection policies is unchanged; the normal object equals the private
candidate. All undefined symbols, weak defaults, aliases and includes are
unchanged. The sole provider change replaces private count with canonical
getCount: both are the same 12-byte payload d2b57ba9852a, selection 2.
The census has six matching getCount copies and three copies of the old count;
no explicit old-name reference was found outside the source in Code or the
symbol/data ledgers.

The source's own link verdict is LINKS, preserving 865 bytes against census
5b5011469d (2026-11-09 19:12). Owning header acceptance retires exactly one
ModuleInfo register row, leaving 19 locally and no header key for this source.
The surrounding ThingTemplate and world-map module ABI views remain separate;
this change establishes no new class name or runtime result.

Scratch before/candidate objects, provider proof and normal build/link/accept
receipts use the moduleinfo-army-upgrades prefix under
build/thingtemplate-header-cohort-20261109/. Broader batch audit and actual
image/runtime verification are separate from this scoped link verdict.

Published as 8541635d74 with the registration-base fold and two independent
handoffs. The four-commit batch landed on attempt three (86.9 seconds after
two lost races). All 38 bodies, six data rows and six EH graphs passed normal
push checks. Each of its five sources' own link verdicts was LINKS, preserving
1,998 bytes. The broader audit was INCONCLUSIVE: unchanged
Common/AICowerState_onEnter.cpp lacked a current receipt against index
5b5011469d and outgoing base d41f8690fa. Carry that evidence gap into the next
census; this scoped package does not close it.
