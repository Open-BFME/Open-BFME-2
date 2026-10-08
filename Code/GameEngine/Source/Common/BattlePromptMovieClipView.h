#ifndef BFME2_BATTLE_PROMPT_MOVIE_CLIP_VIEW_H
#define BFME2_BATTLE_PROMPT_MOVIE_CLIP_VIEW_H

// C7A530 is installed by ctor 005FF912 and destroyed by 005FF95C.
// C7A448 is installed by ctor 005FED2A and destroyed by 005FED4D.
// The panel constructor at 005FEFCC proves the clip occupies +08..+13.
struct Rva005FF912Child;
class Rva005FF912
{
public:
    Rva005FF912(int, int);
    virtual ~Rva005FF912();
protected:
    Rva005FF912Child *m_04;
};
class Rva005FED2A : public Rva005FF912
{
public:
    Rva005FED2A(int, int, int);
    void rva005FF4BD(int);
    void rva005FF4CD(bool);
private:
    int m_08;
};

#endif
