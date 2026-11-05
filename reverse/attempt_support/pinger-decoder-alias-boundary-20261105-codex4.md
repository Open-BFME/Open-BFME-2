# Pinger decoder alias boundary

Inspected revision `2631f5140c`, 2026-11-05. This follows
[pinger-settingdata-alias-flags-20261104-codexb.md](pinger-settingdata-alias-flags-20261104-codexb.md).
The duplicate `_piSettingData` key remains at RVA 0x00A0C104.

Each trial used the supported `./build.sh` over pingerMain.c and peerPing.c,
with the existing owner externally defined, the consumer extern, and `/Ow`.
The starting `/Ow` result was reproduced: only `_piBytesToPing` fails (18/19).
No row was moved and no compiler cache entry was written manually.

| Additional source trial | Result |
| --- | --- |
| Volatile byte input pointer and six explicit dword payload copies from volatile input | Decoder changes its preserved-register contract and header scheduling; piProcessIncoming changes register allocation too (17/19). |
| Original byte input; six payload assignments with both dword source and destination volatile | Payload alternates loads/stores as retail does, but the final buffer increment is folded into +1 source displacements; magic validation becomes a direct memory comparison. Header still has the first increment too early (18/19). |
| Indexed magic/version loads then buffer += 2, with the explicit volatile payload | First two loads/stores agree, but the next field uses add eax,2 instead of the retail increments; validation and payload displacements still differ (18/19). |
| Prefix increment for the version load, with explicit volatile payload | Same header scheduling as the starting /Ow result; validation/displacement differences persist (18/19). |
| Prefix version load with original memcpy | Reproduces the original /Ow decoder mismatch (18/19). |
| Volatile first header destination store with prefix version load and original memcpy | Still reproduces the original /Ow decoder mismatch (18/19). |

These are compiler observations, not proof of the retail source or flags.
Next useful decoder work must preserve both pointer scheduling and the magic
reload while retaining the alternating payload operations; whole-input volatility
also changes the caller contract and is unsuitable. Approved TU placement remains
an alternative prerequisite for separating the alias-sensitive decoder.

All source and flag trials were restored. Final ordinary verification passes
19/19 rows, string/float checks and both named imports; declared-unmatched checks
pass. All five data-debt keys remain. No byte, linking, census or ownership gain
is claimed.
