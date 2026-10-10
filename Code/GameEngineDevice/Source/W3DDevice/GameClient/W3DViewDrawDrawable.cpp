// cl: /O1 /G7 /MD /EHsc
// ZH W3DView.cpp drawDrawable semantic guide, BFME1 revision575ba2b04.
// Native859F5..85A03: cdecl two stack arguments, forwards the context as
// View* to rowed Drawable::draw(27C157), then RET. The camera update8C3AC
// passes this callback address to GameClient's drawable traversal slot68.
class View;
class Drawable {public:void draw(View*);};
void drawDrawable(Drawable*draw,void*view){draw->draw((View*)view);}
