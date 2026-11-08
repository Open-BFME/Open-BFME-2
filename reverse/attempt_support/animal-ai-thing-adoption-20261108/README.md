# Canonical Thing accessor and AnimalAIUpdate, 2026-11-08

Thing's existing getTemplate declaration now has its inline field-access body
in the canonical header. The definition follows the complete class: this
placement preserves matched callers' code generation. AnimalAIUpdate.cpp
adopts that header, replaces its short private Thing prefix with the real
0x60-byte prefix, and shrinks the following Object padding to preserve ID
and flee-distance offsets. Its position helper uses the canonical cached
position. Full Object/AI interface recovery remains separate work.

The accessor name and signature already existed in the canonical header.
The four-byte body reads the known +4 template pointer and agrees with the
private helper being retired. No native accessor RVA, original out-of-line
identity or original spelling is newly recovered or claimed. No row, pin,
alias, compiler flag, shared layout or source path changes.

The first direct-field trial matched 14/15 rows: the 2,916-byte update grew
to 2,922 bytes with changed register allocation. A standalone inline getter
restored all matches but was correctly flagged as an unrowed definition;
that file attempt was restored. Defining the existing accessor in its
proper canonical header resolves the class dependency. An in-class body
changed two reloads in BezierProjectileBehavior; a committed-header control
passed 44/44, while that form passed 43/44. The final definition after the
class passes both Bezier 44/44 and Animal 15/15. Bezier source is unchanged.

The conservative header graph reaches 1,734 ledger sources. The final form
passes 18,890 row checks across those sources, including string, float,
import and data checks, in 245 seconds of normal build.sh batches. EH checks
find 2,504 exact graphs and one pre-existing baselined NetCommandWrapperList
graph; its compile dependencies do not contain the canonical Thing header.
All three Animal EH graphs are exact. Full-scope new-variant checking passes.
Header acceptance retires exactly one Animal Thing debt; strict preparation
of the modified source passes too.

Animal retains all 63 existing code COMDAT facts, flags, relocation bindings
and selection policies, all 30 named data allocations, all external
definitions and undefined references. The sole added compiler iterator
matches native 0x00001423 and the existing ATL provider's flags/policy.
Across the verified scope, all 13 emitted accessor copies have the same
four-byte body and no relocations. final-proof.json records the source and
header hashes; header-verification.json records the scope hash and batches.

This clears one header debt and private Thing copy, and makes the shared
accessor implementation available to the canonical class's consumers.
Bounded provider checks use index d171e84869; they do not establish a new
full image, census, coverage gain or runtime result. The remaining Animal
AICommandInterface, AICommandParms, AIUpdateInterface and AnimalAIUpdate
header debts are not retired by this change.
