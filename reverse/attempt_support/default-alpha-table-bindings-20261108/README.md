# Default-alpha copy uses existing class tables, 2026-11-08

The 97-byte inner copy constructor in
DefaultModuleTemplate01InlineCopyCtors.cpp now binds the existing
`??_7DefaultAlphaModuleInfo@FXParticleSystem@@6B@` and
`??_7Rva0055B5BF@@6BDefaultModuleHeadBase@@@` compiler tables instead of two
one-byte char stand-ins. The rowed constructors at 0x003A616F and 0x0055B5BF
independently establish their native addresses, RVA 0x0081BA60 and 0x0081D5E8:
the cached objects' named DIR32 sites read those exact table VAs in retail.
`provider-proof.json` records each site and the cached object hash. The ledger
already binds both spellings at each address; no new binding is introduced.

The private DefaultAlphaModuleInfo copy view and its redundant bfme_copy_from
provider are removed. The same AlphaKeys assignment now appears directly in
the matched constructor, preserving the complete 128-byte rep-movsd copy.
There are no added definitions. The only three removed external definitions
are the two chars and that helper. The index at eba83a23be (2026-11-08 14:08)
touches all three names only in this source, consistent with current source
searches. This index scope does not replace current-image consumer checking.

Normal verification: 1/1 code row (97 bytes), both unrelated data rows, the
frozen-file check and reference checks pass. There are no EH rows in this
source. Private verification is also 1/1 and LinkGuard is clean. Strict source
preparation passes; ordinary preview remains LINKS/97 authored bytes.

A bounded bridge replay contains this source, the two cached emitters and the
native slot owners. Strong-definition refusals fall from two to zero. The
four-slot alpha-info table is already correct in the cached emitter; the
head table still requires one five-slot bridge, unchanged before/after.
The attached reports retain these two tables' decisions and omit unrelated
name-discovery diagnostics. This is scoped cached-provider evidence, not a
full current-image replay or runtime confirmation.

The registered one-byte Rva003AEA42_v0b and Rva003AEA42_vsub data owners remain
in place, as do the four existing category-table aliases. Recover their full
containing class/tables before retiring them. No data row, source path, pin,
baseline, generated queue or compiler flag changes in this pass. Next real
link must confirm the old char refusals disappear; complete class recovery
and bridge retirement remain open under LINK-636/LINK-619.

Published as c2ca5f6f36 after one lost race. The successful second attempt
took30.1 seconds and reused the first attempt's source verification receipt.
Required byte/data/EH/scoped-DIR32 checks pass. Broader audit remains
INCONCLUSIVE: index eba83a23be versus outgoing base
4904abd4bd222cb47e06f9bbccd5f30303a5e693, affected
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry that
consumer into the next census/image verification; no broader link clearance.
