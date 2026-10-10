# ScoreKeeper counter owner cleanup

Reviewed BFME1 575ba2b04743f190f069805fbdc59936123c45da `game/GameEngine/Source/Common/RTS/ScoreKeeperCounters.cpp` before this dedicated repair. Its merged real counter layout and map find protocol are applicable semantic leads; BFME2's existing layouts and actual providers are retained.

Target facts: existing addObjectLost at 0x39CF73 is 392 bytes, and addObjectsLost at 0x39D0FB is 117 bytes. Both whole bodies remain exact, including calls to the real unsigned/pointer `_M_find` at 0x357180 and ImageSubscriptMap at 0x2077D6. The 392-byte owner's Object+0x254 load is native field access, so its private public-method spelling is unnecessary. The old ZH addObjectLost definition is unmatched and duplicates this real owner; it has been removed. The two old ZH rows (146 bytes) remain exact.

The strict bounded preparation checked all 17 rows in these two homes and the two genuine map providers, then rechecked the final two changed homes (4/4 rows) with strict current receipts. Final files contain no failed comparator experiment and no 0x39CF1D reconstruction.

Measured LINK context is the witnessed 2026-10-10 11:55 census at d68a97b48f. The authoritative census-only control shows two counter-home blockers: duplicate addObjectLost and wrong less<unsigned> copy. After this change only the comparator remains. An older ranking also listed getBodyModule; that is not a current blocker and is not credited as removed. The ZH home retains its other constructor, template, and selected-provider debt. This is +0 recovered C++ bytes and +0 LINK bytes; it removes one present-unmatched body, its actual strong duplicate conflict, and one unnecessary private method spelling without introducing blockers. Complete current-universe LINK is not claimed.

Remaining comparator: retail 0x758C50 is19 bytes, `8b4424048b088b5424083b0a1bc0f7d8c20800`; the local copy is19 bytes, `8b4424048b008b4c24083b011bc0f7d8c20800`, with different register allocation. Declaration-only _M_find forms hit MSVC7.1 errors/ICE. Faithful member/class forceinline and extern-template forms kept the wrong comparator; three equivalent comparison expressions did not repair it. These isolated trials were reverted. No imported symbol, alias, emission anchor, compiler override or new private STL facade was added.

Current 86-byte destroyed-count reconstruction is separately banked; its ESI/EDI and push-scheduling wall remains unchanged. This cleanup does not claim that body or a completed counter file.
