# Transaction field binding: blocked on existing-global naming

The local three-consumer trial loads m_name at offset four from the existing
12-byte Rva007B55E0TxnName records rather than three missing pointer globals.
The records at RVAs A0A00C/A0A0FC/A0A180 are already rowed and initialized by
Rva007B55E0TxnNameInits.cpp. Their native categories/values are respectively
blob/UpdateBlobInfo, recp/UpdateRecord and club/UpdateClub.

The trial passes the official four-source build: 66/66 functions and 69 data
rows. COFF verifies each existing record relocation with addend four; the old
names disappear. Provider-inclusive preview is 4/4 clean, 2,867 bytes, using
stale census 0534e78db3. These checks do not authorize a hatch increase.

Normal hatch_counters --update refuses two additional address_global
occurrences in each consumer. No admission or baseline edit was used. All
three source trials were reverted and rebuilt: 3/3 functions and all
reference checks pass. The corresponding records and initializers are intact.
The trial and original repair drafts are saved under
build/decal-diagnostic/network-transaction-blocked/.

Next prerequisite: use the official inferred-global naming and normal rename
transaction for these already-rowed records, then apply the consumer repair
under the accepted names. Do not add standalone zero globals, aliases, a
wrapper, overlapping data rows, or hide the address spelling behind a macro.

The initial name_lane next request for those three exact global keys serves
none. Its owned inventory intersects matched data rows with
name_metric.global_names; the direct-initialized record declarations are
missing from that inventory while seven ordinary string globals are present.
Investigate the syntax recognition with a regression test before naming; do
not forge an agreement or bypass the served-key check. Provider file and all
three record addresses are claimed for this prerequisite. Claims retained.

## 2026-11-17: verified existing records and native field bindings

The prerequisite is now resolved locally. The naming inventory's literal
initializer recognition has its own tested tooling commit. The official naming
lane accepted independent Luna/Astra semantic-inference votes and applied three
names: TheBlobUpdateInfoTransaction, TheRecordUpdateTransaction and
TheClubUpdateTransaction. These are inferred readable names, not claims about
retail spelling. The normal rename updated the existing provider, registry
lookups and three owned data rows; it did not add a global or initializer.

The three consumers now read m_name from those existing 12-byte records.
Official verification passes 70/70 functions and 76 data rows for the provider
and lookup unit, and 3/3 functions for the consumers. COFF proves DIR32 addend
four reaches retail VAs 00E0A010, 00E0A100 and 00E0A184 respectively, and all six
old provider/phantom names are absent from the five rebuilt objects. The three
new symbols are defined by the original provider. data_check --enforce reports
zero findings in all five units. Scoped link preview is 5/5 clean, 2,639 to
4,120 bytes, against the explicitly stale 0534e78db3 census. This is a preview,
not a fresh full-link result.

The normal hatch_counters --update shrinks address_global from 3,642 to 3,627;
no admission, new alias, pin or baseline expansion is used. An independent
read-only review found no ABI, ownership or naming correctness issue. The
protected heuristic data_ledger cache is not hand-edited: verified data_rows
owners override its stale names as documented by data_ledger.load. Evidence:
build/decal-diagnostic/name-global-init/{apply-native.log,consumers-build.log,
transaction-bindings.json,link-preview.log}. A fresh real link must confirm
removal of the three missing references; runtime is not yet established.

### Commit packaging refusal (not a C++ failure)

The normal hook refused the attempted combined vote-and-source commit. No
commit or publication occurred. The original provider Git blob has SHA256
c94000f4cd26fd52a62ff33fce33b2c7c05e782f2dea809e0846b7a64b862385 (LF); the exact
source served by the official native review packet has SHA256
69e08282c0c2cf7e81632748143e9d2b2124c79ad7e1c9dc3950bc127e6791d3 (CRLF). The six
recorded vote hashes truthfully bind that packet, but cannot pass the hook's
Git-blob fingerprint rule even in a prior records commit. The renamed staged
source has SHA256 58142b2d1f01fbf6227ba1b48f894c7d603511a32232fc99f1b1904b1ed2e673.

No hash was rewritten, no carry fabricated, and no gate weakened. The naming
workflow must be recovered with canonical source bytes and fresh official
records, retaining these rejected transaction artifacts as evidence. Once
correct records exist, docs/naming.md requires the vote/agreement/resolution
commit before the source landing. Local C++/object validation above still
holds; commit readiness and publication are explicitly blocked.

### Native link measurement before naming recovery

The official `exit_link.py --link --local` run completed on 2026-11-17 against
HEAD a936092597 plus the preserved network worktree change. link.exe returned
1120 in 80.0 seconds: 10 unresolved names, zero duplicate names, no image.
All three network names and both SidesList parser-slot names disappeared from
the preceding 15-name result. The measurement used 17,526 objects; omission
proof covered 945/945 funclets with zero missing callers. Existing scaffolding
remained: 468 initializer bridges and 3,122 table bridges (45,949 slots).
This is not a working executable. Exact snapshot and log are preserved under
build/decal-diagnostic/native-real-link-sides-network-20261117/ and its .log.
The complete workflow took about seven minutes including proof/setup/reporting;
80 seconds is the linker-only time, not the total command time.

After preserving every changed file and the staged patch under
name-global-init/rejected-transaction/, the uncommitted naming transaction was
restored to HEAD for a fresh official approval round on canonical LF content.
No published record was changed. Previous votes, proposals and full review
artifacts remain as evidence; no missing global or alias was fabricated.

### Naming recovery completed locally

Fresh actual Luna/Astra proposals were served from the exact canonical LF
preimage. Both independently proposed the same three names, so no resolution
or hash adjustment was needed. Normal hooks accepted the prior naming-record
commit 42d083ebc5. The normal name_lane apply then landed all three names:
70/70 functions and76 data rows pass. Reapplying the exact preserved consumer
patch passes3/3 functions; the explicit COFF field-binding proof passes again.
No gate changed. This supersedes the commit-readiness blockage above, while
retaining its failed transaction and review packets for audit. Evidence:
lf-native-review-control/, lf-votes-commit.log, lf-apply.log,
lf-consumers-build.log and lf-bindings.log under the same scratch directory.
