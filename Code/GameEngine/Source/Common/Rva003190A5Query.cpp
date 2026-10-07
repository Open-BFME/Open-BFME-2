// cl: /O1 /MD
// Native Ghidra0x003190A5..0x003190BB (22B). ECX receiver reads the
// pointer at +0x78; null returns AL=0. Otherwise the unsigned word at
// pointee+0x2C is compared with 4 and its Boolean result returned in AL.
// Original classes, field meanings and complete extents remain unknown.
// The inline Boolean helper preserves the independently observed full ECX
// Boolean materialization followed by MOV AL,CL. It is a storage helper,
// not an independently identified retail member.
struct Item003190A5 { char prefix[0x2C]; unsigned int word; inline bool equalFour() const { return word==4; } };
class Rva003190A5 {
public: bool query() const;
private: char prefix[0x78]; Item003190A5 *item;
};
bool Rva003190A5::query() const
{
if(item) { return item->equalFour(); } return false;
}
