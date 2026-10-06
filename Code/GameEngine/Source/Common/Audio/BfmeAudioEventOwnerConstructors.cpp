// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD
#include "Common/BfmeAudioEventPrefix136.h"
// PC boundaries2DA461-2DA4DB and2DA4DB-2DA555, each122B.
// Lua caller3356AE supplies Object+74; caller33382F supplies Drawable::getID.
// Native position worker2DA1CC confirms tags2/object and1/drawable by its
// GameLogic lookup and GameClient slot40 lookup. All other state comes from
// the shared verified initializer2D96D3. Return-position value is discarded.
enum ObjectID { INVALID_ID=0 };
enum DrawableID { INVALID_DRAWABLE_ID=0 };
BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const OpaqueRefElement4 &ref, ObjectID id) {
 rva002D96D3(ref);
 m_int34=id;
 m_int30=0;
 if(id) m_int38=2;
 else m_int34=0;
 bool valid;
 rva002DA1CC(valid);
}
BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const OpaqueRefElement4 &ref, DrawableID id) {
 rva002D96D3(ref);
 m_int34=id;
 m_int30=0;
 if(id) m_int38=1;
 else m_int34=0;
 bool valid;
 rva002DA1CC(valid);
}
