### MapCache duplicate prerequisite 20261103-1638

The real-link artifact41655923515 reports a duplicate addMap. Removing the old
MapUtil body also drops six existing rowed emissions; five explicit template
instantiations restore five, but getExtent requires its private EAX argument
context. All trials were restored and the native checks pass. The duplicate
remains open; no linker or runtime gain is claimed.
[Retained evidence](../../reverse/attempt_support/mapcache-duplicate-20261103-1638.md).
