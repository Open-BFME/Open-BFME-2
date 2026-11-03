# MapCache duplicate: preserved prerequisite evidence

The downloaded real-link artifact for run41655923515, commit52ca4d5dfce5,
reports LNK2005 for MapCache::addMap: the ledger's native1080-byte owner in
MapCacheAddMap.cpp and the unrowed Zero Hour body in MapUtil.cpp. Its scoreboard
has782 unresolved,2 duplicates, no image and authoritative=false because13
omitted funclets lacked an EXACT parent at that older revision. This is dated
evidence, not a new current full link. The retained owner passes14 native/EH
rows with EXACT parent EH and the original MapUtil passes19 existing rows.

Removing only the obsolete body/marker loses six existing MapUtil emissions:
vector<ICoord2D>::_M_insert_overflow, getExtent, the AsciiString/Coord3D tree
constructor and base constructor, its _M_create_node and node allocator.
Five explicit standard C++ template instantiations restore the template rows
without dummy calls. The remaining getExtent uses an EAX argument under the
original internal/private compiler convention. Making it externally visible
emits a stack argument and fails the complete65-byte row. Neither existing
coverage nor a gate may be weakened to remove a duplicate.

All source trials are restored; the normal19-row MapUtil check passes again.
No ledger, pin, marker, hatch baseline, header or source path was changed.
Next prerequisite: preserve getExtent's independently proven private ABI and
its genuine caller context while withdrawing the obsolete MapCache body, or
rehome it only through current approved TU ownership. Simply deleting it,
adding a dummy caller or keeping a wrong selectable COMDAT is not a repair.
Trial artifacts are under ignored build/up-to-eighteen-each-20261103-1638/.
