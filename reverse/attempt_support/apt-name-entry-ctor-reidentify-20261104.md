# AptValueNameEntry: 0x006CBCB0 re-identified as an Apt value constructor (2026-11-04, claudeb2)

Target facts (retail):
- 0x006CBCB0 (32 B) forwards both arguments to the two-argument Apt value
  constructor 0x006DCD20 and stores vtable VA 0x00CE8BA0 (RVA 0x008E8BA0,
  `reverse/data_ledger.csv` row of 60 B).
- 0x006D6300 (`Rva006D6300TypedValueCtors.cpp`) installs that same table, so
  both constructors probably build one class. No direct caller of 0x006CBCB0.

Change:
- The Zero Hour LaserUpdate port (constructor, destructor, crc, loadPostProcess,
  RvaLaserAnchor and the ZH include block with `#define DrawableModule
  Rva006DCD20`) was replaced by `Rva006CBCB0Value(int, unsigned int) :
  BfmeAptValue006DCD20(type, arg)` using the TU's existing view of the
  canonical base. Row renamed in place from
  `??0ClientUpdateModule@@QAE@PAVThing@@PBVModuleData@@@Z` to
  `??0Rva006CBCB0Value@@QAE@HI@Z` (precedent bfcfa8f3c7).
- Removed alternatename `?loadPostProcess@Rva006DCD20@@MAEXXZ`: the census index
  (2026-11-04 13:15, f6d845ecd4) lists its only referrer as
  `??_7ClientUpdateModule@@6B@`, emitted by this object alone, which no longer
  exists. Three present-unmatched markers (LaserUpdate::crc,
  LaserUpdate::loadPostProcess, RvaLaserAnchor) left with the code.
- Funclet rows uw_007a8038/uw_007a8030 relabelled to the object's current
  `$L4979`/`$L4978` (build already verified them through parent EH data).

Why a TU-unique name: naming the class `Rva006D6300Value` made this object emit
a three-slot `??_7Rva006D6300Value@@6B@` (AddRef, Release, `??_E`) that differs
from TypedValueCtors' one-slot copy (digest e35de392477f). This object precedes
TypedValueCtors in link order, so its copy would win and break the linked unit.
Sharing the name needs one shared view of the fifteen-slot table first.

Verification: `./build.sh` 11/11 matched; `link_check.py`: AptValueNameEntry
LINKS 0 -> 410 B (was: does not link, three Rva006DCD20 unresolveds plus two
LaserUpdate COMDAT conflicts); Rva006D6300TypedValueCtors LINKS 50 -> 50 B;
data_check 0 findings; check_csv OK. Prediction only; no census credit claimed.

Kept: the `??_H` anchor (`#pragma optimize("gsy")` block). Without it the
object still emits `??_H` (and `??_M`) in a shape link_check cannot judge.
