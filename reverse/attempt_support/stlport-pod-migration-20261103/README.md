# POD-vector STLport 4.6 migration: complete byte proof, ABI closure pending

Inspected base: `7fe05e7dac`, 2026-11-03. The default picker reserved
`Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp`.
The trial queue's two library matches cover only72 bytes; the actual source
currently owns160 matched rows. The unchanged4.5.3 control and final normal
build both preserve all160. No migration or source edit is landed here.

## New verified evidence

The private candidate selects the normal supported4.6 profile, adapts18
allocator declarations to its non-const API, removes two obsolete proxy
allocate/deallocate specializations, and supplies explicit null hints at four
calls that now reach the inherited allocator API. It compiles without changing
vendor headers, compiler promises, pins, aliases or shared shims.

All160 complete row bodies match retail through the existing trial tool's
diagnostic `TranslatingSymbolMap` and `compare_row(..., translate=True)`.
That translation resolves actual emitted non-const QAE allocator symbols to
the native addresses already owned by the old const QBE rows. It is diagnostic
evidence only, never a gate exception, ledger binding or landing mechanism.
Without translation,124 rows pass. The older34/157 failure report was therefore
not evidence of34 independent code-generation defects. The current result
separates API/mangled-name binding from native instruction mismatch.

## Why the standalone file move is blocked

Seventeen const allocator rows live in this file. A4.6 class cannot emit those
old const member definitions. Moving to4.6 must preserve or coherently migrate
every actual remaining old-name consumer; merely admitting new names does not
make those consumers call them.

The bounded index/cache audit identifies16 outside caller sources and46
runtime call/tail-jump relocations, including17 edges belonging to matched
caller rows. Nineteen outside old-name provider copies cover12 of the17 names
and equal the control's complete bytes and symbolic relocations. These are
provider facts, not TU approval or final selection proof. Two objects have
receipt/source freshness exceptions; the audit is explicitly bounded to the
historical984a4cdc4d index and may miss new sources.

The committed TU map's function fingerprint is stale. Fifteen allocator rows
have no committed destination, one is only proposed and one has an old approved
assignment. None establishes a fresh approved rehome for this operation.
No allocator row is moved to a convenient alternative provider.

A coherent migration of the known caller set also includes SidesList.cpp,
currently file-reserved by `StarkillerHDX@fleet`. The live dry run reports16
claimable files and that one held file. No foreign source is edited or compiled
as a migration candidate. No compatibility pin, copied allocator class, fallback
header or vendor API alteration is introduced to avoid that prerequisite.

## Next useful work

Refresh the discovery against current providers/index and obtain the complete
caller scope when available. Migrate its genuinely required consumer cohort,
including any additional const allocator ownership discovered there, before
retiring old-name bindings. Verify every row in each affected source, actual
include selection, complete external definitions, undefineds, data/EH and the
joint provider/consumer link result. Rehome only if the current authoritative
TU machinery independently approves it. The banked candidate makes no original
application-type/TU or semantic-name claim.

The current Code file remains on4.5.3, byte-exact. No headline figure, migration
credit, debt retirement, census improvement or global closure is claimed.
BFME1's shared account record remains fresh at verified131fb8ff from2026-11-01;
this investigation did not repeat its official-upstream check.
