#include <iostream>
#include <stdlib.h>

using namespace std;

struct Bit{
  int i;
  Bit* next;
};

//class definition
class Number{
public:
  Number(int a) {
    this->num = a;
    this->bit = convertToBin(a);
  }

  Number() {}

  int getNum() {
    return this->num;
  }

  Bit* getBit() {
    return this->bit;
  }

private:
  int num;
  Bit* bit;
  Bit* convertToBin(int a) {
    Bit* bit = new Bit;
    bit->i = -1;
    bit->next = NULL;

    for (int i=0; i<5; i++) {
      Bit* tmp = new Bit;
      int bin = (a >> i) & 1;

      tmp->i = bin;
      tmp->next = bit;
      bit = tmp;
    }
    return bit;
  }
};


class Container{
public:
  Container() {
    this->relation = new Relation;
    this->relation->gr = NULL;
    this->relation->next = NULL;
  }

  void updateRelation(Number num1, Number num2) {
    Group* gr = new Group;
    gr->num1 = num1;
    gr->num2 = num2;
    gr->dig = getDig(num1, num2);
    gr->relgr = NULL;

    Relation* curr = relation;
    while (curr->gr) {
      curr = curr->next;
    }
    curr->gr = gr;
    curr->next = new Relation;
    curr->next->gr = NULL;
    curr->next->next = NULL;
  }

  void combine() {
    Relation* iterator = relation;
    while(iterator->next) {
      Relation* curr = relation;
      int a[5] = {-1, -1, -1, -1, -1};
      int aIndex = 0;
      while(curr->gr->num1.getNum() == curr->next->gr->num1.getNum()) {
        curr = curr->next;
        a[aIndex] = curr->gr->num2.getNum();
        aIndex++;
      }
      int d = iterator->gr->num1.getNum();
      int dig = iterator->gr->dig;

      aIndex = 0;
      while (a[aIndex] != -1) {
        Relation* tmp = curr->next;
        while(tmp->next) {
          if (tmp->gr->num1.getNum() == a[aIndex] && tmp->gr->dig == dig) {
            iterator->gr->relgr = tmp->gr;
          }
          tmp = tmp->next;
        }
        aIndex++;
      }
      iterator = iterator->next;
    }
  }

  void print() {
    Relation* curr = relation;
    while(curr->gr) {
      if (curr->gr->relgr) {
        cout << "Group: " << curr->gr->num1.getNum() << ", " << curr->gr->num2.getNum() << ", " << curr->gr->relgr->num1.getNum() << ", " << curr->gr->relgr->num2.getNum()<< endl;
      }
      cout << "Group: " << curr->gr->num1.getNum() << ", " << curr->gr->num2.getNum() << endl;
      curr = curr->next;
    }
  }

private:
  struct Group{
    Number num1;
    Number num2;
    int dig;
    Group* relgr;
  };

  struct Relation{
    Group* gr;
    Relation* next;
  };
  Relation* relation;

  int getDig(Number num1, Number num2) {
    Bit* b1 = num1.getBit();
    Bit* b2 = num2.getBit();
    Bit* b1tmp = b1;
    Bit* b2tmp = b2;
    int dig = 5;
    while(b1tmp->i == b2tmp->i) {
      b1tmp = b1tmp->next;
      b2tmp = b2tmp->next;
      dig--;
    }
    return dig;
  }

  void purge(Group* gr1, Group* gr2) {
    Relation* toKill = iterator;
    while(toKill->next->gr != tmp->gr) {
      toKill = toKill->next;
    }
    if (toKill->next->next) {
      toKill->next = toKill->next->next;
    }
    else toKill->next = NULL;
  }
};

///////////////function definition//////////////////

bool related(Number n1, Number n2) {
  Bit* b1 = n1.getBit();
  Bit* b2 = n2.getBit();
  Bit* b1tmp = b1;
  Bit* b2tmp = b2;
  int relCount = 0;
  while (b1tmp->i != -1) {
    if (b1tmp->i == b2tmp->i) relCount++;
    b1tmp = b1tmp->next;
    b2tmp = b2tmp->next;
  }

  if (relCount == 4) return true;
  else return false;
}



/////////////////main class///////////////

int main(const int argc, const char* const argv[]) {
  //deal with arguments
  int arg[argc];
  for (int i=0; i<argc; i++) {
    arg[i] = atoi(argv[i+1]);
  }

  //construct number objects
  Number n[argc];
  for (int i=0; i<argc; i++) {
    n[i] = Number(arg[i]);
  }

  //construct a container
  Container container;

  for (int i=0; i<argc-1; i++) {
    for (int j=i+1; j<argc-1; j++) {
      if (related(n[i], n[j])) {
        container.updateRelation(n[i], n[j]);
      }
    }
  }
  container.combine();
  container.print();
}
