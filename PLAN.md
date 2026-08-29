# Open-BFME-2 bootstrap plan

Reverse engineer BFME 2 the way Open-BFME-1 does BFME 1: byte-exact function
recreation against a committed retail baseline, converted by an agent fleet,
gated by hooks. This plan encodes what two months of BFME 1 taught us and skips
the evolution — we start at BFME 1's current endpoint (ledger schema,
pin-consistency, conversion gate, partial-banking, union-merge config all from
day 1).

## Verified target facts (2026-08-29)

- **`lotrbfme2.exe` is NOT the game.** It is a 495KB launcher stub, and the
  copy in `~/.wine/drive_c/BFME2/` is IDA-patched (no-CD; `lotrbfme2.dif`
  documents the exact bytes). The engine is **`game.dat`** (10,969,600 bytes,
  a normal PE). Target `game.dat`; never baseline the stub.
- **Install is official patch 1.06, and the baseline preflight PASSED
  (2026-08-29).** Three-way verification:
  1. Installed `game.dat` and `worldbuilder.exe` are byte-identical to their
     pristine distribution copies in the Workshop's content-addressed cache
     (`~/.wine/drive_c/BFME Workshop/Cache/<md5>.pfcache`; naming scheme
     verified via the canonical empty-file md5).
  2. An independent Hybrid-Analysis sample carries the identical sha256 and
     identifies it as 1.06.
  3. Read from our own bytes: version resource `1.6.2429.30210`, PDB debug
     timestamp 2006-09-25 22:54:43 UTC ("Version 1.06 - September, 2006" per
     `launcher.txt`; the PE header timestamp is scrubbed to 1970 — use the
     debug directory).
  `game.dat`: md5 `34391b253b0ee12d6cec1178f46d3bf9`, sha256
  `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`,
  10,969,600 bytes. `worldbuilder.exe`: md5 `50a71402f29442f7a87d51240bff0e0b`,
  sha256 `af1d464083e45f65331aab2ee1d0b3f4a0b89ac719d875a686a440fe04792f68`,
  33,771,520 bytes. Provenance: BFME All-In-One Launcher install.
- **Same toolchain as BFME 1: MSVC 7.1** (linker 7.10). The committed
  `build/toolchains/vs2003` is reused as-is, and every codegen recipe in
  BFME 1's `docs/lessons.md` (vptr scheduling, `throw()` states, `novtable`,
  the EH-transposition wall, private static-call convention) transfers 1:1.
- **`.text` is 8,096,994 bytes with only 1.5% `0xCC` padding** — BFME 2 is
  NOT incrementally linked (BFME 1: 13.0MB `.text`, 25.7% padding, ILT thunks
  everywhere). Real code ≈ 8.0MB vs BFME 1's 9.7MB: a slightly smaller
  target, and the entire incremental-link-thunk ambiguity class (the worst
  pin_consistency pain in BFME 1) mostly disappears.
