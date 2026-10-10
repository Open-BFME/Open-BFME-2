// ?rva000B5FE6@W3DScriptedModelDraw@@QAEXXZ
// partial score=0.7246193054607237 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target B5FE6..B61AB; same-this calls from scripted model draw.
// Object-template flag offsets and render slots measured from native.
class Team;enum Relationship{ENEMIES,NEUTRAL,ALLIES};
class Player {public:Relationship getRelationship(const Team*)const;};
class PlayerList{char prefix[16];public:Player *local;};extern PlayerList *ThePlayerList;
struct Rva000B5FE6Template {char prefix[0x108];unsigned flags[19];char gap[0x632-0x154];bool special632;};
class Object{public:char prefix[4];Rva000B5FE6Template *definition;char pad8[0x304-8];Team *team;char pad308[0x437-0x308];unsigned char state437,state438;bool isLocallyControlled()const;};
struct Rva000B5FE6Drawable{char prefix[4];Rva000B5FE6Template *definition;char pad8[0xfc-8];Object *object;char pad100[0x258-0x100];unsigned status258;};
class Rva000B5FE6Render {
public:
 virtual void v000();
 virtual void v001();
 virtual void v002();
 virtual void v003();
 virtual void v004();
 virtual void v005();
 virtual void v006();
 virtual void v007();
 virtual void v008();
 virtual void v009();
 virtual void v010();
 virtual void v011();
 virtual void v012();
 virtual void v013();
 virtual void v014();
 virtual void v015();
 virtual void v016();
 virtual void v017();
 virtual void v018();
 virtual void v019();
 virtual void v020();
 virtual void v021();
 virtual void v022();
 virtual void v023();
 virtual void v024();
 virtual void v025();
 virtual void v026();
 virtual void v027();
 virtual void v028();
 virtual void v029();
 virtual void v030();
 virtual void v031();
 virtual void v032();
 virtual void v033();
 virtual void v034();
 virtual void v035();
 virtual void v036();
 virtual void v037();
 virtual void v038();
 virtual void v039();
 virtual void v040();
 virtual void v041();
 virtual void v042();
 virtual void v043();
 virtual void v044();
 virtual void v045();
 virtual void v046();
 virtual void v047();
 virtual void v048();
 virtual void v049();
 virtual void v050();
 virtual void v051();
 virtual void v052();
 virtual void v053();
 virtual void v054();
 virtual void v055();
 virtual void v056();
 virtual void v057();
 virtual void v058();
 virtual void v059();
 virtual void v060();
 virtual void v061();
 virtual void v062();
 virtual void v063();
 virtual void v064();
 virtual void v065();
 virtual void v066();
 virtual void v067();
 virtual void v068();
 virtual void v069();
 virtual void v070();
 virtual void v071();
 virtual void v072();
 virtual void v073();
 virtual void v074();
 virtual void v075();
 virtual void v076();
 virtual void v077();
 virtual void v078();
 virtual void v079();
 virtual void v080();
 virtual void v081();
 virtual void v082();
 virtual void v083();
 virtual void v084();
 virtual void v085();
 virtual void v086();
 virtual void v087();
 virtual void v088();
 virtual void v089();
 virtual void v090();
 virtual void v091();
 virtual void v092();
 virtual void v093();
 virtual void v094();
 virtual void v095();
 virtual void v096();
 virtual void v097();
 virtual void v098();
 virtual void v099();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual void v110();
 virtual void v111();
 virtual void v112();
 virtual void v113();
 virtual void v114();
 virtual void v115();
 virtual void v116();
 virtual void v117();
 virtual void v118();
 virtual void v119();
 virtual unsigned flags(); virtual void addFlags(unsigned,bool);
};
struct Rva000B5FE6ModuleData{char prefix[0x6a];bool hidden;};
class W3DScriptedModelDraw {
 char pad0[4];Rva000B5FE6ModuleData *data;Rva000B5FE6Drawable *drawable;
 char padC[0x50-12];Rva000B5FE6Render *render;char pad54[0x214-0x54];int mode;
public:void rva000B5FE6();
};
void W3DScriptedModelDraw::rva000B5FE6(){
 Rva000B5FE6Drawable *d=drawable;Rva000B5FE6Template *t=d->definition;
 if(!t)return;
 if(mode==-1){if((t->flags[0]&2)||(t->flags[1]&0x10000000))render->addFlags(4,true);}else if(mode==1)render->addFlags(4,true);
 if(t->flags[0]&0x40)render->addFlags(8,true);
 else if((t->flags[3]&2)||(t->flags[4]&0x100))render->addFlags(0x200,true);
 Object *o=d->object;
 if(render->flags()&4){
  unsigned f=4;
  if((t->flags[2]&0x4000000)||(t->flags[0]&0x400)||(t->flags[5]&0x1000))f=0x84;
  if(o){Relationship r=ThePlayerList->local->getRelationship(o->team);
   if(o->isLocallyControlled())f|=0x100;
   else if(r==ENEMIES && !(o->definition->flags[1]&0x10000000))f|=0x10;
  }
  render->addFlags(f,true);
 }
 if(t->flags[2]&0x10)render->addFlags(0x20,true);
 if(t->flags[2]&0x1000)render->addFlags(0,true);
 if(o){
  if(o->state437&0x10)render->addFlags(0x40,true);
  Rva000B5FE6Template *ot=o->definition;
  if(!(ot->flags[0]&0x1400000) && !ot->special632 &&
    (((ot->flags[0]&0x80) && ((d->status258>>5)&1)) || (o->state438&1)))render->addFlags(0,true);
 }
 if(data->hidden)render->addFlags(0,true);
}
