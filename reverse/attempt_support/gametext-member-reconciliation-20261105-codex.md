# GameTextManager donor reconciliation

Base: `05fbaef1d02d3d58454585285ae160cac29781c0`, 2026-11-05.

The supported planner (`name_lane.py consolidate --under
Code/GameEngine/Source/GameClient/`) was reviewed. Its grouping is a lead;
`tu_skeleton.py --plan` rebuilt the stale map in memory and approved the
GameTextManager donor for GameText.cpp. Mixed sources remain outside this pass.
Neither the map nor protected debt registers were edited.

The initial supported merge dry run refused GameTextManager.cpp with C2065
for `m_vec34`, `m_ptr2c` and `m_ptr30`: the seed declares these fields as
`m_asciiStringVec`, `m_textTable` and `m_mapTable`. The donor now uses the seed's
names and GameTextTable pointer types. Prefix enumeration still casts those
pointers to the existing Rva002E674B view; no recovered name is claimed for
that helper. The independent donor passes `./build.sh` (8/8 rows, including
its destructor, deleting destructor, base destructor, EH handler and three unwind rows) and
`find_declared_unmatched.py`.

The new merge dry run compiles but reports `bytes`. Read-only comparison of
its existing trial objects `ca9c5a41058764af.obj` and
`0cae7d0a434367ce.obj` against the two sources' ledger rows isolates two misses:

- `??1Rva002E66F2Mid@@UAE@XZ` is absent. The seed's manager derives from
  GameTextInterface, so its unwind path names that interface's destructor.
- `$L5334` at 0x00778D49 consequently cannot resolve the expected destructor
  callee. The matched parent is `??1GameTextManager@@UAE@XZ`, 0x002E66F2.

All other rows from those two sources compare exactly in those trial objects.
No merge was applied and no source-file or linking gain is claimed. This
confirms the prerequisite recorded in `re_attempts.log` by
`halilkkaya-cons-o9` and `halilkkaya-tool-o4`: reconcile the destructor identity
at 0x002E55D8 through the naming workflow before retrying composition. The
existing agreement is `nl-99bc35368af6` for Rva002E55D8 -> GameTextInterface;
its blocked application is not authorization to hand-rename the ICF row.

There are no path moves in this change. The donor has no data, identity, header
or Microsoft-header queue keys; GameText.cpp's existing File,
GameTextInterface and InGameUI header debts remain. No aliases or hatches were
removed. Provider/consumer names in the donor's rowed bodies are retained.
