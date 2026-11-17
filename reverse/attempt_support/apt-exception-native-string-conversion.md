# Apt exception reporter: native conversion binding

Repair base: `a46eefb2bc`. Consumer:
`Code/Libraries/Source/Apt/AptActionInterpreter.cpp`,
`?rva006FD340@Rva006FD340Object@@QAEXPADPAX@Z`, RVA `0x006FD340`, 171 bytes.
Provider: `Code/Libraries/Source/Apt/AptObject/AptArrayConstructor.cpp`,
`?toString@AptValue@@QBEXAAVEAStringC@@@Z`, RVA `0x006DD6C0`.

The current canonical AptValue header already declares the const reference
signature. The consumer had called the same address through an undefined
placeholder-class method taking a string pointer. The bounded repair changes
only that expression to call the existing provider through AptValue. It does
not infer any further placeholder-class identity or alter object storage.

Validation commands:

- `./build.sh Code/Libraries/Source/Apt/AptActionInterpreter.cpp`: 101/101
  functions, one data row, all string/float/import checks pass.
- `tools/eh_verify.py Code/Libraries/Source/Apt/AptActionInterpreter.cpp`:
  19 EXACT, zero missing or non-exact graphs.
- `tools/link_check.py` on that consumer plus
  `Code/Libraries/Source/Apt/AptObject/AptArrayConstructor.cpp`: exit 0,
  2/2 clean, consumer 12,344 bytes and unchanged provider 5,968 bytes.
  The old `0534e78db3` census index limits this to a scoped preview.

Independent COFF comparison of all 278 sections confirms unchanged non-debug
code/data bytes and flags. The only external relocation change is the REL32
at section 129, offset 58, now targeting the existing toString symbol. The
85 renumbered local labels retain the same sections and offsets; normalized
SafeSEH handlers are unchanged. Defined external symbols are unchanged and
the old callee is absent. A whole-object check against the 20 obsolete opaque
names finds no references, including weak bindings and linker directives.

Local before-source/object and logs are under
`build/decal-diagnostic/apt-exception-*`. Full real-link and game execution
remain separate required checks. No body, alias, pin or hatch was added.
