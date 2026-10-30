# GiantBird canonical Module data access

Replace the private eight-byte Module declaration with the canonical header and
an abstract access view exposing the existing protected getModuleData member
through a using declaration. The view adds no fields, override or method body.
The independently recovered ModuleData interpretation remains separate.

Target instructions at 0x00369CDB load module+4; 0x00369CDE then adds +0x3C for
the existing name field. The complete Object::findModule body returns the raw
module entry. No full derived-class identity or native out-of-line getter RVA
is inferred from those accesses.

The getter's emitted spelling changes from public QBE to the canonical
protected IBE. Both copies contain exactly 8B 41 04 C3, without relocations.
The index records no executable incoming edge to the public name. Current
Drawable_xferDrawableModules and FoundationAIUpdateConstruct objects retain
public copies; WorkerAIUpdateCtor already supplies the protected copy. Their
source/command/dependency hashes and object receipt hashes match. Every getter
reference in these observed objects is debug-only. The evidence distinguishes
ordinary receipt currency from the stricter include-inventory receipts.

Private before/trial builds retain six exact rows and EXACT EH; all 30 external
code definitions and relocation edges are identical after this one access-name
normalization. The final strict-current object reproduces the trial. Normal
verification passes the two strings, empty-string reference and two floats.
The owning Module acceptance tool retires one key; preview against ccafe54d1d
retains LINKS/1,359 authored bytes. No census gain is claimed.
