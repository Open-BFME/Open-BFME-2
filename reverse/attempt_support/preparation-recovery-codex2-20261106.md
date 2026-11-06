# Preparation recovery, codex2, 2026-11-06

Recovered the eight commits preserved at
`refs/runner/preparation/1793922544374214409` (`fdc8fe52c774`).
The preparation record named no stash. The stopped rebase completed without
skipping any commit. Upstream `c181d855ce` had already adopted canonical
AIUpdate.h in HeroModeSpecialAbilityUpdate, Rva00495801 and
TeleportToCasterSpecialPower; retain its complete AIUpdateInterface types and
native calls, rather than reintroducing the older opaque subobject casts.
The pending AIStructureCreepTactic adoption and its queue retirement survive.

The first `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` refused only
the BodyModule retirement for OldSchoolHelpBoxContentSource.cpp:
`link_check predicts a loss of census-linked bytes`.
The ordinary preview (index `f44cbcf5b0`, census 2026-11-05 15:19) reports
3,289 -> 0 linked bytes and unresolved
`?TheEmptyString@UnicodeString@@2V1@B`. Both the attempted canonical-interface
source and the unchanged upstream source produce exactly this result.
This is a current preview prerequisite, not evidence that this adoption caused
the unresolved symbol. Restore its exact BodyModule queue row; retry acceptance only after the
UnicodeString binding is resolved. A trial restoration of upstream source
was rejected by pre-commit as a new private BodyModule copy, so retain the
canonical caller source. It adds no new unresolved name compared with upstream.
The original attempted adoption remains in the retained backup ref and
`a98b90b006`; its prior evidence is not a current acceptance receipt.

`./build.sh Code/GameEngine/Source/GameClient/GUI/GUICallbacks/OldSchoolHelpBoxContentSource.cpp`
passes 33/33 rows, 31 funclet bindings, 26 nonempty and one empty-string reference
for both caller versions (the header-debt hook built the canonical version).
`find_declared_unmatched.py` passes before and after restoration.
During the rejected restoration trial, searched every `.obj` under
`build/` for `?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ` and parsed
all 308 hits: 307 other definitions, one undefined external, zero weak symbols,
zero parse errors. The retained canonical source withdraws no further provider.
No source pragma or explicit alias changes. Raw local checks are in
`build/recovery-push-dry-run.log`, `build/recovery-oldschool-link.log`,
`build/recovery-oldschool-restored-build.log`,
`build/recovery-oldschool-restored-link.log`,
`build/recovery-oldschool-retained-build.log`, and
`build/recovery-oldschool-interface-accessor-audit.json`.

No real image, census improvement, or runtime result is claimed.
