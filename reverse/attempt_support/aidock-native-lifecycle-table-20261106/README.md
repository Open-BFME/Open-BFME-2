# AIDockState lifecycle table restoration

Native table VA C11368 contains transfer3415F5, onEnter341695, onExit341723 and update341770 at slots3..6. Those four real methods already had verified rows and canonical State signatures in AIDockStateOnExit.cpp. The packed constructor and destructor views omitted their overrides, emitting pure/default base entries instead.

Both existing views now declare those four exact methods at their inherited slots. The destructor view also retains the constructor/transfer-proven byte at+24, bringing its declared data extent into agreement with the constructor. No executable function body changes, row move, alias, pin, header or compiler-flag change. Every existing code provider is unchanged; the removed unused State::onEnter header copy remains identically defined in the current packed constructor object.

Verification: normal40/40 rows across constructor/destructor/callback provider; three EXACT EH graphs; frozen checks clean; normal objects equal the private winners for both changed sources. Both emitted68B tables resolve slots3..6 to the four exact matched ledger owners and native pointer targets. Preview against faee62b0b2 retains3/3 LINKS and1639B.

This is a bounded lifecycle repair. Slot2 remains pure pending the name getter33565, held by another contributor during this pass. Its existing body remains untouched in ConstIntGetters4.cpp. rename.py --to-class explicitly refuses that free-function signature; no workaround or unclaimed body edit is made. The table remains incomplete until that independently owned getter is recovered. Other packed states retain the register's signature prerequisites; no unrelated state view is changed. Actual image selection, bridge retirement, runtime and census confirmation remain pending.
