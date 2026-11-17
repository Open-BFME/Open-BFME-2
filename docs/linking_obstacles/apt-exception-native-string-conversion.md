### Apt exception reporter calls the existing string conversion

Status: repaired locally; fresh real-link confirmation pending.

The real link at `1ffed447e60475f63b29d0d56d4b41ff4fe06578` reports the
undefined pointer-argument spelling of `BfmeAptValue006DCD20::rva006DD6C0`
from `AptActionInterpreter.cpp`. The exception reporter at RVA `0x006FD340`
calls the existing `AptValue::toString(EAStringC &) const` body at `0x006DD6C0`.
The canonical AptValue declaration is already included by this consumer.

The call now uses that declaration directly, interpreting the existing value
pointer as AptValue and passing the existing local string by reference. No
conversion implementation, alias, pin, layout or shared header changes.

Official scoped build: 101/101 functions and one data row pass. All 19 EH
graphs are EXACT. Provider-inclusive link preview: 2/2 sources link cleanly,
18,312 own bytes; the conversion provider retains its 5,968 bytes. This preview
uses census index `0534e78db3` and is not a fresh whole-game link measurement.

See [evidence](../../reverse/attempt_support/apt-exception-native-string-conversion.md).
