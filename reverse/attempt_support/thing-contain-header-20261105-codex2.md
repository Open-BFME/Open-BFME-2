# Thing header adoption: contain and bone transforms, 2026-11-05

Base: `cf34120adbdc446e4967246579ee912291c9bce0`.

Seven units replace their private Thing declarations with the existing canonical
`Common/Thing/thing.h`. No shared header, source path, compiler flag, pin or
alternatename changes. `header_adopt_lane.py accept --class Thing` accepts the
whole seven-file cohort and retires seven Thing queue keys.

## Scope and layout

- `Common/Thing/ThingConvertBonePosToWorldPos.cpp`
- `GameLogic/Object/Contain/GarrisonContainOnRemoving.cpp`
- `GameLogic/Object/Contain/HordeContain/HordeTransportContainRva00477BA2.cpp`
- `GameLogic/Object/Contain/HordeContainIface20Slots.cpp`
- `GameLogic/Object/Contain/HordeContainRva0046CF21.cpp`
- `GameLogic/Object/Contain/HordeContainRva00473125.cpp`
- `GameLogic/Object/Contain/HordeContainRva00475F61.cpp`

All paths are under `Code/GameEngine/Source/`. The existing canonical Thing
base occupies 0x60 bytes. Derived Object padding starts there while retaining
the original accessed field offsets (including 0x74, 0x78, 0x10C and 0x304).
The template-field consumer casts the canonical template pointer to its existing
TU-specific view. Bone-transform helpers operate on canonical Matrix3D storage
with the original arithmetic order. The two template-access consumers use file-local inline helpers. Retaining the
old getter as an out-of-class definition was correctly rejected by the frozen
source gate; direct field substitution changed the parent EH placement in one
unit. The helpers preserve the original inlining shape without adding an
unrowed member definition.
These are source-layout reconciliations, validated against the retail bytes;
no donor layout or new runtime behavior is inferred.

## Verification

- [Byte verification](thing-contain-header-20261105-codex2/build.log): 24/24
  rows match across seven sources, including six existing funclet pins;
  two string literals, two empty references and three float literals verify.
- [Owning acceptance](thing-contain-header-20261105-codex2/accept.log): 7/7 pass.
- [Link preview](thing-contain-header-20261105-codex2/link-preview.log): 7/7
  clean; 4,794 -> 4,794 census bytes, index `f44cbcf5b0` from
  2026-11-05 15:19. This is a prediction, not a real-link or runtime result.
- `check_csv.py` and `git diff --check` pass. All seven post-edit
  `find_declared_unmatched.py` checks exit successfully.

## Link-wide provider audit

Original objects were saved before adoption. Comparing external definitions and
alternatenames against rebuilt objects finds three removed definitions and zero
removed aliases; every other external definition is retained. An all-object
scan inspected 26,379 cached `build/match` objects, checking undefined symbols,
weak defaults, alternatename sources/targets, /INCLUDE directives and import
spellings for each removed definition. [Detailed results](thing-contain-header-20261105-codex2/provider-audit.json).

- `Matrix3D::Transform_Vector`: 41 surviving providers, no references or weak,
  alias or /INCLUDE dependencies found.
- `Thing::getTemplate`: 40 surviving providers and seven referencing objects.
  All 40 providers have the original `8b4104c3` bytes and no relocations; no
  weak, alias or /INCLUDE dependencies found.
- `Matrix3D::bfme_mul_bp`: no surviving providers and no references or weak,
  alias or /INCLUDE dependencies found. It was a TU-only inline helper.

The audit covers the cached objects available to this checkout, not a new real
image. Matrix3D's queue keys are left untouched because its class claim is held
by another worker. No startup or game-run claim is made.
