// ??1Rva0052B497@@UAE@XZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /MD /GX-
// Target31B native52B497..52B4B6. Existing deleting wrapper52B56C
// names Rva0052B497 and vtableC68620. SaveGameInfoCopyBFME2.cpp
// establishes XferSave-derived storage40, flag40, digest41..50, context54.
// This hot-body trial deliberately has an incomplete vtable contract:
// target39 slots override2/4/5/6/11/38; no Code admission until providers
// and target ABI are reconciled. XferSave spelling remains donor-derived.
void __cdecl operator delete(void *);
class XferSave {
public: virtual ~XferSave();
private: char m_storage[0x3c];
};
class Rva0052B497 : public XferSave {
public: virtual ~Rva0052B497();
private: unsigned char m_flag; unsigned char m_digest[16];
 void *m_context; unsigned char m_done;
};
Rva0052B497::~Rva0052B497() {
 if(m_context) ::operator delete(m_context);
}
