The existing vector<AsciiString>::operator= at 0x000BDB46 (180 bytes) remains byte-exact under the existing bfmealloc_alloconly header plus _STLP_NO_EXCEPTIONS. These settings eliminate seven allocator and construction-range link blockers while retaining stock dispatch by const reference. This is evidence for a future repair, not new recovery or linking credit.

The unit still cannot link: the first operator= COMDAT kept in link order is the wrong stock definition from ThingTemplate.cpp. W3DModelDraw.cpp and stlport_vector_asciistring_copy_backward.cpp also precede the proven owner. Original link checks 26437 and 82097 ended with exit 1; the current owner is judged retail, while the independently repaired VectorAsciiStringErase.cpp links 91 bytes.

The proposed declaration-only specialization repair was not attempted in those earlier providers. ThingTemplate.cpp is reserved by peppy-luna-singletons-20261009 and W3DModelDraw.cpp by w5-l02. The acquired copy_backward file claim was released without edits. The published change restores the old assignment row and flags, retaining only vendor-consistent inline linkage for its existing exact copy_ptrs helper to remove the competing strong definition.

Target facts: the native assignment calls actual rowed allocation/copy at 0x000BBCA7 (45 bytes), clear at 0x0002CD53 (30), copy_ptrs at 0x000B6614 (29), destruction at 0x0002CB64, and construction-range copy at 0x0002C4B2 (38). The existing twenty callers establish source-reference thiscall assignment. Vendor headers at BFME1 revision 575ba2b04743f190f069805fbdc59936123c45da and current BFME2 compatibility headers were inspected. The existing row, callers, and helper contract support the string-vector identity. No alias, pin, or private class is added.

Two explicit member-template declaration forms hit the MSVC7.1 internal compiler error C1001. Declaring only the construction-range specialization changed register and tag lifetimes and failed byte proof. These forms were reverted. The successful trial preserves the existing Code/Libraries/Source/WWVegas/WWLib/StlportAsciiStringVectorAssign.cpp body, including the inline dispatch repair. Only its existing compiler comment adds /D_STLP_NO_EXCEPTIONS and /Ireference/shims/bfmealloc_alloconly. Its full private snapshot is build/seat3/resume-oct8/assignment-alloconly-exact180.cpp. A second source artifact is deliberately not registered: this RVA already has real C++, so check_csv correctly forbids a reverse/attempts stash for it.

The exact trial configuration, against that existing body:

```text
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc_alloconly
```
