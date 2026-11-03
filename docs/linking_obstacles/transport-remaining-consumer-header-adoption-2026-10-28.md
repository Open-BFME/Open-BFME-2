### Transport remaining consumer header adoption (2026-10-28)

Status: header adoption retained; queue retirement pending. Upstream now exposes
TransportMessage and the receive ring directly; the relay uses that canonical
view. The two header queue entries are retained because the fleet push hook
could not obtain usable per-unit link verdicts. A refreshed local census index
`840db2d676` reports LINKS for both consumers; the earlier byte verification
matched 490 rows across the 37 sources affected by the header, with 81 EXACT
EH rows. Re-run the header adoption lane when the publisher has a usable index,
and carry the consumers into the next census. The separate Transport
composition obstacles remain open.
