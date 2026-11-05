# Verifier upgrade and link-first plan (Open-BFME-1 and Open-BFME-2)

Status (October 2026): steps 2 (publisher tool; not yet the only path to `master`),
3 (gate checks), 4 (escape-hatch counters, shadow mode) and 5 (BFME2 link cycle) have
landed in both repos where applicable; step 6 is partial (retail inventories). Steps 7–12
are in progress.
This file is identical in both repos. Numbers come from an audit of Open-BFME-1 @ e5ce116448 and
Open-BFME-2 @ 22fb48d9ee; "measured" numbers were re-derived independently, "est." are estimates,
and simulated gains are ceilings, not targets.

## Why

The byte compare is strict about the bytes it compares, but much of what decides whether code is
right sits outside those bytes. Measured on the audit commits:

- Deliberately wrong code passed the real pre-commit hook 6 of 6 times in BFME2 and 4 of 7 in
  BFME1: a wrong callee via one new `symbols.csv` pin; a wrong global under an unseen decorated
  name; `gen-alias` in a row's notes masking every call target; local static data never
  compared; truncated string literals; switch jump tables never compared.
- BFME2 has 13 truncated string literals and 6 switch statements whose bytes match retail but
  whose case mapping is wrong (e.g. `piEnterResultToJoinResult` returns 1 where retail returns 10).
- A real `/ORDER` link of BFME2 with retail-byte fillers puts 37.6% of `.text` at its exact retail
  address, but only ~16% is placed *and* wired to the right targets. About half of the failures
  were the test link's own setup (exception-handler thunks, `__except_list`, imports), the rest
  mostly duplicate or wrong data definitions.
- In BFME1, link.exe 7.10's incremental thunk table can be reproduced exactly; it pins each
  thunked function's decorated name. 17.5% of thunks carry the exact retail name today; 6,336
  real-looking names are contradicted; 3,986 repairs can be derived automatically.
- Retail BFME2 GameEngine code was built with `/G7`, which no source declares; it explains ~405
  exception-table mismatches. BFME1 game code is one flag set (/O2, x87).
- Metrics: progress bars include prebuilt libraries, generated code and address-named
  placeholders; "linking %" means a file raised no error in a `/FORCE` link, never compared with
  retail placement.
- Every past metric, lane or gate that shipped without a guard was gamed within hours to days;
  shrink-only baselines, tombstones and `Verifier-Change:` trailers worked.

## Rules for every change below

1. Policy lives in hooks, tools and queues, not in AGENTS.md prose.
2. No metric, lane or queue ships without its anti-gaming check.
3. Every headline number has a counter beside it (aliases and pins per row, `__emit`/asm bytes).
4. Every escape hatch is counted and shrink-only: `gen-alias`, data pins, `object-symbol=` rows,
   `/alternatename`, `selectany`, `g_Va*` globals, `class-gate: allow`, `present-unmatched`,
   `#pragma optimize`. A 2× jump in 24 h freezes it until a `Verifier-Change:` commit lifts it.
5. Baselines only shrink, provably: agents may remove lines (the hook re-verifies each), only
   tools add them, and the checker that judges a commit is pinned outside that commit.
6. Checks are scoped to what a commit touches, never repo-wide totals.
7. Queues serve only items with a machine pass test and say where the code goes.
8. Only verified output counts; attempts and votes are reported separately; repairs are credited.
9. Rule changes are versioned and shown next to the old numbers.
10. Integration is scoped: each unit declares the paths it may touch (shared ledgers,
    headers and build files count); units with overlapping scopes are serialized; the
    final diff must stay inside its scope; incomplete units are never partially applied;
    repeated equivalent failures on one target are capped. (Planned for the publisher.)

## Plan

Days are wall-clock from adoption, overlapping, sized for fleets of ~45–130 commits/hour. Each
step names the bottleneck that more agents cannot speed up. Exit criteria, not dates, decide
promotion.

