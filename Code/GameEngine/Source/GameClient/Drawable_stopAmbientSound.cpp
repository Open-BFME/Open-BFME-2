// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?stopAmbientSound@Drawable@@QAEXXZ, retail 0x002743D7, 42 bytes.
// Drawable audio-handle release plus opaque holder clear: TheAudio slot 0x6c
// removeAudioEvent with the +0x144 handle then store 1 then tail-jmp to the
// rowed ?clear@Rva000A8C9B@@QAEXXZ on the +0x110 holder.
// Evidence: packet disasm plus TheAudio ?TheAudio@@3PAVAudioManager@@A plus
// slot 0x6c removeAudioEvent precedent CastleMemberBehaviorDtor plus rowed
// clear Rva000A8C9BClear plus neighbour Drawable_rva00274176 TU and flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class OpaqueRefCounted;

void Drawable::stopAmbientSound()
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	TheAudio->removeAudioEvent(self->m_ambientSound144);
	self->m_ambientSound144 = 1;
	return self->m_holder110.clear();
}
