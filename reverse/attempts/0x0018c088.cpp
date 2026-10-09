// ?state@Rva0018C088TextureState@@QBEHXZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /DNDEBUG /MD
// Target 18C088..18C09B: two texture-state slots at +30/+34; original identity unknown.
class Rva0018C088TextureState { unsigned char unmodelled00[0x30];void *m_first;void *m_second;public:int state() const;};
int Rva0018C088TextureState::state() const {if(m_second)return 2;return m_first!=0;}
