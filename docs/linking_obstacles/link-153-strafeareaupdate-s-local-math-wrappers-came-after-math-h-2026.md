### LINK-153: StrafeAreaUpdate's local math wrappers came after `<math.h>` (2026-10-30)

`StrafeAreaUpdate_update.cpp` wraps `<math.h>` in `#define inline static
inline` to keep its float wrappers local. A header included earlier had
already pulled `<math.h>` in, so the include guard voided the wrapper. The
unit then emitted an external `?sin@@YAMM@Z` (17 B, calling `_sin`). That
copy differs from retail's intrinsic copy (`fld; fsin; ret`, which three /O2
units provide), and it was the unit's sole blocker. The
out-of-line copy was referenced only from `.debug$F`. Calling `sinf` instead
(the recipes.md lever) breaks the row: it reopens the banked case-0 operand
order. Fix: move the wrapper block ahead of the first include. Row 1/1 is
exact. The object loses only four COMDATs, which become static: `_sinf`,
`_sqrtf`, `?sin@@YAMM@Z` and `?sqrt@@YAMM@Z`. Nothing else is added or
changed, and the undefined externals are identical. Preview against index
`6fe1089c24`: LINKS, 0 -> 945 bytes. Census confirmation is pending.
