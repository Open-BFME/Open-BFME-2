# tu_skeleton compose: deferring a positional #undef (dropped), 2026-10-30

Seat: w3dview-seat. Outcome: four tooling rounds through sol-loop, then
dropped. `tools/tu_skeleton.py` keeps master's behaviour. Bundles r1 to r4
(`0a2c9bdce4`, `cf5f426910`, `3e1b4965fa`, `b8d716e9d3`) were not landed.

## Problem

`compose()` hoists every preprocessor line of every donor above all
declarations and bodies. A file that defines a macro, uses it, then
`#undef`s it composes with the `#undef` directly under the `#define`, above
every use. W3DView.cpp's `BFME_UNUSED_VIRTUALS_16` (a multi-line macro that
spells a vtable view's slots, then `#undef`) made cl reject the uses (C2061
`'slot000_'`), so the seed failed under every merged flag set and the top
queued TU took neither a merge nor a carve. Multi-line `#define`s were not
the cause: `chunks()` keeps continuations intact.

## Counts (text measurements, no compiler)

- 176 Code sources `#undef` or redefine a macro after code that uses it.
- 100 of them, composed alone, put an `#undef` above a use. The measure
  splits the composed text at its first blank line, so it may undercount.
- In the fleet merge map (673 TUs), 17 TUs had such a file as seed or
  verified donor, and 15 of those rejected it or failed the seed (W3DView,
  shown as a timeout there, is a further case).
- With the final fail-safe rules (current toolchain index, 222,404 names):
  85 of the 100 deferred alone. 39 sit in a queued TU's donor set, and 29
  of those 39 still deferred when composed with every donor of their TU.

## Findings by round (sol-loop)

- R1 S1: deferral checked only the owning file. The deferred `#undef` lets
  the macro reach every later donor (`#ifndef X`, an identifier `X`).
- R2 S2: unresolved and toolchain includes were skipped (fail-open). Fixed
  with ms_header_audit's toolchain-name index (read only, hoist without it).
- R2 S3: same-file directives and includes after the `#undef` were
  unchecked. Also added: hoist on a `/D` of the name.
- R3 S4: quoted-include lookup skipped the ancestor includers' directories.
- R3 S5: the compose flag set's `/I` directories were ignored. R4 answered
  S4/S5 by scanning a superset of candidates rather than cl's order.
- R4 S6: forced includes (`/FI`) were not scanned.
- R4 S7: `#pragma include_alias` and `#import` were ignored.
- R4 S8: the `INCLUDE` environment directories were not searched.
- R4 S9: the aggregate `_HEADERS` cache could return a stale result after
  a header changed.
- R4 S10: directory-listing errors became empty directories instead of
  uncertainty.

The pattern: every round found another input that decides what the
compiler sees. Proving that a macro reaches no other code means modelling
the whole include environment, and each model leaves a gap.

## Simpler alternative (not attempted)

Keep each macro's lifetime around its owning file's bodies: emit a file's
`#define` before that file's first use and its `#undef` after that file's
last use, in the composed text. Every other file then sees the macro
exactly as it did before. The cost is in `compose()`: bodies are emitted
interleaved in retail order across donors, so compose has to track
per-file preprocessor state (which positional macros are live at each
body) and emit `#define`/`#undef` pairs around runs of that file's bodies,
including re-defining after another file's body. No header scanning is
needed.

## Follow-up for W3DView.cpp

The W3DView merge (`bee389ac31`, 10 files, 19/19 rows) was composed with
the r1 tool, so the landed file has `#undef BFME_UNUSED_VIRTUALS_16` and
`#undef BFME_SHAKE_DATA` as its last lines. Master's `compose()` hoists them
above the uses again (checked at `e295fede42`), so the next W3DView merge
or split fails the seed with the same C2061. Deleting those two trailing
lines does not change what the TU compiles. Verify with `./build.sh` before
the next W3DView consolidation.
