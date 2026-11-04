# W3DScriptedModelDraw.cpp TU approval: blocked on missed F evidence (2026-11-04, claude-opus-5-5)

Served by `tools/next_work.py --claim` (TU approval, `noncontiguous`):
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDraw.cpp`,
90 proposed rows in 60 files. Pass test: `tu_skeleton.py --plan` shows them approved
in the map rebuilt from current inputs. Not passed; nothing edited.

## Target facts

- The proposed code rows (0x000B3A80..0x000C8914) come from N (the class-name
  convention) alone. They interleave throughout with rows approved for
  `Drawable/Draw/W3DModelDraw.cpp` (Z/S from Zero Hour, plus C/E) and, at
  0x000C6A4D..0x000C79AD, provisional `BfmePod248.cpp`.
- Retail game.dat (sha256 f008b587...) holds
  `C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Drawable\W3DScriptedModelDraw.cpp`
  at VA 0x00BC9C40 (file offset 0x7C9040). Five `.text` instructions take it as
  an imm32: `push` at 0xB3EA0, 0xB4A63, 0xBF6A7, 0xC4CD0 and `mov esi` at 0xC43BE.
  They sit in 0xB3E96, 0xB4A1C, 0xBEE25, 0xC4C73 and 0xC433A. All five are
  already listed in `tu-evidence-missed-file-xrefs-20261104.tsv`.
  `reverse/string_xrefs.tsv` lists none of them, so F never fires here.
- Retail's directory is `Drawable/`, not the served TU's `Drawable/Draw/`.

## Why a seat stops here

F reads only the Ghidra export. `docs/consolidation.md` ("FXParticleSystem: approved
units are single files, approval is the wall", "What approval needs") names the
maintainer routes:
- re-export `string_xrefs.tsv`; or
- let F take capstone-verified imm32 operands, then run `tu_map.py --validate`
  and the hold-out harness.

A seat must not hand-edit the generated input.

This region adds a conflict for that decision. Of the 67 code rows approved for
`Drawable/Draw/W3DModelDraw.cpp`, 17 (Z 9, C 4, S 2, E 2) lie between the first
and last of the five F references. If F extends the retail path across its own
references, it contradicts those Zero Hour-derived approvals. BFME 2 appears to
compile ZH's `W3DModelDraw` code inside `Drawable/W3DScriptedModelDraw.cpp`, but
that is an inference from layout, not a proven TU. The map must settle F against
Z/S here before any merge into this TU makes sense.

Claim released; the item stays in the queue for the maintainer's F change.
