### LINK-344: browser TU affected-consumer confirmation

Status: Blocked. Updated: 2026-11-04; inspected revision: 76a8594dfc.
DX8WebBrowser initialization is absorbed into its approved TU: 18/18 rows and four EH graphs exact; local preview preserves 1,330 bytes. Wider provider/consumer closure needs a current census and the Common/0CreateAHeroManager21FE49.cpp consumer receipt. Carry the destination and its consumers into the next scheduled census; no census gain or global clearance is claimed. [Evidence](../../reverse/attempt_support/dx8webbrowser-tu-merge-20261104.md).

Update 2026-11-18 (base `c2c4f23b03`): the census of 2026-11-18 10:35 (`147fd3e52b`) held
dx8webbrowser.cpp (1,330 B) out on its own copy of
`?CreateInstance@?$_com_ptr_t@V?$_com_IIID@UIFEBrowserEngine2@@...@@QAEJABU_GUID@@PAUIUnknown@@K@Z`
("unproven and differs from the kept copy"). The two emitters' 141 bytes were equal; one relocation
was not. dx8webbrowser.cpp's explicit specialization names the IUnknown GUID `IID_IUnknown`, the
object the data ledger owns at 0x007D4E4C, while WebBrowserComCreateInstance.cpp, which rows
0x00176F10, instantiated comip.h's body, whose `__uuidof(IUnknown)` binds the compiler's
`__GUID_00000000_0000_0000_c000_000000000046` there. Declaring the member in dx8webbrowser.cpp and
calling the owner's copy is not open: retail expands the body once into `Initialize` (the row fails
with two calls). Completed: the row's unit takes the same specialization text, so both objects emit
one body (sha1 7e826dc9e3, six relocations, `_IID_IUnknown` at +34) and no unit binds the `__GUID_`
name at 0x007D4E4C any more. An inline specialization nothing uses is not emitted, so the row's unit
carries a marked stand-in caller, `bfmeAnchorBrowserCreateInstance`. `./build.sh` of both: 19/19
exact. `link_check.py` (index `147fd3e52b`): both LINK, 141 -> 1,471 bytes.
Remaining / next check: 0x00176F10 lies inside dx8webbrowser.cpp's span (0x00176FA0 onward is
approved for it) but `tu_map.csv` gives the row no unit. Once it has one, the row goes home, and
WebBrowserComCreateInstance.cpp's copy and its stand-in caller go with it. The consumer-confirmation
blocker above is unchanged.
