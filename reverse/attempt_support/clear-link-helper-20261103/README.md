# Clear unit: current link and helper boundary

2026-11-03, based on 3e58c8da87. Source: Code/Libraries/Source/WWVegas/WWLib/Rva0020EE29Clear.cpp, 15 matched bodies / 938 own bytes. Current strict preparation and normal build pass all fifteen rows. Preview against index984a4cdc4d remains U2/C1, zero linked bytes; this is not a new census or a runtime pass.

The picker retains the older nineteen-unresolved diagnosis. LINK-093's Nov2 repairs already reduced it to two: the free stdcall lookup219B9E and Rva0021BDAccess lookup21BD22. Both arise from the31-byte Rva0021BEC1 wrapper, which actually forwards incoming ECX to the existing private const CreateAHeroClass lookup and uses the returned subclass as receiver of the const int lookup. Scope/signature correction needs canonical evidence under docs/naming.md; no guessed member name, alias, receiver trick, row or pin change is retained.

The remaining beacon hash-table COMDAT has a concrete visibility cause. Its current60-byte copy calls vector<void*>::size() const and const operator[], whereas the kept CreateBeaconObject copy equals retail's47 bytes at2888D4 with zero relocations. hash-find-conflict.json preserves both provider names and bytes. An ordinary explicit member-template specialization compiles successfully, unlike earlier declaration-only suppression trials. It accesses the established real three-pointer bucket storage, retains integer hashing/equality/node traversal, and preserves all fifteen parent-file rows, but emits46 bytes rather than retail47. G7 and four equivalent storage-expression variants reproduce the same register-hoisting mismatch. This private raw-storage view is an experiment, not recovered original source or a complete container identity claim. The native address already has real matched C++ in Armor.cpp, so check_csv correctly prohibits an address-level attempt stash for this source-local conflicting copy. No stash is retained. The experiment below and byte results are handoff evidence only and must never be copied into Code without closing the helper mismatch and provider checks. No private object touched build/match.

The queued LivingWorldRegionManager header adoption also still refuses: m_08 belongs to another unrelated class in this source, so its token-wide field mapping is unsafe. No canonical header was edited and no queue entry retired. A future scoped adoption must preserve the independent receiver views and their layout.

Retained cleanup corrects the stale unmatched annotation for2115D0, whose28-byte hidden-result string construction already lives in GameClient/System/Rva002115D0String.cpp. find_declared_unmatched reports all definitions matched before/after. The owning hatch_counters --update scanner removes this occurrence and twelve other stale occurrences already absent from HEAD sources (eight address-global occurrences, one alternate-name occurrence and three other unmatched occurrences); total13. It adds no allowances, and normal staged/outgoing hatch gates recheck the shrink. These are register cleanup, not new linked bytes.

The outgoing batch audit's standing inconclusive affected-consumer receipt prerequisite remains Common/0CreateAHeroManager21FE49.cpp. Carry it and these remaining identity/provider cases into the next scheduled census. No full link closure is claimed.

## Failed local helper experiment (evidence only)

```cpp
namespace _STL {
template <> template <>
_Hashtable_node<pair<const int, Rva003FD14D *> > *
hashtable<pair<const int, Rva003FD14D *>, int, hash<int>,
          _Select1st<pair<const int, Rva003FD14D *> >, equal_to<int>,
          allocator<pair<const int, Rva003FD14D *> > >::_M_find<int>(const int &key) const
{
    void **const *storage = reinterpret_cast<void **const *>(&_M_buckets);
    size_type bucket = _M_hash(key) % size_type(storage[1] - storage[0]);
    _Node *node;
    for (node = static_cast<_Node *>(storage[0][bucket]);
         node && !_M_equals(_M_get_key(node->_M_val), key);
         node = node->_M_next) {}
    return node;
}
}
```
