# Method-only canonical header false rejection

The existing Rva001F3852ByteOneSetter header intentionally declares only
void enable(). Its fresh complete compiler record is size1, nonpolymorphic,
with enable as its sole method and no fields, bases or statics. The older
contract JSON still describes a padded view and is not proof of this header.

The provider's native8B body at1F3852 is byte[this+1A3]=1;ret. A prepared
canonical-header candidate with that byte store passes all49 provider rows.
The normal adoption preparer nevertheless refused: its field-name mapping
probe requires at least one canonical field. Both rendering consumers already
include this header and need no source change.

The source batch was restored before the separate tooling correction. The
correction admits only a plain declaration-only method view, independently
proved by the actual header and complete compiler record. Missing, forward,
partial, inherited, static, virtual, attributed or data-bearing declarations
remain refused. Other stripped classes still require their field mappings.
Class/include/macro checks and full-source compilation/native byte verification
remain mandatory. An old m_enabled access must still fail and restore its unit.

Regressions cover the positive case, lost char fields/bases, incomplete records,
parser diagnostics, class attributes, mixed stripped classes, macro shadowing
and full-source gate failure/restoration. The two existing Windows fixture
failures (newline and separator expectations) reproduced on unchanged HEAD;
their fixture assertions were made portable without changing tool behavior.

The source adoption is a separate follow-up after the tooling commit. No body,
header or ledger recovery is claimed by this evidence record alone.