| # | Step | Bottleneck | Exit | Days |
|---|---|---|---|---|
| 1 | Admins restrict pushes to master to a publisher bot; fleets submit to a queue. Until then hooks run the checker from `origin/master`. | admin and operator decisions | direct and API pushes refused | 0–2 |
| 2 | Publisher: isolated builders without push rights, a pinned and separately promoted checker, signed receipts, continuous drain (no fixed sleep), per-operator quotas, dependency bundles and aging. | publisher gate-seconds vs arrival rate | bypass and crash fixtures pass; queue depth flat at peak | 0–3 |
| 3 | Close the gate holes in both repos: NUL-terminated string compare; exact `$L` jump tables; bytes past a row's extent equal retail; `.c`/`.asm` in the hook; `gen-alias` only as an exact token with a callee identical in bytes and resolved relocations; `symbols.csv` validation (RVAs, no data pins, no second name on an owned address); `object-symbol=` limits; local static data; keyed identity baselines; shared exploit fixtures in both repos; build provenance. | 48 h shadow per check on live traffic | every reproduced exploit rejected; no correct work rejected | 0–4 |
| 4 | Escape-hatch counters with the 2×/24 h freeze. | — | freeze fixture passes | 1–2 |
| 5 | Real link cycle as the only source of credit: `/ORDER` from the ledger, retail-byte fillers, quarantine loop; setup fixes (EH thunks belong to their function, `__except_list`, retail import libraries); every failing relocation per row; data checked by address and content; a second link at a shifted base; credit = unique retail bytes in verified closure, fillers/stubs/aliases never count; each cycle pinned to a commit, checker digest and build provenance. | link.exe, 45–70 min per host | deterministic receipts; series published next to the current bars | 1–6 |
| 6 | Tool-owned retail inventories: code and data extents, interior targets, thunk routes, an ICF fold list verified on bytes and resolved relocations, `data_items.csv`, `flag_regions.csv`. | — | every reference has a classified target or keyed debt | 2–6 |
| 7 | Data identity sweep: one definition per retail global, references bound by retail address, invented globals for retail constants replaced; extents, alignment, linkage and initializers preserved; residue to a queue. Largest single lever measured. | consumer recompiles, publisher, ledger conflicts | wrong/duplicate-global debt shrink-only | 4–10 |
| 8 | Code identity: allowed-symbol sets from retail address identities; tool-only `/alternatename`; rows for unowned targets only when bytes match; duplicate-definition tool; verification of the COMDAT the linker selected; name tiers (evidence / unverified / address) written only by tools. | aggregate links | wrong bindings shrink-only | 4–12 |
| 9 | BFME1 track: pause bulk renames and raw dump harvests; run the step-3 shadow gate; thunk-table name check in the hook; tool-applied name repairs with caller evidence; relocations recovered in MASM dumps; BFME1 link cycle (bind at the thunk, no ICF, x87). | BFME1 full gate and link | repairs landed; dumps relocatable; BFME1 series live | 0–14+ |
| 10 | Flags from `flag_regions.csv` (BFME2 GameEngine `/O1 /arch:SSE /G7 /EHsc`); `// cl:` overrides only through the tool; exception and funclet data verified. | region recompile + full gate | funclet failures 538 → <130 | 5–14 |
| 11 | Canonical classes: first make header gating fit a publish window; a canonical layout is accepted only with retail evidence (constructor stores, access widths, vtable targets) and all consumers verifying; private copies detected by layout fingerprint. | header gate and windows | registered classes have no private copies | 7–24 |
| 12 | Original source files by tool sweep; new rows land in their assigned file; start-up and runtime lane (CRT entry, initializers, imports/exports, SafeSEH, resources, relocations in fillers and dumps); RotWK as a second verification target over the BFME2 tree after step 8. | publisher, full links, boot and crash triage | links without `/FORCE` or stubs at a non-retail base; automated runs reach the menu, a skirmish and save/load, then match retail's game-logic CRCs with a perturbed run caught as the negative control; `Code/` holds retail's TUs with every code row approved in its TU (`tools/progress.py` SOURCE FILES, TU-APPROVED) | pilot 2–7; completion weeks |

