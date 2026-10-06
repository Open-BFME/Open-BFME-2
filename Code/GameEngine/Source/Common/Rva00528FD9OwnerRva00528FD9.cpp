// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?reset@Rva00528FD9Owner@@QAEXXZ, retail 0x00528fd9, 7 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Target Ghidra528FD9..528FE0 7B: [this] forwards to169B528F30.
// Full callee ends528FD9 RET0 and resets flags/strings/six records.
// Callee is unrowed; pointer owner and original names remain unproved.
class Rva00528F30Target {public:void reset();};
class Rva00528FD9Owner {public:void reset();private:Rva00528F30Target*target;};
void Rva00528FD9Owner::reset(){target->reset();}
