# Deferred SJA pointer-helper binding repair

Source base: cc80e697fd. Checker fixes were published independently in
e17942b252 and 673e958dc5 before this source change.

The existing pointer-table helper declarations now use inline call adapters to
rowed native owners: bucket index -> Rva000427195::bucketIndex (0x00223149),
node release -> Rva001FD9EF::rva001FD9EF (0x001FD9EF), iterator advance ->
Rva000411084::advance (0x003F7925). Canonical receivers use their headers.
The adapters provide no emitted body or import/reference in the current COFF;
existing same-named value-table specializations remain distinct.

Verification:

- `./build.sh Code/GameEngine/Source/Common/BfmeConv1292DeferredWalkers.cpp`:
  all 6 rows / 298 bytes exact, including normal string/float/import checks.
- `link_check.py --prepare-current` for this source: normal 6/6 byte checks
  and strict current source/flags/include receipt. The frozen inventory's
  `--fail` check passes with that receipt.
- [Provider delta](provider-delta.json): all 56 external definitions retained;
  no added/removed provider or binding-property change. Exactly three pointer
  callers change relocations to the native owners above; their complete raw
  payloads are unchanged. This compares the pre-edit object against the final
  strict-current object, using COFF bodies, relocations and COMDAT selection.
- [Scoped preview](link-preview.txt): LINKS, 0 -> 298 bytes against census
  2026-11-03 20:03 at 8661f15284. This is an indexed preview, not a closed
  current provider-closure check or an official census/real-link/runtime result.
- [Identity scan](identity-findings.json): exactly the same three inherited
  shadow findings as the prior native-provider evidence. All their parent and
  callee payloads/relocations are unchanged by this repair. They remain open.

No ledger, pin, alternatename, hatch, source-path or census changes. The next
scheduled census must confirm the preview and prior push-receipt gaps; no
nightly, game smoke or direct link-cycle run was started. Separately reconcile
value-iterator increment and value-hash erase identities documented in the
inherited findings; this repair does not establish them.
