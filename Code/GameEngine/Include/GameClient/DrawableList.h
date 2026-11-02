// Target facts (code addresses are RVAs): DrawableList has no virtual functions or vftable. The constructor path 0x00352E6F calls _List_base<Drawable *>::_List_base at 0x00239BB0, which stores its sentinel at +0 (0x00239BCF) and self-links node +0/+4 (0x00239BCA/0x00239BCC); no vptr is stored. GameClient::addIconLayer at 0x00239FD5 indexes these lists with stride 4, proving sizeof 4.
// Destructor ??1DrawableList@@QAE@XZ at 0x00239AF4 calls clear at 0x00239380 and returns the sentinel to the pool at VA 0x00DBA5E8; the list destructor thunk 0x00239BAB jumps to that same body. AIChargeTargetState::onEnter calls this destructor at 0x00352EAA. Declare it out of line. The rowed list constructor 0x00239CB7 and insert 0x00239D02 supply the inherited operations; pushBack's existing symbol binding and GameClient's call at 0x00239FDC identify list<Drawable *>::push_back at 0x00239E0B.
// Donor names: Zero Hour GameClient/InGameUI.h typedefs DrawableList as std::list<Drawable *>; BFME2's ledger proves the class spelling and destructor. Structural inference: the STLport base owns the only data word; DrawableList adds no members or virtual slots.

#pragma once

#ifndef BFME2_DRAWABLELIST_H
#define BFME2_DRAWABLELIST_H

#include <list>

class Drawable;

class DrawableList : public _STL::list<Drawable *>
{
public:
    ~DrawableList() throw();
    void pushBack(const Drawable *&drawable);
};

#endif
