// cl: /O1 /G7 /MD /EHsc /DNDEBUG
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Reference: clean BFME1 6d943426 W3DModelDraw::stopClientParticleSystems
// establishes find-by-ID, destroy-if-present, then clear the tracked IDs.
// Target evidence is separate: native 0x004BE3EF/142 uses a linked chain at
// receiver +0xC8 (node ID +4, next +8), the rowed find-by-ID at 0x001F5B0A,
// ParticleSystem::destroy at 0x001F462C, and handle unlink at 0x0004CBC0.
// The node's original class is unknown. Native slot 0 takes flags=0 and
// returns the allocation pointer subsequently passed to scalar delete.
// The 12-byte result view preserves the callee ABI and guards intrusive
// unlink exactly as this caller does; the linker alias uses the existing
// verified provider rather than defining a second manager function.
struct ParticleSystem { void destroy(); };
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID=0 };
// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle { ~BfmeParticleSystemHandle(); ParticleSystem *system; void *previous; void *next; };
struct BfmeW3DParticleHandle {
 ParticleSystem *system; void *previous; void *next;
 // ?BfmeW3DParticleHandle::~BfmeW3DParticleHandle absent-from-retail
 __forceinline ~BfmeW3DParticleHandle() { if (system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0(); }
};
class W3DModelDraw;
class ParticleSystemManager {
 friend class W3DModelDraw;
 BfmeW3DParticleHandle findParticleSystemByID(ParticleSystemID);
};
extern ParticleSystemManager *TheParticleSystemManager;
#pragma comment(linker, "/alternatename:?findParticleSystemByID@ParticleSystemManager@@AAE?AUBfmeW3DParticleHandle@@W4ParticleSystemID@@@Z=?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z")
struct BfmeW3DParticleNode { void *vtable; ParticleSystemID id; BfmeW3DParticleNode *next; };
class BfmeW3DParticleNodeDispatch {};
typedef void *(BfmeW3DParticleNodeDispatch::*NodeDestroy)(unsigned int);
class W3DModelDraw {
protected: void stopClientParticleSystems();
 char opaque00[0xC8]; BfmeW3DParticleNode *nodes;
};
void W3DModelDraw::stopClientParticleSystems() {
 while (nodes) {
  BfmeW3DParticleHandle system=TheParticleSystemManager->findParticleSystemByID(nodes->id);
  if (system.system) system.system->destroy();
  BfmeW3DParticleNode *next=nodes->next;
  void *released;
  if(nodes) released=(((BfmeW3DParticleNodeDispatch *)nodes)->*(*(NodeDestroy *)&(*(void ***)nodes)[0]))(0);
  else released=0;
  operator delete(released);
  nodes=next;
 }
}