## What changes for agents now

Until the step-3 checks land: edit `tools/build.py`, `.githooks/`, baselines and whitelists only to
fix verifier bugs; add no new escape hatches (rule 4 list); BFME1 pauses bulk renames. Keep
matching as usual — rows the new checks flag will be served as a queue.

## Decisions needed from maintainers

1. Publisher with a pinned checker and push restriction on master (steps 1–2).
2. Date for showing the new link-based series next to the current progress bars (step 5).
3. BFME1 pause on bulk renames and raw dump harvests (step 9).
4. A word cap for BFME2's AGENTS.md.

## Live rules in detail (moved from AGENTS.md, 2026-10)

AGENTS.md ("Hard rules") states each rule in one line. This is the detail.

### Debt leaves a register only by its own path

`tools/repair_queue.py` `verify-removed` and `verify-missing` judge every removed
key against staged inputs:

- `reverse/gate_baseline.txt`: delete the line with the fix
  (`repair_queue.py pass-test "<line>"` does it). The hook rebuilds the row's
  source and refuses if the row still fails its check. No trailer applies.
- `reverse/data_check_baseline.txt`, `reverse/code_identity_baseline.tsv`:
  `repair_queue.py retire data|identity SOURCE`, which deletes only the keys the
  owning tool no longer finds after a clean build. The hook re-judges them.
- `reverse/header_queue.tsv`: the row's `header_adopt_lane.py accept` command.
- A data, identity or header key whose source no longer exists: transfer the same
  key to the new source, cover every one of the old source's ledger rows in
  `reverse/deleted_rows.csv`, or, rarely, give a human explanation per key in a
  `Debt-Retired: <key> <source> <reason>` trailer (the full literal register line,
  or the class for a header row; at least 20 characters of reason). This trailer
  covers only that vanished-source case. It is no alternative to a verdict, and
  `Verifier-Change` never retires a key. `python3 tools/repair_queue.py retired`
  lists the committed trailers.

### Escape hatches

`tools/hatch_counters.py` counts selectany definitions, hand `/alternatename`,
`symbols.csv` pins, `object-symbol=` rows, address-named globals,
`class-gate: allow`, `present-unmatched` markers, `#pragma optimize`, `__emit`
lines and `.asm` `db` bytes in `reverse/hatch_baseline.tsv`, which is enforced
(`# mode: enforce`). Most hatches are judged per token (a pin or an alias row per
address): a file's count of a key may not rise. Growth passes only (a) as a move
that keeps the hatch total (a renamed file or a moved function;
`hatch_counters.py --update` writes it), or (b) as an admission a checking tool
wrote after its own verification: `tools/pin_admission.py --add`,
`tools/add_match.py --pin`, `tools/name_globals.py` (its kept, byte-verified
rewrites) and `tools/gen_small.py land` (generator pins that pass admission). An
`object-symbol=` row naming a compiler label (`$L<n>`, `_$E<n>`), such as a
`tools/gen_uw.py land` funclet row, is not a hatch. `/alternatename`,
`present-unmatched` and selectany are keyed by a spelling a rename changes: while
code identity is in shadow they too are judged per token, and once it is enforced
at HEAD and in the commit they are judged per file, so a same-count respelling is
noted, not refused.

Policy goes further than the hooks: prefer removing hatches and never add one by
hand. A hatch count may rise only through a verified admission by one of the
tools above, and only where that tool admits it. Running `hatch_counters.py
--allow` or `--admit` yourself to pass a hand-written hatch is hand-adding.

### Pins

