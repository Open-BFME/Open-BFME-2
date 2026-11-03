### LINK-164: Downloader allocator copies need proxy-level inline cleanup (2026-10-30)

The registry's fully specialized char allocator cannot accept another member
specialization (C2910) or a late imported member redeclaration (C2761). A local
specialization of the primary allocation proxy performs the existing null
check and throwing namespace free directly. It preserves all 21 registry rows,
six EH graphs, 45 retained external code definitions and actual relocation
destinations. Exactly three debug-only allocator/proxy/rebind definitions
disappear; no import, pin, row, alias, hatch or header changes. The selected
proxy and rebind providers remain unchanged; both existing proxy providers
are complete native 18-byte exact. With the separately checked URL builder,
strict four-source preparation passes 38 rows and eight EH graphs. The
`ccafe54d1d` preview retains 4/4 LINKS, 942 -> 3,717 authored bytes, including
registry 0 -> 1,907. Full affected-consumer selection/loss checks and census
confirmation remain pending; no official headline change is claimed.
[Registry and provider evidence](../../reverse/attempt_support/download-char-deallocate-link-20261030/registry.md).

The URL builder's separately verified repair preserves all nine rows and its
EH graph, with 42 retained external definitions and relocation destinations
unchanged. The same three removed definitions are debug-only; selected global
proxy/rebind providers remain unchanged. Its preview clears 868 authored bytes
in the four-source cohort, for 2,775 total predicted bytes across the pair.
[URL-builder evidence](../../reverse/attempt_support/download-char-deallocate-link-20261030/url.md).

Outgoing audit: INCONCLUSIVE because `ccafe54d1d` predates outgoing base
`0deec88cb3` and affected CreateAHeroManager lacks a current receipt. Carry
the full removed-provider and affected-consumer scope into the next scheduled
census; the verified four-source preview is not full-image loss clearance.
