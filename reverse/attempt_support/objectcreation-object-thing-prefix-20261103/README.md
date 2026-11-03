# Canonical Thing prefix for ObjectCreationUpgrade's Object view

Private probe only,2026-11-03. Include ../../../Common/Thing/thing.h before the existing Object partialview, derive Object publicly from Thing and shrink only pad00 from0x284 to0x284-sizeof(Thing). Keep existing mask, method declarations and friend unchanged. First Snapshot context is preserved: canonical Player/Module were already read before this include. No private Thing copy or complete Object recovery is claimed.

ALL20 current seed rows match in control and candidate. All30 existing external code/data definitions and ordinary symbolic relocations remain identical, with none removed or changed. One compiler array-construction helper ??_H@YGXPAXIHP6EPAX0@Z@Z is newly emitted (32B, no ordinary relocations); helper-comparison.json compares it to the prior verified Update control/candidate. No new Object/Thing vtable or application provider is emitted. This is not an identical external-set claim and not a proof of final whole-image provider selection.

A second sanctioned private Verifier run with compile-time sizeof(Thing)==0x60 and offsetof(Object,mask)==0x284 assertions succeeds with ALL20 rows exact. layout-proof.json records that boundary. No field's native mask offset changes. Current source passed find_declared_unmatched.py before probing.

No tracked source, ledger, claim, network or shared build-cache mutation occurred. Root must retain ordinary byte/data/EH/strict/link and provider-selection checks before landing. Candidate.cpp is scratch evidence only; no sourcefile reduction or census gain is claimed.

Tracked application: source matched control SHA256; normal20/20, owning Thing
acceptance and strict reusable receipts pass. No pending Thing queue entry was
retired for this source. The added compiler helper is exactly identical to
both prior Update controls; no application provider is replaced. No source
path or matched row moves. Subsequent Object-view and Update composition still
require their own layout/provider/byte checks and fresh approved merge.
