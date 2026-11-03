# Devastate canonical AsciiString provider review

**Verdict: no provider or inline-ownership blocker found for this bounded adoption.** Both added helpers are exact copies of already-rowed native operations, with the same symbolic relocations and COMDAT properties as a current verified-source owner object. Root still owns normal seven-row verification, frozen/header acceptance and the affected-provider/batch checks after applying.

The reviewed private `build/devastate-seed-ascii-namekey-proof-20261104/proof.json` reports seven exact rows and two exact EH graphs; every old ordinary provider and binding property remains identical. There are no removed definitions. The adoption uses registered `reference/shims/bfme2_ascii/ascii_string.h`, replacing the private StringBase facade with its existing four-byte AsciiString wrapper at member offset `0x8C`; it also includes the existing NameKeyGenerator header. This review does not infer additional class or destructor identity from those bytes.

| Added operation | Native owner | Callee | Candidate proof |
| --- | --- | --- | --- |
| `??0AsciiString@@QAE@PBD@Z` | `0x654A`, 18 bytes | StringBase const-char ctor `0x37BA0` | All bytes exact after resolving REL32 at +8 |
| `??1AsciiString@@QAE@XZ` | `0x48BA39`, 5 bytes | StringBase releaseBuffer `0x36410` | Exact tail jump after resolving REL32 at +1 |

Both are EXTERNAL `.text` COMDAT SELECT_ANY (selection 2), exactly matching the current continuing `Code/Libraries/Source/WWVegas/WWLib/ascii_string.cpp` object. Its source MD5, object MD5 and all three header digests are current; object SHA-256 is `505ce1da022a7ac545d91a9d40e717f3937219f79b377bf11a6a86b3784d42eb`. The actual candidate digests are constructor `8f8a65ffcd4c` and destructor `d08bf29c9c2b`. Native bytes and symbolic edge details are in `provider-proof.json`.

The sole added undefined name is `?releaseBuffer@?$StringBase@D@@AAEXXZ`. Its existing 133-byte row remains owned by `Code/Libraries/Source/WWVegas/WWLib/StringBaseWideReleaseBuffer.cpp`; that current object defines it and has matching source/object receipts plus both recorded header digests. No new pin, body owner or alias is needed.

## Selection and routes

The saved census index is commit `23b85ddde5`, 2026-11-03 18:36. It has 818 constructor copies, all with the candidate's retail digest; constructor's first copy and ledger owner are ascii_string.cpp at position 19. It has 2,274 destructor copies with two retail digests; the candidate matches the continuing owner at position 19. The first indexed destructor copy is WinMain at position 17. Its cached helper payload/properties match, but its current source receipt is stale, so it is **not** used as a current verified-source witness. The current ascii_string.cpp owner is the current witness for both helpers. Devastate's indexed position is 13,310, later than those established copies; adding these copies does not change first selection in that saved index. This is not a fresh full-image selection claim.

Whole-object routes are intentionally different. Weak and INCLUDE sets are unchanged; no undefined name disappears. Seven `/alternatename` directives arrive through the preexisting canonical header. Every route exactly matches the current ascii_string.cpp object's directives and existing earlier index entries (positions 6, 17 and 19); no new spelling or manual hatch was introduced in this source. These existing header routes plus the one releaseBuffer dependency explain `routes_identical=false`. Do not report route identity.

## Inline and frozen ownership

The constructor and destructor are already globally rowed in ascii_string.cpp. Their additional canonical in-class copies need no Devastate rows, ownership transfer, unmatched annotation or dead-strip annotation. `inline-policy.md` records the exact frozen-checker and canonical-header boundary.

The existing protected `DevastateSpecialPower::~DevastateSpecialPower()` present-unmatched marker remains unchanged, with its existing 25-byte provider and hatch. It is separate debt; this adoption does not recover it or justify an absent-from-retail marker. The normal frozen check still applies. Header queue retirement must use owning acceptance rather than this report.

All tracked/native reads stopped. No compilation, claim, network, tracked edit or publication was performed by this reviewer.
