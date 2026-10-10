# Native stance-name ownership

The native .rdata table at VA C3C210 is exactly six pointers and a null (28 bytes).
The existing `TheStanceNames` identifier is preserved; the six label identifiers
are descriptive and do not assert original names. Each row owns only the complete
measured NUL-terminated datum, with no padding. No data or code alias is added.

| Label | Native VA | Size including NUL |
|---|---|---:|
| Uninitialized | C3C260 | 14 |
| Battle | C3C258 | 7 |
| Aggressive | C1F724 | 11 |
| HoldGround | C3C24C | 11 |
| Porcupine | C3C240 | 10 |
| HoldGroundMoving | C3C22C | 17 |

All four raw executable references to C3C210 are independently decoded:
35B864 passes the table to INI::scanIndexList; 3B4B1D indexes it for UI text;
425DDD passes it to scanIndexList; the complete unrowed 425DC2 getter indexes
it after signed bounds checks. No executable reference writes the table.
Both prior mutable declarations and the third consumer's address alias are
reconciled to one read-only pointer-array declaration. Other consumer debt is
unchanged. Private declaration controls preserve all 18 existing consumer rows.

BFME1 dependency checkout is committed 575ba2b04743f190f069805fbdc59936123c45da.
No clean same-named Stances source exists there. The independently verified
BFME2 Thing-class diagnostic-label owner supplies only the data-definition
workflow; table contents, pointer targets, extents and consumer relationships
are established from BFME2 retail, not inferred from that unrelated table.

The separately reserved getter starts at 425DC2 after the prior RET4. Its
27-byte extent includes the false 6-byte 425DD7 fallback row. Only the two
conditional branches within 425DC2 target that suffix; no direct call, tail
call or absolute address reference exists. Its retirement and ordinary full
body admission are separate commits and are not part of this data-only claim.

Ordinary production verification checked all seven data rows (98 bytes) and
all 18 consumer function rows: 97 complete literals, 36 empty-string references,
three float literals and every relocation passed. Supported bounded strict
preparation verified the four changed providers against the same objects.
The first strict current-ledger preview lacked newly published HordeMeleeSwarm;
its one explicit provider was then prepared and its native 939-byte body passed.
The next preview refused 12,831 unrelated providers without current compiler
witnesses in this worktree. No wider compilation, census, index injection or
receipt transplant was performed. This data repair is byte-verified, but current
whole-universe LINK closure remains pending; it is not reported as DONE.

The single false 425DD7 six-byte method row is retired in a separate reviewable
commit. Its contributor-local ModuleNameGetters4 file contained no other body
and is removed. All other ledger lines remain byte-for-byte unchanged. Native
RET4 before 425DC2 and the next 425DDD prologue bound the complete 27-byte body;
only its internal JL/JGE target 425DD7. This retraction credits -6 C++ bytes.
No replacement row, pin or alias is introduced by the retraction.

Ordinary add_match subsequently admitted the complete address-owned
Rva00425DC2StanceName function (27 bytes) with both genuine DIR32 references:
its single owned table and the complete eight-byte Unknown literal. The required
signed stack index and full EAX pointer result are observed target facts;
original method spelling, owner and unused arity remain unknown. No class,
synthetic caller, inline assembly, replacement pin or alias is introduced.
Supported strict preparation verified all four provider/consumer objects and
all 19 rows together, seven data rows, 98 complete literals plus 36 empty refs,
and three float literals. Incidental placement reports zero additional bodies
and zero pins. The separate -6/+27 commits yield +21 unique C++ bytes; the new
proper source has zero supported open bodies. Current whole-universe LINK is
still pending primary-cache verification and no publication/DONE is asserted.

The shadow data-name audit still uses the old harvested 83C210 entry, whose
mutable decorated spelling has status unowned and an empty source. It flags
these read-only declarations even though the new data row supplies the sole
actual definition. No second data owner existed, no baseline is expanded and
the enforced converged-data check passes. The FontLibrary allocator identity
shadow finding is disclosed as unrelated to this unchanged-byte table repair.
