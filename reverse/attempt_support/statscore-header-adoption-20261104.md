# GameSpy stats-core header adoption

Inspected base: `b0cc08ec59`, 2026-11-04. Canonical header:
`Code/GameEngine/Include/GameNetwork/Rva00553E47StatsCore.h`.

## Applied and verified

- `GameNetwork/GameSpy/PeerDefs.cpp` replaces its private core declaration
  with the header. The two accesses to `m_maps04[0/1]` now use the header's
  corresponding `m_maps04_0/1` fields. Normal build: 136/136 rows exact,
  five data rows exact, string/import checks pass.
- `GameNetwork/GameSpy/Thread/PeerThreadPushStatsBfme.cpp` replaces its opaque
  core declaration with the header and enables the existing STLport include
  overlay via `// stlport`. Normal build: 8/8 rows exact, including EH funclets;
  string/import checks pass.
- `header_adopt_lane.py accept --class Rva00553E47StatsCore` passes both units
  together. The owning tool retired their two header-queue rows.
- Ordinary combined `link_check.py` against census index `5a13f2cd61`
  (2026-11-04 02:25) reports both LINKS: 7,255 and 666 bytes respectively,
  preserving 7,921/7,921 census-linked bytes. The two UnicodeString allocator
  diagnostics in PeerDefs are unreferenced and are not blockers. No census
  gain is claimed. No shared header, symbol, pin or function row changes.

## Remaining provider obstacle

`GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp` retains its private
core declaration and header-queue row. Automatic adoption fails its existing
271-byte destructor row `??1Rva00553E47StatsCore@@QAE@XZ`, RVA `0x00383D71`.
The original declaration lets the compiler generate that destructor implicitly;
the canonical header declares an out-of-line destructor.

A bounded trial replaced the private declaration with the header and supplied
an empty out-of-line destructor definition. All other directly compared rows
passed (305/306), but the destructor gained a six-byte `mov [esi], vftable`
store after saving `this`, before destroying the map members. Retail and the
original implicit destructor lack that store. Thus an empty explicit body is
not a byte-exact substitute. This is a code-generation difference, not evidence
for a different layout or a different original class name.

The trial was fully reverted. The restored normal build passes 306/306 direct
rows and three STLport constructor folds, three data rows, and string/float/
import checks. Next: resolve the canonical destructor declaration/emission
contract across its providers before retrying this unit; do not repeat the
empty explicit destructor trial or retire its queue row.
