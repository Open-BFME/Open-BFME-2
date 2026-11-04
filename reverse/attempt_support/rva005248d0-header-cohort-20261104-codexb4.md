# Rva005248D0 header adoption cohort

Inspected revision: `fc54a9c145`; 2026-11-04, codexb4, gpt-6.1-sol.
The default claimed picker selected 20 queued consumers of
`Code/GameEngine/Include/GameClient/Rva005248D0.h`.

All 20 sources passed `find_declared_unmatched.py`. A normal
`header_adopt_lane.py adopt --class Rva005248D0 --header
Code/GameEngine/Include/GameClient/Rva005248D0.h --apply` trial retained none:

* 16 sources stop on their `Rva005248D0::m_commandMaps` (or GameSorter's
  `maps`) member at +4: the header instead inherits AptCommandMapAdder,
  whose storage is `field00`. This includes AptOptionsConstructor,
  AptPlayerStatus, AptQuitMenuCallbacks, AptRowListCallbacks,
  AptRowListConstructor, AptScoreScreen, AptScoreScreenCallbacks,
  AptSkirmish, AptStrategicPlayerStatus, AptTimeLine,
  AptTributeRowConstructors, AptPalantirConstructor, AptPalantirUpdate,
  Rva005173F8Dtor, parseSpellIndex_Thunk and GameSorter.
* AptSaveLoad.cpp's proposed header-layout probe fails C1083. This is a
  probe failure, not evidence that the original unit fails to compile.
* AptSaveLoadRva00435DE7Dtor.cpp's opaque +4, 84-byte field has no single
  canonical field with the same extent.
* W3DAptComponentColorPicker.cpp's +0x10 AptExternHandlerAdder member
  encounters canonical Rva005241B0::holder10 storage.
* Rva005248D0Dtor.cpp reaches byte verification but its destructor fails.

Target facts: the matched constructor at RVA 0x002D2C34 and destructor at
0x005248D0 describe six non-polymorphic bases. Their existing private
declarations disagree on the third base's class identity: constructor
Rva00524415 versus destructor Rva00524436. The ledger owns the former's
constructor at 0x00524415 and the latter's destructor at 0x00524436; there
is no row for Rva00524415's destructor. The final base is AptTimerAdder in
the constructor/header but Rva00524349 in the destructor. Both destructor
names already have rows at 0x00524349. These are identity prerequisites,
not evidence permitting a new alias, pin or donor name.

Next work: reconcile member-style consumers with the evidenced base model
and establish holder lifetime identities through the naming workflow;
then repeat byte and link acceptance. Diagnose the AptSaveLoad probe's
missing include separately. No header queue row was retired, no source
edit retained and no census or ownership gain claimed. An additional
unused-class scan of eight GUI cohort sources found no removable classes.
