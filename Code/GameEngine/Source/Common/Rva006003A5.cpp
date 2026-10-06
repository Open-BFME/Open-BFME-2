// cl: /MD
// ?rva006003A5@Rva006003FC@@QAEXPAVObject@@@Z @0x006003A5 8B vslot.
// Retail add ecx,8 then jmp performUpgradeFX 0x0047A69C. Evidence: vslot lane;
// slot 2 of 0x0087A638 class of ??1Rva006003FC@@UAE@XZ; pin-only callee
// ?performUpgradeFX@UpgradeMuxData@@QBEXPAVObject@@@Z; tail return-mem-method
// gives add-jmp at /O1.
class Object;
class UpgradeMuxData {
public: void performUpgradeFX(Object *obj) const;
};
class Rva006003FC {
public: void rva006003A5(Object *obj);
private: char m_pad[8];
         UpgradeMuxData m_mux;
};
void Rva006003FC::rva006003A5(Object *obj)
{
	m_mux.performUpgradeFX(obj);
}
