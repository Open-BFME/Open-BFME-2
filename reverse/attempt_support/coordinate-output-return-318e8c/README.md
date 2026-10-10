# Coordinate output return contract at 00318E8C

The complete 18-byte retail body copies the float word at receiver+20 and raw word at receiver+24 into the one stack-supplied 8-byte output buffer, then returns that buffer in EAX and pops its pointer. Its bytes are `d941208b442404d9188b4924894804c20400`; the body has no relocations.

The existing address-owned C++ declaration returned void. Independent retail caller 005666C5, at call site 005667A6, immediately moves EAX to ECX and reads both output words. The void source contract therefore omitted an observed result; incidental register preservation in its byte-exact compilation is not sufficient caller ABI evidence. Native 0031A372 also calls the provider at 0031A51E and 0031A542 with an 8-byte stack output buffer.

This commit withdraws only that obsolete void-return claim and its sole source definition, as a separate reviewable retirement. tools/add_match.py requires a real claim to be retracted separately; tools/ledger_io.py preserves every unrelated CSV record and line terminator. The next ordinary admission will use an explicitly physical address-owned output-pointer contract, not infer the original class or by-value signature. No pin at 00318E8C is added or renamed.

Bounded private source controls: an explicit output-pointer return reproduces every one of the 18 bytes without relocations; canonical Coord2D return uses a different frame/SSE shape; mixed aggregate construction emits 18 bytes but hoists the second-field load; POD return also differs. These controls do not establish original C++ signature identity. The full 548-byte campaign reconstruction remains nonmatching and is not landed here.

Ordinary add_match admission and the official Windows build.sh entry pass the complete 18-byte body with no unresolved targets, literals, floats, or imports. Scoped link_check proves LINKS18 ->18 with the current object, and find_declared_unmatched reports all definitions matched. This is an ABI-contract repair with zero net unique-byte or linking-byte gain; the nonmatching campaign548 remains one supported open body.
