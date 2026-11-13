# Pinger shared-flag byte-alias contract (root20, 2026-11-14)

Default data selection served pingerMain.c duplicate _piSettingData at A0C104.
The existing owner in peerPing.c and consumer still define private statics.
Prior direct-extern, argument-capture, /Oa, /Ow and volatile decoder trials were
read before proposing a new expression. No prior failed trial was repeated as
a claimed new result.

One narrow new clean-C hypothesis was tested: make peerPing.c the external owner,
make pingerMain.c extern and use /Ow there, then access only the decoder's magic
and version stores/checks through an unsigned-char view of udpPing. Keep all
word-field expressions and the original memcpy. The first build exposed C89's
declaration-before-statements requirement; the corrected test puts the local
view before asserts.

Corrected normal cohort result: 18/19. Only piBytesToPing still fails; the first
buffer increment precedes the native magic store, and payload loads/stores still
interleave differently. This byte view does not solve either remaining scheduling
boundary, so no combined volatile-payload repetition was justified. Exact native
and candidate decoder bytes are in the adjacent JSON.

Both source files were restored byte for byte. Final ./build.sh passes 19/19,
zero string/float refs and two named imports. No flag, source, ledger, baseline
or ownership change is retained. No debt-retirement command was attempted on
the nonmatching candidate. piNextID's four keys remain separate debt.

Current tu_evidence --source pingerMain.c prints only its CSV header: no new
structural placement evidence. Relevant committed tu_map rows still have no
approved destination. The two files also contain incompatible same-name static
piFindActivePing signatures and duplicate send/queue helpers, so combining text
without identity/preamble reconciliation is not a supported merge.

## External donor facts and limits

The third-party [2017 import](https://github.com/GameProgressive/UniSpySDK/commit/4579b61c73137dbab080402f82a19a950c28b2d1)
labels itself GameSpy 2007 SDK. Its [pinger/pingerMain.c](https://github.com/GameProgressive/UniSpySDK/blob/4579b61c73137dbab080402f82a19a950c28b2d1/pinger/pingerMain.c)
(blob d6b8297e35c2d5a5d3553783aa2fc161e2576040) contains the response/init/queue/
timeout/ping families together and one shared static flag. That supports donor
cohabitation, not BFME II's original source path or exact SDK release. The import
already uses v140 projects; its Common Code 2.06.00 changelog is not a pinger
release. Its piFindActivePing signature and dispatch naming also differ. No
fork source was copied into Code and no BFME1 upstream check/fetch occurred.

Next: obtain placement-owner-accepted original release/build-path evidence or a
genuinely new clean-C contract hypothesis that verifies the complete cohort.
Do not change the baseline, fabricate a vendored version, move unapproved rows
or use scoped optimization/alias hatches. Baseline, corrected trial, restored
build and fresh TU evidence logs are under build/root-pinger/.
