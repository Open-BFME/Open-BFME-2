### LINK-165: Buddy constructor needs the native string lifetime provider (2026-10-30)

The constructor's incompatible narrow-allocator chain is live, so the earlier
debug-only suppression recipe does not apply directly. Its five native string
cleanup funclets all jump to existing destructor `142D70`. A declaration-only
string-destructor specialization binds those calls to that owner and stops
eleven local lifetime helpers from being instantiated. All ten owned rows and
constructor EH remain exact. Retained raw code is unchanged; only five
relocation names in the pre-existing unrowed implicit Buddy destructor change
between two existing bindings at `142D70`. That 140-byte implicit view is not
admitted or claimed native exact; the separately rowed 170-byte Buddy body
and complete/deleting-destructor identities remain separate prerequisites.
All referenced removed names retain selected providers. Both existing string
providers remain complete 14-byte native exact. Strict three-source preparation
passes 27 rows, one data row and seven EH graphs; preview against `ccafe54d1d`
retains 3/3 LINKS, constructor 0 -> 230 authored bytes. No pin, row, alias,
hatch or header changes. Full affected-consumer and census confirmation remain
pending. [Proof and remaining scope](../../reverse/attempt_support/buddy-ctor-string-lifetime-20261030/readme.md).

Outgoing audit: INCONCLUSIVE because index `ccafe54d1d` predates base
`2ea103ccc1` and affected CreateAHeroManager lacks a current receipt. Carry
all removed lifetime helpers, retargeted bindings and affected consumers into
the next scheduled census; no broader selection/loss clearance is inferred.
