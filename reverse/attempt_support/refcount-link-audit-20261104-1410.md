# RefCount/rendering outgoing-link audit

Source batch `0b327ff4aba3dbb3ebef08301320101e76f7d21b`; 19 sources, 233 existing native
rows. Native prepare-current and new-variants checks pass. The dated
984a4cdc4d preview preserves19/19 source predictions and LINKED16206->16206;
it is not a fresh census or a full-image link.

Native broader batch-audit return code: 2.

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base a7d6d877db6f0b65e6827a0479c32093b5eb8d52; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Return2 means INCONCLUSIVE evidence, not a proven regression or a clean
whole-project result. Missing current objects are not silently replaced by
old census material. No census/real-link/game workflow is started here.
No runtime, memory/crash, FPS or multicore claim. See the source batch and
refcount-renderobj-prerequisite-20261104-1410.md for its separate held scope.
