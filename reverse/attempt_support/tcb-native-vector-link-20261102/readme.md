# Native twelve-byte vector storage repair

Base bc450807165bf634e63bd9f21fe0d7b5c594e654; model GPT-6.
Scope: existing tcbspline.cpp vector instantiations, not a recovered spline TU.
Read prior tcbspline-emission-20261029 and LINK-004/LINK-175 evidence before trial.
The BFME 1 reference remains the committed 946f3c05a1b1e60448734e874a8f47f8017cfdb9;
no independent upstream check or original BFME 2 header recovery is claimed.

## Target facts and limited view

Native VectorClass slot 2 and the rowed DynamicVector Resize caller reach
0x000F0BF1. That 227B body's array iterator constructs twelve-byte elements
with the empty constructor at 0x0047A6A9, then assigns three float components.
The existing Vector3 owner and its verification establish the memberwise-copy
and nonthrowing array-delete contract; the donor TCB POD does not satisfy it.

Use a TU-local nested storage view with an empty default constructor and
componentwise assignment. Retain existing TCBClass, Tension, Continuity and
Bias spellings as donor vocabulary only. No TCBSpline outer object, method,
base layout or table is instantiated. This is structural evidence for existing
vector operations, not proof of original element identity or an original path.
No other file, shared header, flag, signature, row, pin or hatch changes.

## Verification

The private candidate first emits both native helpers exactly: Resize227B at
0x000F0BF1 and base ctor150B at0x000F0D2F. Production comparison repeats that
check with resolved relocations; both complete EH graphs are EXACT. The empty
element constructor matches the existing3B owner at0x0047A6A9 too.

All five existing rows340B stay exact. Object comparison preserves17 existing
COMDAT fingerprints including both complete24B vector tables. Only the former
68B base ctor and156B Resize change to their verified150B/227B native bodies.
No external provider disappears:19->21 definitions. The two additions are the
verified empty element constructor and the ordinary empty placement-delete
cleanup required by array construction. final-audit.py is read-only verification
of already compiled objects; it never compiles or changes production caches.

Normal eight-source verification passes45/45 functions, two data rows, eight
strings and five float literals. All eight current objects preview LINKS:
5015->5355B, +340B solely from tcbspline.cpp; every peer retains its bytes.
The three explicit vector sources also pass strict-current preparation14/14.
Index984a4cdc4d (2026-11-02 08:35) is older than the base: these are bounded
predictions, not census linking credit, runtime proof or full consumer clearance.

The owning identity-retirement tool refuses because1132 ledger objects are
missing, leaving global kept selection unknown. Nothing is retired or manually
removed from reverse/code_identity_baseline.tsv. The old wrong-Resize key stays
until its complete fresh-object prerequisite can be met through the normal lane.
Carry the provider and affected consumers into the next scheduled census.

Native Resize/storage family: t=13 model=gpt-6 lane=R budget=30m.