A new `symbols.csv` pin must be an in-image code RVA and may not put a second real
name on an address that already has one (rename the owner). An ICF-folded
template instantiation is admitted only with `fold-proof=<ledger source>` in its
notes, when that unit compiles the name to retail's whole body there with every
owner row's relocations and the name has no address of its own, a gen-alias twin
included (`tools/pin_admission.py --add`); a later row or pin giving a
fold-pinned name another address is refused too. Pins are an additive candidate
list: the resolver keeps the first pinned address that reproduces retail, so a
pin naming the wrong function still byte-matches; hence the
`tools/pin_consistency.py` checks.

### Converged data addresses

Each address in `reverse/data_converged.csv` (TheGameLogic, TheAI,
TheWritableGlobalData, ...) has one global. Another symbol bound there
(`g_00DFE78C`, `extern AIView *TheAI`) links as a separate datum and fails
link_cycle data-back for every row at that address. Declare the real global
(`class AI; extern AI *TheAI;`) and cast to your view where you use it:
`((AIView *)TheAI)->m_field`. The list only grows (`tools/data_check.py
--converged`, after the byte gate).

### Shadow checks

Code identity (`tools/code_identity_gate.py`) runs in shadow on `origin/master`:
`reverse/code_identity_baseline.tsv` says `# mode: shadow`, findings print and the
commit passes. A flip to `# mode: enforce` is in progress; from the commit that
lands it, a finding outside the registers is refused, and the mode never returns
to shadow. Read the register's mode line rather than trusting this paragraph. The
other data checks (`tools/data_check.py` outside `--converged`),
`tools/tu_ownership.py`, `tools/invented_names.py` and link admission
(`tools/link_check.py --shadow`) also report without refusing.
`tools/publisher.py` only re-verifies pushed work afterwards.

### Verification runners

The nightly link cycle and measurement run on GitHub-hosted runners:
`.github/workflows/nightly-measure.yml` (`docs/nightly_actions.md`). Its secret-free
build jobs run the gate, `tools/link_cycle.py`, the boot image and
`tools/image_ownership.py`. Its publish job (`tools/nightly_measure.py --actions`)
re-validates, records and publishes the ownership row. The two-account local
setup (`docs/nightly_setup.md`) is superseded. `tools/audit/run_nightly.cmd`
runs only from the maintainer's scheduled task. Also maintainer-controlled: a direct or manual
`tools/link_cycle.py` run, `tools/boot_smoke.py` and the shadow publisher. Seats
need none of them; they use `python3 tools/link_check.py --fetch-index`,
`reverse/link_census_history.csv` and `repair_queue.py link`.

### Boot and smoke queues

Retail's own results, and what they do not yet show, are in `docs/automation.md`.

Served through `repair_queue.py repair` where their files exist; maintainer runs
write them. Each item's pass test decides who can close it:

- static relayout findings (`build/boot/static_queue.json`): the pass test,
  `tools/boot_relayout.py findings --overlay rva:RVA --only CHECK --no-write`, runs
  locally;
- game-smoke desyncs (`build/game/desync_queue.json`): the pass test links a
  one-row image (`tools/boot_image.py link --tag one ...`) and runs
  `tools/game_smoke.py determinism --image one --game-dir SANDBOX` against
  retail's record. A seat the maintainer has given a sandbox game directory and
  retail's record may run it locally;
- start-up crashes (`build/boot/boot_queue.json`): the pass test is a
  `tools/boot_smoke.py --overlay rva:RVA` run, which is maintainer-controlled.
  Repair the row and verify it with `./build.sh`, then record it as awaiting the
  maintainer's boot pass, in a handoff under `reverse/attempt_support/` or as a
  `re_log.py ... blocked "awaiting boot pass: ..."` entry. A desync item without a
  sandbox is recorded the same way, as awaiting a game-smoke pass.

`game_smoke.py bisect` needs a relayout image that `boot_smoke` measured,
retail's record and a game lock script that is not in this repository:
`python3 tools/game_smoke.py bisect --image TAG --game-dir SANDBOX --lock LOCK.py
[--record-json RECORD]`. The maintainer provisions SANDBOX and LOCK.py, so seats
do not run bisect.
