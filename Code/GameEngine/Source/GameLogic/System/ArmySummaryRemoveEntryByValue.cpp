// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG
// Twin lead: ArmySummary.cpp rva0040E672. Native40E6A4..40E6D6
// uses entry-pointer equality search40CB79 instead of key search40CB3A.
// The output ABI is the same owning4-byte handle, not an int return:
// this explains the otherwise unexplained return-state initialization.
// API-only receiver declarations: no ArmySummary allocation/layout asserted.
// The return handle's established default constructor and destruction
// contracts agree with ArmySummary.h; no copy/destructor emits here.
struct Rva004F69C3Target;
struct Rva0040DD3ARef {
 Rva004F69C3Target *value;
 Rva0040DD3ARef():value(0){}
 Rva0040DD3ARef(const Rva0040DD3ARef &);
 ~Rva0040DD3ARef();
};
class ArmySummaryEntry;
class Rva0040CB3AIndexedField {
public: int rva0040CB79(ArmySummaryEntry *) const;
};
class ArmySummary {
public:
 Rva0040DD3ARef RemoveEntry(int);
 Rva0040DD3ARef rva0040E6A4(ArmySummaryEntry *entry);
};
Rva0040DD3ARef ArmySummary::rva0040E6A4(ArmySummaryEntry *entry) {
 int index=reinterpret_cast<const Rva0040CB3AIndexedField *>(this)->rva0040CB79(entry);
 if(index<0) return Rva0040DD3ARef();
 return RemoveEntry(index);
}
