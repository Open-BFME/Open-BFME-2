### LINK-136: GameSpy colour array was split into scalar data owners

Status: Open; ownership repair and full gate verified, census pending.
Updated: 2026-10-29; inspected upstream revision d701d875b.
Evidence / affected units: retail GameSpyColor at VA 0x00DB9198, 29
entries / 116 bytes; field table 0x00BE0428 has 29 names and a null
terminator. The two former scalar owners at 0x00DB9198 and 0x00DB91A0
split that array and overrode its canonical name in data checks.
Completed: Chat.cpp and PeerDefs.h now reproduce the complete retail table;
the two duplicate scalar definitions are removed and the combo-box reader
uses GameSpyColor[2]. The data-retirement tool clears the obsolete
AptOnlineCustomMatchCallbacks.cpp key after its new GameSpyColor finding is
resolved. Scoped builds retain 140 exact function rows; the array and all
field-table tokens, offsets and parser bindings verify against retail.
Remaining / next check: carry the changed owner, removed providers and colour
readers into the normal census.
Clearance: complete table and scoped data checks pass; full gate verifies
98,943 function rows and 2,230 data rows with every check green.
The outgoing audit at base 91a3a60aa remains INCONCLUSIVE: index d92e7e6635
predates the base and 50 source objects lack current census receipts; first
is AptOnlineCustomMatch_PopulateLobbyComboBox.cpp.
Census confirmation: not claimed.
[Evidence and provenance](../../reverse/attempt_support/gamespy-color-table-20261029.md).
