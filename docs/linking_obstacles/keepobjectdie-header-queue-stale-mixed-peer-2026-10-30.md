### KeepObjectDie header queue: stale mixed peer (2026-10-30)

The current merged TU already uses canonical ObjectModule/DieModule and
Thing/ThingTemplate, with inherited m_object replacing the historical m_08
failure. Fresh normal/strict verification passes ten rows and both parent EH
graphs. Acceptance still refuses because its single-source preview retains
the old name-getter definition in mixed ModuleNameGetters3. That current peer
has no copy and passes 101 exact rows; ordinary paired preview is 2/2 LINKS.
Record this header-adoption false reject and keep both queue keys. Retry after
a supported current-index refresh or a separate verified peer-aware guard
change. No source or checker change and no debt/census gain.
[Evidence and remaining boundary](../../reverse/attempt_support/keepobject-header-queue-stale-peer-20261030/README.md).
