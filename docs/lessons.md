# Codegen recipes

Start here, then read Open-BFME-1's `docs/lessons.md` and `docs/lessons-archive.md`
(in `reference/open-bfme-1/`): the toolchain is identical, so every codegen
recipe there — vptr scheduling, `throw()` unwind states, `novtable`, the
EH-transposition wall, the private static-call convention — applies to this
binary unchanged. Add BFME 2-specific findings HERE, in the same curated,
edit-in-place style: a recipe earns its place by being re-verified against
game.dat, and the war story goes in the commit message.

## game.dat is not incrementally linked

Unlike BFME 1's exe (25.7% inter-function 0xCC padding, ILT thunks
everywhere), game.dat has 1.5% padding and direct calls. BFME 1 lessons about
incremental-link thunk ambiguity mostly do not apply; a REL32 usually reaches
the real body directly.
