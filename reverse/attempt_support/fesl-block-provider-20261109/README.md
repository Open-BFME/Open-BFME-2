# FESL block/buffer deleting provider, 2026-11-09

The picker served `??_7Rva00802680Owner@@6B@` at RVA 0x008E3D28 in
Rva00802640FeslCtor.cpp. Its first deleting wrapper called the external
destructor rather than matching retail's complete 72-byte wrapper at
0x0066E960. Y2FeslBrowserDestructors.cpp already owns the verified body.
This is the sibling LINK-619 provider issue, not missing byte coverage.

The constructor's existing flat ABI view now defines its cleanup inline:
zero +4/+C/+8, reset the +30 then +28 buffer views, clear the +20 block
view, and explicitly tear down the existing base view. Force-inlining the
cleanup preserves retail's wrapper rather than emitting a short call to
a separate destructor. No optimization pragma, asm, pin, alias, row,
source-path change or artificial emission anchor is added.

This is a deliberately partial ABI view. The casts refer to the established
destructor views of native subobjects; the declaration does not recover a
standards-complete inheritance/lifetime model or original class identities.
The initialization-only V2ZeroInt/V2ZeroPair views are retained. No donor
layout, original field ownership or whole-class recovery is claimed.

Verification:

- Normal and strict checks verify 21/21 rows, 671 bytes across constructor
  and destructor files; EH has zero obligations. Frozen-file and new-variant
  checks pass. The separate destructor source remains byte-for-byte unchanged.
- All retained constructor/helper bodies, code flags, selection policies,
  relocations and data are unchanged. The only changed COMDAT is the owner
  deleting wrapper: its complete body/relocations/flags/policy equal the
  verified provider, and independently match native 0x0066E960, 72 bytes.
- Only the existing base's 31-byte deleting wrapper and four-byte compiler
  table are added; both equal the verified provider. The wrapper independently
  matches native 0x0066E690. No standalone base constructor/destructor is
  emitted. All original destructor-file object facts are unchanged.
- Paired previews preserve LINKS at 671 bytes using the refreshed index
  717b70f4ab (2026-11-09 00:25, census a46241d8d1). No census runs here.
- Bounded eight-source replay clears one target-not-winning-provider refusal.
  Temporary bridges rise from one/nine slots to two/eighteen slots. Both
  native tables are 36 bytes; both compiler tables remain four bytes. Four
  cached supporting objects lack strict receipts, listed in proof.json.

The actual file and all emitted code were checked rather than transferring
the previous sibling's result. An initial larger cleanup stayed out of line;
the force-inline trial was judged against all 72 bytes and relocations before
application. No nonmatching trial is left in Code/.

Remaining: complete both nine-slot tables and actual class recovery, then
verify their selection in the next census/real image. No bridge retirement,
headline linked-byte gain, game-start or runtime clearance is claimed.
