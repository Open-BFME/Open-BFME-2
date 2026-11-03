### LINK-176: GlobalWeatherSystem destructors folded out of `Rva00318637`; shared-blocker names traced (2026-11-01, seat halilkkaya-lk14)

Status: Partly repaired (preview). Base `bd66989490`; index 2026-11-01 19:53 (`93c5672365`).
Follows LINK-175's GlobalWeatherSystem row.

- `rename.py class --fold` now accepts a multiple-inheritance class's deleting-destructor
  adjustor thunk on the class's own secondary table, and reads the installing rows' live DIR32
  bindings when `data_ledger.csv` lags (`396c918ce6`). Applied: `Rva00318637` folds into
  `GlobalWeatherSystem` (retail vftable 0x00C0C734; `??_E...@@WM@` thunk 0x00318613 is slot 0
  of 0x00C0C724, installed at +0xC by dtor 0x00318637 and ctor 0x00318588).
- The fold alone made `Rva00318637Dtor.cpp` lose `??_7GlobalWeatherSystem@@6BSubsystemInterface@@@`
  (its canonical `SubsystemInterface.h` view declared only the dtor: a 4-byte table against the
  ctor unit's 14 slots). `/DBFME_SUBSYSTEM_SLOTS` gives it the header's retail slot list; both
  units now emit the same 56-byte table. link_check: `Rva00318637Dtor.cpp` LINKS 146 -> 146;
  `GlobalWeatherSystemCtorDeferred.cpp` keeps one blocker, `??1WeatherData@@QAE@XZ`.
- `??1WeatherData@@QAE@XZ`: the ctor's `eh vector constructor iterator` passes 0x0010F149 as
  the element destructor; the unit now defines `WeatherData::~WeatherData()` (release of the
  counted sound pointer) and rows it as a fold-proof ICF twin of
  `??1BfmeStringTailRecord156@@QAE@XZ` (`add_match --icf-owner`, 12/12 bytes and relocation).
  link_check: `GlobalWeatherSystemCtorDeferred.cpp` 0 -> 155 B LINKS; `GlobalWeatherSystem.cpp`
  (303), `CreateAHeroParseBlingBinder.cpp` (419), `Rva007ABBF6BlockParseInits.cpp` (2,728) and
  `SubsystemInterface.cpp` (22,023) keep linking. Census confirmation: pending.
