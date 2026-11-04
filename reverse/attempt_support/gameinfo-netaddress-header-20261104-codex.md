# GameInfo network-address header adoption, 2026-11-04

Inspected revision: `cc03897485`.

Scope: `Code/GameEngine/Source/GameNetwork/GameInfo.cpp` and
`Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp`, claimed through
`class:BfmeNetAddress`.

Both units declared private eight-byte address records. The existing canonical
`GameNetwork/BfmeNetAddress.h` supplies the same unsigned dword and unsigned
word layout and the comparison declaration used by `GameSlot::isPlayer`.
The automatic adoption helper refused a token-wide field rename because the
distinct `GameSlotConnectInfo` also uses `m_ip`/`m_port`. Replacing only the
address declarations and changing only `slot->m_addr38`'s two field accesses
uses the canonical `ip`/`port` fields without changing the connection record.
No shared header, class layout, pin, alias or ledger identity changed.

Verification:

- `./build.sh` for both sources: 137/137 functions matched; 60 funclet pins,
  41 string literals, 14 empty-string references and 23 named imports verified.
- `find_declared_unmatched.py` passes for both edited sources.
- `header_adopt_lane.py accept --class BfmeNetAddress` passed both sources and
  retired exactly their two rows from `reverse/header_queue.tsv`.
- Ordinary current-object `link_check.py`, index/census 2026-11-04 20:47 at
  `f12552d0a7`: GameInfo LINKS 2,869 -> 2,869 bytes;
  GameSlotApparent LINKS 7,007 -> 7,007 bytes. Total 9,876 -> 9,876.
- `check_csv.py` passes; no function/data row changed.

The adjacent GameSlotConnectInfo adoption was also inspected under its class
claim. Its helper stopped before writing with
`vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input`.
That declaration and its queue row remain unchanged; its claim was released.
This result concerns the adoption helper's include scan, not a compiler or
byte-verification failure of the accepted address changes.

No census gain, real whole-image link or runtime verification is claimed.
