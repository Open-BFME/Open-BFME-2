# Thai glyph GDI declarations from the Windows SDK

The default picker serves FontCharsClassStoreThaiGdiGlyph.cpp's local ABC,
GetTextExtentPointI and GetCharABCWidthsI definitions. The whole file and
its prior rasterizer/cleanup attempts are reviewed; the matched loop body
is left intact.

Remove the sweep include directory and the three local definitions. The
existing <windows.h> include now uses the explicit // platformsdk opt-in.
The real wingdi.h exposes the two glyph-index APIs only with
_WIN32_WINNT>=0x0500, so the source's compiler flags select that profile.
NO_STRICT preserves the existing opaque handle ABI already used by the
shared FontGlyphDCSelection helper in FontCharsClassLoadCharBitmap.cpp.
These are SDK configurations, with no fallback header or fabricated API.

The first SDK trial without that feature macro could not see the two APIs.
A strict-handle trial changed only the helper constructor's decorated
signature, while retaining its whole30-byte body and relocations. Reusing
the sibling's opaque-handle configuration preserves all five original code
COMDATs unchanged, including that constructor. Neither trial was applied.

Private verification covers every owned address:1323-byte rasterizer,
eight-byte cleanup and ten-byte EH handler. Normal ./build.sh and strict
preparation pass3/3 and all five named imports; the frozen check passes.
The strict input receipt proves real PlatformSDK windows.h and wingdi.h
with no sweep include or retry. The owning inventory scan finds zero
local copies, prototypes or failed analyses and retires this one queue
entry, leaving460 other files.

Own link_check reads LINKS,1333->1333 own-row bytes, against the published
20:08 index at b974574bd6. No code provider, consumer, source path, pin or
global binding changes. Three local definitions retire, with zero unique
byte gain. This scoped preview is not a new census or an executable image.
