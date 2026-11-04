# Wind header publication recovery, 2026-11-04

Recovery scope: the seven commits preserved by
`refs/runner/preparation/1793814335165757417`. No saved stash or uncommitted
edit was named by the preparation record. All seven commits rebased cleanly;
the backup remains intact.

The first local push dry run refused the removed WindModuleInfo queue row for
FXParticleSystem.cpp. An ordinary three-provider preview identified unresolved
`?DoXfer@DefaultAlphaModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z` and
`?DoXfer@DefaultColorModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z` in the main
provider, predicting 5,650 -> 0 bytes. The two smaller wind providers preserved
284 and 272 bytes. The local index was from 2026-11-04 16:16 at 2f0cb97f52.

Upstream commit a67341daa5 already renamed and verified both native transfer
providers and their consumers; it is outside this recovery's outgoing range.
`link_check.py --update-index` successfully refreshed local compiled evidence.
The next `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` passed:
424/424 function rows, four data rows, all reference checks, DIR32, three exact
EH rows and the header retirements. Its broader batch link audit remained
INCONCLUSIVE because current consumer receipts were unavailable; no complete
link closure or measured gain is claimed.

The runner accepted the seven-commit bundle, but the fleet publisher subsequently
refused the same main-provider header retirement against base 95f193bec507.
Its diagnostic again reports a predicted loss of census-linked bytes. Unlike
the local reproduction, that diagnostic does not name the missing symbols;
stale publisher provider evidence is an inference, not a proved fleet diagnosis.
After rebasing again, the unchanged local three-provider preview reports LINKS
for all three, preserving 6,206 bytes. This is local preview evidence, not a
new census or proof of the publisher's inputs.

Restore only the original FXParticleSystem.cpp WindModuleInfo queue row. Keep
its byte-verified canonical-header adoption and both accepted smaller-provider
retirements. The two TU consolidations and their debt-key transfers remain
unchanged. This defers one retirement without discarding useful recovered
source. Retry its supported `header_adopt_lane.py accept` command after the
publisher can independently reproduce the current provider preview. Eight
Common rows retain their separate identity prerequisites under LINK-247.

Recovery publication transcript: local scratch
`build/recovery-publish-20261104-codexb5.log` (not tracked).
