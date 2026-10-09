// cl: /O1 /G7 /MD /EHsc /DNDEBUG
// ZH W3DModelDraw::doStartOrStopParticleSys is the semantic donor.
// Retail B6EDE..B6F6D instead iterates a sentinel list at +64 (node ID+8),
// with drawable+8 and shroud byte+49. Calls to the rowed hidden predicate,
// handle-returning findByID, byte stop/start setters and guarded unlink prove
// the target data flow. Ordinary potentially-throwing setter declarations
// preserve the native handle unwind state and hidden local; throw() changes
// the caller ABI shape by eliminating its EH frame. No pins or aliases.
class Rva00270260 { public: bool rva00270260(); };
class Rva001F3852ByteOneSetter { public: void enable(); };
class Rva001F384AByteZeroSetter { public: void disable(); };
class ParticleSystem {};
class RvaSmartPtr12
{
public:
 void rva0004CBC0();
 ParticleSystem *m_system;
 void *m_previous;
 void *m_next;
};
class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
 __forceinline ~BfmeParticleSystemHandle() { if(m_system) rva0004CBC0(); }
 operator bool() const { return m_system != 0; }
};
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
class W3DModelDraw;
class ParticleSystemManager
{
 friend class W3DModelDraw;
 BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);
};
extern ParticleSystemManager *TheParticleSystemManager;
struct Rva000B6EDEParticleNode
{
 Rva000B6EDEParticleNode *next;
 Rva000B6EDEParticleNode *previous;
 ParticleSystemID id;
};
class W3DModelDraw
{
private:
 void doStartOrStopParticleSys();
public:
 char p0[8];
 Rva00270260 *drawable;
 char pc[0x49-12];
 bool fullyObscured;
 char p4a[0x64-0x4a];
 Rva000B6EDEParticleNode *head;
};
void W3DModelDraw::doStartOrStopParticleSys()
{
 bool hidden=drawable->rva00270260() || fullyObscured;
 for(Rva000B6EDEParticleNode *n=head->next; n!=head; n=n->next)
 {
  BfmeParticleSystemHandle sys=TheParticleSystemManager->findParticleSystemByID(n->id);
  if(!sys) continue;
  if(hidden) ((Rva001F3852ByteOneSetter *)sys.m_system)->enable();
  else ((Rva001F384AByteZeroSetter *)sys.m_system)->disable();
 }
}
