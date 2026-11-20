# BFME II modernizer (1.06)

Smoother presentation for *The Battle for Middle-earth II* 1.06, from the
modern variant of the Open-BFME-2 decompilation:

- 120 FPS presentation; game logic keeps its original speed;
- smooth units, animations, projectiles, construction and selection circles;
- Hor+ widescreen and twice the zoom-out range;
- HUD and menus at their own proportions, the palantir and side command bar
  at the screen edges;
- every display mode in the options menu, including wide ones.

## Install

1. You need BFME II 1.06 with this `game.dat` (the BFME All In One Launcher's
   1.06 installs it):
   `SHA-256 f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
   Any other `game.dat` is left alone and the game runs unmodified.
2. Copy `dinput8.dll` and `bfme2-modern-106.blob` into the game folder, next to
   `game.dat`.
3. Start the game as usual.

`game.dat` is never modified. To uninstall, delete the two files.

## Settings

Set these as environment variables before starting the game:

| Variable | Effect |
| --- | --- |
| `BFME2_MODERN_FPS` | presentation rate, default 120; `0` follows the display; `legacy` turns it off |
| `BFME2_MODERN_HUD=stretch` | retail's stretched HUD |
| `BFME2_MODERN_HUD_EDGES=0` | keep the palantir and side bar in the centred HUD box |
| `BFME2_MODERN_HORPLUS=0` | retail's field of view on wide screens |
| `BFME2_MODERN_ZOOM=0` | retail's zoom-out limit |
| `BFME2_MODERN_TRACE=1` | write `modern_trace.csv` (pacing events) |
| `BFME2_MODERN_DISABLE=1` | do not load the modernizer |

Each start writes `bfme2-modern.log` in the game folder: which blob was used,
and why the modernizer stayed off if it did.

## Known limits

- Only BFME II 1.06. The 1.09 community patch and RotWK are not supported yet.
- Not tested online. Game logic is unchanged, but mixed games with unmodified
  players have not been played.
- A launcher that syncs the game folder (switching patch or mod) may remove the
  two files; copy them again afterwards.
- Health bars over hordes and arrow streaks still move at the logic rate.

Built by `.github/workflows/modernizer.yml` from the commit named in the
release; `SHA256SUMS` lists the files. Source: `tools/modern_blob.py` (the
blob) and `mods/modernizer/loader` (the DLL).