- **The binary carries its own source tree map.** Assert strings keep full
  paths: `C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\...` — the
  exact `Code/` layout ZH and BFME 1 use. Of 173 recovered paths: ~53 exist in
  the ZH reference, ~54 in BFME 1's `Code/`, 116 are BFME 2-new (HordeContain
  family, CreateAHero, LivingWorld, Apt* GUI, FXParticleSystem modules,
  AIWallBuilder, new AIUpdates). Watch case drift (`GameLogic/Ai/` vs
  BFME 1's `GameLogic/AI/`) — `check_case_collisions.py` matters on Linux.
- **1,964 mangled C++ exports** (BFME 1 had ~1,300) — free ground-truth
  identities including template statics (`FXParticleSystem` keys visible).
- **Same third-party stack**: `STLPORT_` section, FESL (`jabba\fesl` strings
  shared with BFME 1), Miles (`mss32`), `d3dx9_27.dll`, GameSpy-era netcode.
  BFME 1's prebuilt-lib lane (10.84% of its held bytes) applies directly.
- **`worldbuilder.exe` (33.7MB, same 7.10 linker) has `.reloc` and `.idata`
  sections.** Relocations are DIR32 ground truth the game binary lacks —
  commit it in the baseline from day 1 (BFME 1 did) and use it to
  cross-anchor shared engine TUs even before WB conversion starts.
- **The RotWK exe in `~/.wine/drive_c/RotWK/` is a cracked/unpacked binary**
  (SafeDisc `stxt*` + ImpREC `.mackt` sections). Unusable as a baseline.
  RotWK later requires a clean 2.01 `game.dat`.

## Community landscape (why the roadmap differs from BFME 1's)

- **Off-host delay fix already exists**: RotWK unofficial patch 2.02 v9.0.0+
  ships it, and BFME 2 patch 1.09v3+ carries the same fix. Do NOT lead with a
  delayfix port. BFME 1's netlat work (mods/features/03x) ports only if it
  measurably beats 1.09v3's fix — verify before promising.
- **High FPS is unsolved and is our flagship item**: the known "unlock"
  (delete `USEFPSLIMIT`/`FPSLIMIT=30` from gamedata.ini) speeds up game logic
  itself because logic is frame-locked. Real 60/120 FPS needs logic/render
  decoupling — exactly what byte-level source recovery enables and what no
  INI patch can do.
- **No existing BFME 2 decompilation project** (OpenSAGE is a clean-room
  reimplementation, not byte-match). Greenfield.
- Community infra to stay compatible with: T3A:Online, BFME Workshop /
  All-In-One Launcher (our baseline provenance), GameReplays 1.09v3 (INI/asset
  layer over 1.06 — our vanilla-1.06 baseline stays the correct substrate).

## Repo design decisions

1. **Fresh repo `Open-BFME/Open-BFME-2`** — same GH org, not a fork. BFME 1's
   593MB of ledger-churn history buys nothing here.
2. **`reference/open-bfme-1` = git submodule** of Open-BFME-1, pinned SHA,
   `shallow = true` in `.gitmodules`. One pin brings everything shareable:
   - ZH source (`reference/CnC_Generals_Zero_Hour`, 93MB) — no re-vendoring
   - BFME 1's converted `Code/` (114MB) — the nearest-ancestor reference,
     already ZH→BFME-reconciled, and it keeps growing
   - `vendor/` (STLport, d3dx9, dxerr9, comsupp) and `reference/shims/`
   - the vs2003 toolchain (`build/toolchains/`)
   `build.py` toolchain/reference constants point into the submodule. Bump the
   pin deliberately (it is a reference, not a dependency — a stale pin only
   costs sweep yield). Fleet writers clone locally so git hardlinks the
   objects; contributors do `git clone --recurse-submodules`.
3. **Fork `tools/` and hooks by copying** from BFME 1 at bootstrap; adapt the
   ~8 files with hardcoded paths (`build.py` `MANIFEST`/`EXE`, `progress.py`,
   `modbuild.py`, `dir32.py`, `gaps.py`, `callers_of.py`, `fieldnames.py`,
   `audit_ret_arity.py`). Do NOT try to make BFME 1's tools dual-target —
   coupling two live repos is worse than divergence. Expected divergences are
   real ones: no-ILT simplifications, BFME 2 sweep sources, flag deltas.
4. **Baseline**: `baselines/bfme2/workshop-vanilla-1.06/` with
   `manifest.json` (schema_version 1, hashes, PE facts, provenance note about
   the launcher-stub patch) plus `files/game.dat` and `files/worldbuilder.exe`
   committed directly (plain git, no LFS — BFME 1 precedent).
   Leave room for `baselines/rotwk/…` as a later third target.
5. **Fleet**: new root `~/Projects/open-bfme2-local-fleet/` via the copied
   `setup_local_fleet.py`, so both games' fleets run simultaneously.
   `AGENTS.md` carries over nearly verbatim (work selection, work-the-file,
   anti-lift, partial-banking, placement rules).
6. **Ledgers start empty but with today's schema and gates**: `functions.csv`,
   `symbols.csv` (+ union-merge `.gitattributes`, consistent line
   terminators from day 1 — BFME 1's `\r\r\n` mess was pure legacy pain),
   `pin_consistency` in hooks from the first commit with an EMPTY baseline
   backlog (only-shrink rule enforced from a baseline of zero).
7. **`mods/` + `cave.py` pipeline works from day 0** on `game.dat` (jmp-hook
   into an appended section needs only addresses, not decomp) — early
   feature-patch capability while conversion ramps.

## Bootstrap sequence

Phase 0 — repo skeleton — DONE 2026-08-29
- [x] Repo created, README/LICENSE/`.gitattributes`/`.githooks` seeded.
- [x] Submodule `reference/open-bfme-1` pinned at 125e52fd0 (shallow).
- [x] Baseline `baselines/bfme2/workshop-vanilla-1.06/` committed
      (game.dat + worldbuilder.exe + manifest; hashes preflight-verified).
- [x] `tools/` + hooks copied and adapted (toolchain + ZH reference resolve
      through the submodule; `vendor/` and `reference/shims/` copied);
      `docs/lessons.md` seeded with the pointer + no-incremental-link note.

Phase 1 — prove the loop — DONE 2026-08-29
- [x] Flag calibration: 756 BFME 1-matched bodies appear VERBATIM in
      game.dat (72KB), 1,534 more with call operands wildcarded — same
      compiler, same flag families. No systematic drift found.
- [x] Ghidra headless inventory of `game.dat` (`ghidra_functions.csv`,
      `string_xrefs.tsv`, `vtables.tsv`); `exports.csv` generated from the
      PE export table (1,964 names, 1,428 code). Worldbuilder Ghidra project
      + reloc harvest still pending.
- [x] Loop proven far past one function: zlib 1.1.4 (65 bodies, 11 TUs),
      EAC codecs, LZHCompress, CompressionManager_decompressData, WWLib md5
      — 143 byte-verified functions, six symbols.csv pins, hooks green.

Phase 2 — mass landing, in measured-yield order (the first weeks)
- [ ] Prebuilt-lib sweep (`lib_window_sweep.py`/`obj_sweep.py` lineage):
      STLport, FESL, Miles stubs, d3dx9, GameSpy. Cheapest mass; BFME 1 got
      10.84% of held bytes here. The GameSpy/FESL permission grant extends to
      this project (owner confirmed 2026-08-29) — record the scope in this
      repo's own `PROVENANCE.txt` alongside the vendored tree, mirroring
      BFME 1's.
- [ ] Reference sweep A: **BFME 1 `Code/` tree** compiled TU-by-TU against
      `game.dat` (the `zh_sweep.py` machinery pointed at the submodule).
      Nearest ancestor, expected top yield on engine core.
- [ ] Reference sweep B: **ZH `GeneralsMD/`** for TUs BFME 1 hasn't converted
      yet (never `Generals/` — BFME forks from Zero Hour).
- [ ] `gen_asm` dump generation for everything still unclaimed — establish
      the boundary-proven conversion queue (`list_naked_candidates.py` lane).
- [ ] Identity harvest: exports (1,964), vtables + `Clone`-slot reasoning,
      string anchors, ModuleFactory registration blocks, worldbuilder reloc
      cross-anchors. Feed `next_work.py` tiers.
- [ ] Re-run sweeps A/B whenever the BFME 1 pin advances (their new
      conversions are our free candidates — the cross-repo flywheel; later,
      evaluate the reverse direction for BFME 1).

Phase 3 — steady state
- [ ] Fleet on the AGENTS.md loop; `progress.py` headline in README; same
      convert→verify→commit→push cadence, same partial-banking discipline.

## Roadmap (README order)

* [ ] BFME 2 Source Code (0% → sweeps land the first mass)
* [ ] 60/120 FPS — logic/render decoupling (flagship; community "unlock"
      just speeds up the game)
* [ ] Memory fix (LAA/allocator)
* [ ] Better crash logs
* [ ] Multi-CPU
* [ ] Worldbuilder Source Code (baseline + reloc harvesting from day 1)
* [ ] Bigger maps / more players
* [ ] RotWK support (deferred by owner 2026-08-29 — revisit after BFME 2 has
      momentum; needs a clean 2.01 `game.dat`, the current wine copy is
      cracked; where the competitive community lives via 2.02)
* Delay fix: NOT planned unless it beats 1.09v3/2.02's existing fix —
  verify theirs first, port BFME 1's netlat findings only if there's a gap.

## Owner decisions (2026-08-29)

1. **GameSpy/FESL permission extends to Open-BFME-2** — sweep and vendor
   those sources; record the scope in this repo's `PROVENANCE.txt`.
2. **RotWK deferred** — not now; keep the roadmap slot, no baseline work.
3. **Baseline preflight done and PASSED** — evidence in "Verified target
   facts" above; freeze `workshop-vanilla-1.06` as-is.
4. Repo README reuses BFME 1's measured agent prompt verbatim (it was A/B'd;
   vague prompts produced zero progress).
