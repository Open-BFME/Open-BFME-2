# Player local-player storage projection

The matched `Player::isLocalPlayer` body at RVA 0x002A9D89 loads the local-player pointer at +0x10. The imported older PlayerList header used by Player.cpp places its donor field at +0x0C; including that getter would change native behavior. The standalone donor now forward-declares the actual PlayerList and casts its existing global to a narrow observed-storage view, removing the conflicting private class definition.

The private before/after probe verifies the 15-byte row and its sole ThePlayerList relocation unchanged. Its only other emitted code was an unrowed four-byte getter with debug-only incoming references. The provider audit records the selected current matching copy and remaining providers; this source was not selected first. No native getter identity, new byte coverage, whole-unit link improvement or census gain is claimed.

Final ordinary gates, strict compiler receipt and provider preview are recorded with this change. Player's broader header, ABI, provider and mixed-file consolidation prerequisites remain open; the running supported consolidation dry run predates this prerequisite edit.

On current base5d43d4fe40, ordinary gates and strict reusable preparation passed. The actual object reproduces the private trial, including the sole global relocation and native +0x10 access. Against indexd249ce458a (2026-10-31 18:11), the donor, GameClientDrawableTOC and GameLogicInit preview3/3LINKS, retaining36,832 bytes (15+8,416+28,401). GameLogicInit retains an unreferenced getPlayerType diagnostic; no repair is claimed there.

The refreshed audit resolves all26 indexed touching objects. Fifteen current retained providers emit the same four-byte getter, and all inspected raw incoming references are debug-only. Selection is under the saved index order: GameClientDrawableTOC remains first with a current identical getter, but its whole-object SHA differs from the index snapshot. Ten peer receipts are stale, and the saved index predates this base. Complete post-index consumer closure remains unverified; carry this provider cohort into the next scheduled census. No broad linking clearance or census gain is claimed.
