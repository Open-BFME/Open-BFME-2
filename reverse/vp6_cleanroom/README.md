# VP6 clean-room lane

game.dat statically links an On2 VP6 video decoder (retail 0x001B5530..0x001D8E7A,
including the SIMD block that used to be labelled BinkMmx/BinkSse). Public VP6 source
exists, but nobody has the right to redistribute it, so this decoder is recovered as
a clean room:

- A separate dirty room read that source and wrote one plain-language spec per
  function (`specs/<rva>.md`): what it does, its ABI, the struct offsets and retail
  tables it touches, its callees. Every constant and table is cited from retail.
- Three independent adversarial reviews (2026-10-08) checked every spec for copied
  expression, source-only facts and retail correctness before publication.
- You implement from the spec plus retail's disassembly, and the gate proves the
  bytes.

## Rules for implementers

1. Never open, fetch, search or paste any VP6/VP60/VP62 decoder source or derivative:
   On2, Winamp `libvpShared`, ffdshow, MFNode, `build/vp6-source-handoff`, or any
   copy of them. This lane is not a reference sweep; "Prefer coverage-first
   reference sweeps" in AGENTS.md does not apply to it. If you have read such source,
   do not take this lane.
2. Work from `specs/<rva>.md`, retail disassembly, and code already in this repo.
3. Commit with the trailer `Clean-Room: reverse/vp6_cleanroom/specs/<rva>.md` (one per
   spec used). A spec that is wrong or insufficient: record it with `tools/re_log.py`
   (`blocked "vp6-spec <rva>: <what is wrong>"`) and move on; never fix it from source.
4. Place recovered code under `Code/Libraries/Source/VP6/`; replace placeholder rows
   with `tools/add_match.py ... --replace-rva`.

`queue.tsv`: rva, size, name, ledger_status (what the ledger holds today), difficulty
(1 easy .. 3 hard), depends_on (specs whose functions this one calls; `ext:` marks a
callee outside this decoder). Take low difficulty first and claim with
`tools/claims.py claim 0xRVA` like any other row. All 300 specs are published.
