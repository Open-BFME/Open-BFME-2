# Certify the texture atlas insertion chain

GPT-6; lane R; t=20min active; budget=30m. Work began 2026-11-01 and
resumed 2026-11-02 after an overnight interruption. All six expired body/file
claims were reclaimed and confirmed before further source/ledger edits.

## Actual cause and repair

The previous canonical-method pass exposed one shadow wrong/unknown binding:
UpdateResultTexture calls a typed59B insert_equal at00170E3D, whose136B
_M_insert has the right native shape but lacked a complete callee proof.
The default typed _M_create_node emitted36B, directly calling the counted
pair constructor. Native34B factory00170B70 calls18B _Construct00170A97
instead, through the already rowed Rva00170B19 owner. Its24B allocation and
value at+10 are independently established by the native insert/factory/value
chain. This is a source-code generation mismatch in the unused emitted
factory copy, not proof the existing892B parent stopped matching.

A small inline-only specialization forwards the typed factory to that
existing34B owner with the same receiver and value storage. It keeps pointer
return transport and counted construction; no function-pointer cast or new
alias is retained. Earlier experiments around the136B helper's class-result
return added11 or6 bytes to insert_equal and were discarded. The simpler
factory binding preserves both the59B and136B shapes and their native calls.

The forwarding specialization emits no standalone function (COFF evidence:
zero definitions). Its absent-from-retail marker labels only that compile-time
forwarding view; the real34B factory remains rowed, called and verified.
The strict frozen-source check accepts it. No present-unmatched hatch is added.

## Existing pin, complete proof

The official pin_admission.fold_proof_problems succeeds with no problems,
recursively proving the existing59B typed insert pin and its136B _M_insert
callee in the same defining object. Their established native owners remain
unchanged. The existing pin is removed/re-added only through the normal
pin_admission.add_pins path to attach fold-proof=texturepacker.cpp. Its name
and address are exactly the old ones. Complete before/after pin multisets
are identical; pin consistency passes; the entire hatch register is byte
identical. No second pin, new address or permissive gate change is made.

The subsequent scoped identity scan certifies the call:46 references,37 owner,
7 fold,1 EH,1 alias, zero wrong bindings (previously6 fold and1 wrong/unknown).
This clears that one finding, not every provider or legacy alias in the TU.

## Verification boundary

Ordinary and strict provider verification pass81/81 rows across texturepacker,
StlSweepW5Rva00170E3D and RvaTreeValueEraseFamily, including the existing
STLport constructor fold,2 float literals and exact parent-based placement
of the six renumbered compiler cleanup labels. No row or source path moves.
The published0156fc269e preview keeps all three units LINKS3344->3344 bytes.
These are existing scoped bytes; no new match, headline census credit or
runtime proof is claimed. The outgoing consumer audit and post-rebase
verification remain required before publication.

## Current master and consumer audit

The source commit rebases cleanly to19915717a58fa3cb00245b5d49b814889fcb7abb
on base80879e4e81098808542b62e5792de39c5d117bd0. The incoming canonical
AssetReference header adoption changes one helper source, so all three
providers are strictly verified again:81/81, one constructor fold,2 float
literals, same exact parent cleanup placements. The current scoped identity
scan still reports46 references,7 folds and zero wrong bindings. No new pin
name/address, hatch-register change or row/path change accompanies the rebase.

The newly fetched published index is984a4cdc4d (2026-11-02 08:35), with18203
reusable objects imported. The explicit full outgoing audit over all three
verified providers returns2 INCONCLUSIVE: its baseline predates the outgoing
base, and affected consumerCommon/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry the atlas insertion proof, three providers and affected
consumers into the next scheduled census; no whole-consumer clearance or
headline credit is claimed. No whole-tree build, direct census or smoke run
was started.
