# NetGameCommandMsg header adoption, 2026-11-04 (codex3)

Inspected revision: `32e66a3660ef`; published census/index:
`8661f15284`, 2026-11-03 20:03. These are ordinary preview results,
not a new census or real-link measurement.

## Applied scope

Three sources now include the canonical NetGameCommandMsg header:

- Common/NetGameCommandMsg_constructGameMessage.cpp: 3 matched rows.
- GameNetwork/Connection.cpp: 21 matched rows.
- GameNetwork/ConnectionManager_sendLocalGameMessage.cpp: 1 matched row.

The latter two also explicitly include NetCommandMsg.h. No shared header,
compiler directive, pin, alias, ledger identity or source path changes.
The existing link-wide Connection alias remains intact.

The private explicit-vfptr views can be replaced directly by the real
polymorphic base. constructGameMessage uses inherited m_playerID at +0x0C,
m_type at +0x24 and m_argList at +0x28. Its existing constructor view still
takes void*, so the canonical integer message type is cast at that boundary;
the forward-declared argument list is cast to the existing local node view.
No unrelated ArgNode::m_type token is renamed.

`header_adopt_lane.py accept` passes for NetGameCommandMsg in all three
sources and for NetCommandMsg in Connection and sendLocalGameMessage.
Only that tool removes the five queue rows.

## Verification

`./build.sh` on the three retained sources plus the restored destructor:
27/27 rows exact across four sources, including seven renumbered funclet
pins resolved through their parents. Literal, float and import checks pass.
`find_declared_unmatched.py` passes for the three retained sources.

Combined ordinary `link_check.py` preview:

```text
NetGameCommandMsg_constructGameMessage.cpp: LINKS 443 -> 443 bytes
Connection.cpp: LINKS 1,644 -> 1,644 bytes
ConnectionManager_sendLocalGameMessage.cpp: LINKS 133 -> 133 bytes
3 of 3 link cleanly; LINKED 2,220 -> 2,220 bytes
```

## Restored trials and prerequisites

The supported six-source adoption trial also finds existing failures in
NetCommandMsgCtor.cpp (NetWrapperCommandMsg destructor), NetPacket.cpp
(the aggregate m_gameFields view has no single canonical field), and
NetGameCommandMsgDtor.cpp (argument node pointer type). No edits remain in
those sources and their queue rows remain.

A manual destructor trial replaced both private message classes with
NetGameCommandMsg.h, retained `inline NetCommandMsg::~NetCommandMsg() {}`,
and cast the canonical GameMessageArgument list to the existing local
NetGameCommandMsgArg view for next-link access/deletion. Both rows (91 B)
byte-match, but acceptance correctly refuses the ordinary preview:

```text
NetGameCommandMsgDtor.cpp: does not link; LINKED 91 -> 0 bytes
comdat ??_7MemoryPoolObject@@6B@: differs from first copy in link order
comdat ??_7NetGameCommandMsg@@6B@: differs from first copy in link order
```

The canonical derived class declares getContentsAsAsciiString, while the
constructor donor's private derived view only overrides vslot08; base
inheritance also introduces MemoryPoolObject emission. These are source
observations, not a completed selected-provider audit. Next inspect the
first-provider vtables and reconcile their declarations/emission together
before repeating the destructor adoption. The trial is restored and its
original two rows reverify. The blocked verdict is recorded with re_log.py.

The carried outgoing source-path merges retain their existing combined
path/debt/consumer audit in `aistructurestats-tu-20261104-codex3.md`. This commit adds no path changes or consumers
of those absorbed files; no extra merge or debt retirement is claimed.
