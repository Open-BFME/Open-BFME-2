# ImageCollection destructor header adoption

Base: 0defd0d2cb, 2026-11-04. Replaced the destructor unit's private
ImageCollection and NameKeyGenerator declarations with their canonical headers.
Image.h supplies Image and the full canonical SubsystemInterface, replacing
ImageClass.h and the subsystem shim together to avoid duplicate definitions.
No header, flags, row identities, pins, hatches or source paths changed.

Verification: build.sh passes all five rows; find_declared_unmatched reports
all definitions matched. eh_verify reports the destructor's EH graph EXACT.
header_adopt_lane.py accept passes for ImageCollection and NameKeyGenerator
and retires their two queue rows through the owning workflow. Its link
preview uses the fetched 2026-11-04 02:25 index at 5a13f2cd61; this is local
acceptance, not a census gain or runtime result.

Consolidation investigation: the supported planner was run for
Code/GameEngine/Source/GameClient/System/. Image.cpp's four-donor dry run
accepted none. The seed still uses map<int, void *> where the canonical
collection uses map<unsigned, Image *>; the destructor's iterator cannot
compose with that seed. FindImage also needs canonical Image and collection
declarations and removal of its duplicate subsystem view. The two address-key
STL donors respectively lose byte verification and introduce a losing
_M_erase COMDAT under the seed environment. These reproduce the earlier
tu-merge attempt in re_attempts.log; neither donor was changed or moved.

Next prerequisite: reconcile Image.cpp with the canonical collection while
preserving its folded map-constructor call, then retry the dry run. This
change retires header debt only; it does not claim any source-file reduction.
