#ifndef Classes_H
#define Classes_H

class Star {
  private:
    String nome;
    byte id;
    int xpos;
    int ypos;
    byte velocita; //1:ad ogni step fai un passo, 2:ogni 2 step un passo
    byte contavelocita; //conteggio velocita, ogni stap tolgo 1 finche' non arrivo a zero
    byte passi; //quanti pixel avanzo
    byte colore[3];
  public:
    Star(byte id) {
      this->id = id;
    }
    int setXPos(int addxpos) {
      xpos += addxpos;
      return xpos;
    }
};
//  INIT Star star1 = Star(1);
#endif
