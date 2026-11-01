# LineGroup owning-layout reconciliation

Target facts: the existing destructor at 1B3510 releases seven buffers, then
owns the pointer at +24 through an implicit member destructor. Its native EH
graph and all four rows verify. Constructor, setters and renderer verify the
remaining offsets of the complete layout.

Donor facts: method declarations and non-owning fields follow the LineGroup
header at the committed BFME 1 reference pin. This does not establish BFME 2's
original header path or the original name of its ownership template.

Structural inference: retain the existing reconstruction's RefCountPtr name
for a four-byte owning member. Keep only its proven null default constructor
and destructor; expose Referent to the existing implementation instead of
inventing pointer-conversion or assignment semantics. Existing Set_Texture
and Get_Shader provider/ABI debt remains, and their complete code is unchanged.

Both current units share linegrp_class.h through the already-sized header
context. The duplicate private destructor view and its two redundant pragma
controls leave; hatch_counters retires those controls. All 27 native rows and
both EH graphs pass ordinary and strict checks. Every retained complete code
definition and symbolic relocation remains unchanged; bounded LinkGuard
replacement against the newer dae306bc9d index reports no loss. The only new
combined definition is an unused null-default constructor, not a claimed row
or new byte-matching progress. No pin, profile or ledger row changes here.

The private supported composition accepts both units and preserves all 74
existing complete definitions, but actual file absorption still belongs to
the next tu_skeleton merge after this prerequisite commits.

Publication follow-up: the preceding 6e00b635d8 batch's wider audit was
INCONCLUSIVE against index86db074988, reporting two receipt gaps, first
linegrp.cpp. The newer index has now been fetched, and fresh strict receipts
cover both current LineGroup units. This is scoped evidence; the next census
must measure the new path/layout and wider consumer scope. No global link
clearance is asserted by the private checks.
