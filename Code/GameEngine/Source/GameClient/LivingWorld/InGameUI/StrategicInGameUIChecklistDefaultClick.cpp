// cl: /O1 /G7 /MD
// Native C74F44 slot08 is the one-byte empty default click hook B3FD0.
// ResolveBattle checklist C75734 overrides the same slot with 5D1CD3;
// WB15B6B50 explicitly calls the empty base hook before its own work.
// Neutral base owner established by existing12B ctor/dtor views. Slot-name
// is structural, not a recovered original method name. Real empty C++
// body folds with the existing empty-dtor owner; zero unique-byte gain.
class Rva005CCDDD {
public:
 virtual ~Rva005CCDDD();
 virtual void slot04();
 virtual void clickSlot08();
 virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C(void*);
 int unknown4;void*payload;
};
void Rva005CCDDD::clickSlot08() {}
