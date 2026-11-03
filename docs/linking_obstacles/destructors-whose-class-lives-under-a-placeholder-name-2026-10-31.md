### Destructors whose class lives under a placeholder name (2026-10-31, Noro420, open)

Two units fail only on a destructor whose retail body is rowed under another
class name. Both names exist, so `rename.py class` cannot merge them; each
needs a code-identity class merge first. Recorded in `reverse/re_attempts.log`.
- `FXParticleSystem/T1Base005F3750Ctor.cpp` (176 B): unresolved
  `??1T1Base_005F3750@@UAE@XZ`. Ctor 0x0055C903 installs vtable 0x00C1D3F4;
  slot 0 `??_GRva003ABA36` (0x003AE8D5) calls `??1Rva003ABA36@@UAE@XZ` 0x003ABA36.
- `ScriptEngine/Scripts.cpp` (512 B): unresolved `??1OrCondition@@MAE@XZ`.
  `OrCondition::duplicate` 0x003B6D06 installs vtable 0x00C1F3F4; slot 0
  `??_GRva003B262E` (0x003B331E) calls `??1Rva003B262E@@MAE@XZ` 0x003B262E, the
  BFME 1 `OrCondition::~OrCondition` body (Scripts.cpp:1434). `rename.py class
  --basis canonical:bfme1` refuses: `bfme1_sweep` has no body candidate for it.
- `Common/BfmeConv901.cpp` (33 B): unresolved `??0Rva001320D0@@QAE@PAX@Z` and
  `??1BfmeThingJC@@UAE@XZ`. The base ctor is now rowed as
  `??0BfmeThingSJ@@QAE@H@Z` (0x001320D0), so respelling the base fixes the
  first. Ctor 0x002DB882 installs vtable 0x00803E48, whose slots are
  0x00131C40 (`bfmeGo1035G`, shared with the BfmeThingSJ table 0x007D25D8),
  0x002DB8BF (`MapPreviewTextureAssetFactory::PreLoad`), 0x00131CD3 and
  0x00132129. `BfmeThingJC` is therefore `MapPreviewTextureAssetFactory`, and
  retail has no separate `??1` for it. The open path is the sibling
  `TextureAssetGet.cpp` pattern (a non-virtual view plus an admitted
  vtable data row for 0x00803E48), or a class merge into
  `MapPreviewTextureAsset.cpp` once `tu_map` approves that TU (both rows are
  still `proposed`).
Census confirmation: not applicable (no repair yet).
