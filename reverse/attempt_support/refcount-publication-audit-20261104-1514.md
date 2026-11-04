# RefCount/rendering outgoing-link audit

Source batch `cf4613d102c9c78609a6d9986a9d5144fa2d2639`; 6 sources, 71 existing native
rows. Native prepare-current and new-variants checks pass. The dated
984a4cdc4d preview preserves6/6 source predictions and LINKED6585->6585;
it is not a fresh census or a full-image link.

Native broader batch-audit return code: 2.

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 535c1732ba305db90bd3b349eb680de435189d05; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Return2 means INCONCLUSIVE evidence, not a proven regression or a clean
whole-project result. Missing current objects are not silently replaced by
old census material. No census/real-link/game workflow is started here.
No runtime, memory/crash, FPS or multicore claim. See the source batch and
refcount-prerequisites-20261104-1514.md for its separate held scope.
