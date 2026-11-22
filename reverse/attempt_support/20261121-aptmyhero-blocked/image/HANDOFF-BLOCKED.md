# AptMyHero008: ImageCollection prerequisite remains blocked

Status: **blocked; zero completed queue items and no production proposal**.
Evidence basis is clean HEAD `55dd91d046f25ce01a961f2582867b2b620dcdcf`,
Unresolved source SHA-256
`0b7f226bec8cc35e0ffdaea8c8f20bedb7fd908fc1a790052ae93f9ad0a82a3a`.
Root has since staged an independent Matrix3D prerequisite. These are historical
probes against the stated snapshot, not current-head admission results.

## Actual family and intended legitimate adoption

The Unresolved source has a private method-only ImageCollection declaration and
TheMappedImageCollection extern, with no direct calls or field reads in this TU.
The main AptMyHero source already uses the canonical GameClient/Image.h.
That header defines the actual 24-byte ImageCollection: SubsystemInterface at0,
map at12, constructor RVA002D932B, destructor002D9283, and findImageByName002D92F6.
Its real std::map requires its documented `// stlport` marker. Neither a replacement
container nor a private fallback header was proposed.

The native header-adoption misclassification route does not apply: the queued
historical source really contained a private body. Removing the unused body and
claiming it was only a forward declaration would not be an honest retirement.

## Reproducible controls

`image-probe.json` is the actual native tu_skeleton.Verifier result for an early
real Image.h include at the removed private declaration, plus documented STLport
opt-in. All temporary compilation outputs are private; native flags and gates are
unchanged, BFME_OBJSTORE is off.

- Current source:16/16 matching rows.
- Candidate:12/16. Missing RVAs005B190D,0079EF4A,0079EF52,0079EF78.
- Public destructor RVA`0x005B190D`, complete row extent250 bytes, COFF symbol
  `??1AptMyHero@@UAE@XZ`, emits246 bytes rather than250.
- The four-byte EH-state store before releasing the +15C vector is absent.
- `image-code-audit.json` records all13 public strong code definitions. Only the
  AptMyHero destructor changes. Its BfmePod8Vector destructor stays exactly14
  bytes with exactly the original `_free` relocation. The main direct `_free`
  call also remains `_free`; this is not an import-name mismatch.
- The three other missing rows are local cleanup funclets, not new public names.

One further justified control put the real Image.h include after the existing
BfmePod8Vector definition, preserving its original declaration context. The
compiler rejects it with actual Microsoft stdlib.h(279) C2375: free redefinition,
different linkage. See `image-probe-late.json` and the corresponding log.

**Certain:** both observed controls fail normal admission. **Probable:** the
real standard-header context affects the destructor EH treatment. A precise
language-level explanation or a broader canonical Apt class solution has not
been proved; it is not a license to change free prototypes, flags, guards or
exception specifications until the desired bytes happen to emerge.

## Artifacts and replay

`early-BLOCKED.cpp.txt`/`.patch` and `late-BLOCKED.cpp.txt`/`.patch` preserve both
unsuitable candidate sources unambiguously. Their hashes are in
`image-code-audit.json`. Neither patch is approved for production. Older
`AptMyHero_Unresolved.image.cpp.txt` and `imagecollection.patch` were overwritten
by the late variant during diagnosis; do not mistake them for the earlier probe.

The private script `../aptmyhero008_image_probe.py` performs the two native
experiments, using `--late-header` for the second. Re-running it must first refresh
all source/header currency and is unnecessary while Root owns staged changes.
`../aptmyhero008_image_handoff.py` only reconstructs these two historical textual
artifacts from Git and audits already compiled objects; it does not compile or
write production files.

`image-small-receipt.json` is the compact transferable receipt: exact public
destructor row/symbol/250-byte extent, both actual COFF byte/relocation records,
and hashes for the early/late banks, diffs and native results. The first probe
log was created at2026-11-21T00:59:02.9719064Z; the last probe receipt was written
at01:02:10.7917731Z. This proves an artifact window of at least3 whole minutes
(187.82 seconds). **Total/active work time is unknown and has not been estimated.**
The receipt labels the3-minute figure as an artifact-window lower bound only.

No flags, aliases, row baselines, source-owned data addresses, declarations of
free, or hatches were changed. No full link or runtime claim follows from this
diagnosis.
