# Defection Module storage view

Replace the private, nonpolymorphic Module placeholder with the registered
eight-byte base and a partial storage view for TemporarilyDefectUpdate's byte
at +0x2C. Only that byte is modeled; the original complete hierarchy and the
meaning of its other state are not claimed.

The complete 218-byte native completion caller at 0x0029A12B calls the existing
findModule owner at 0x0029A195, then writes one at [EAX+0x2C] at 0x0029A19C.
The complete 43-byte finder returns the unadjusted module-array entry. Its
name-key initializer uses the TemporarilyDefectUpdate literal. Containment,
AI, the independently rowed Object::defect body and all call signatures stay
unchanged.

Private before/trial compiles and the final strict-current object preserve all
six rows, both EXACT EH graphs and all four external code definitions and
symbolic relocations. Normal builds retain both string references. The owning
header acceptance tool passes and retires one Module key. Ordinary preview
against ccafe54d1d retains LINKS and 546 authored bytes; no census gain is
claimed.
