### AptPlayerStatus destructor unused CRT declarations (2026-10-30, codexb4)

At base `3134afceb4`, removing unused `memset` and imported `sprintf`
prototypes from AptPlayerStatusDtor.cpp retires its two Microsoft-header
findings through the owning scoped scanner. All six function rows, the
string reference and the parent EH graph remain exact. All 19 external
COMDAT fingerprints and definition/reference sets are unchanged. Strict
preparation passes; ordinary preview retains LINKS, 263 -> 263 authored
bytes, against index `85f6b7f40c`. [Evidence](../../reverse/attempt_support/apt-player-status-crt-20261030-codexb4/README.md).

The outgoing audit remains INCONCLUSIVE: the index predates the batch base
and the earlier LinearCampaignManager.cpp provider lacks a current strict
receipt. Carry that provider and affected consumers into the next scheduled
census. No census-linking or image-ownership gain is claimed.
