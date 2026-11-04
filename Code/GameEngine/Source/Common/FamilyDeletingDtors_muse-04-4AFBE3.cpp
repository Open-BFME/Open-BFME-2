// cl: /MD
// ??_GRespawnUpdateModuleData@@UAEPAXI@Z @0x004AFBE3, 28B.
// Scalar deleting dtor slot 0 of vtable 0x008556F8; calls rowed ??1 at
// 0x004AFBFF plus rowed delete at 0x0002FD60.

struct EmitVtableTag;

class RespawnUpdateModuleData { public: RespawnUpdateModuleData(EmitVtableTag *); virtual ~RespawnUpdateModuleData(); public:
	virtual void bfmeVtSlot1() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot2() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot3() = 0; // __purecall in every copy of this vtable
};
// ?<RespawnUpdateModuleData::RespawnUpdateModuleData> absent-from-retail
RespawnUpdateModuleData::RespawnUpdateModuleData(EmitVtableTag *) {}
