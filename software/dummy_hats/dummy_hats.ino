// cycles per frame
#define CPF 50


class Node {
public:

  Node* next;

  Node();
  Node(Node* next);

};

class Grid {
private:

  uint8_t ret = 22;
  uint8_t select4 = 24;
  uint8_t select3 = 26;
  uint8_t select2 = 28;
  uint8_t select1 = 30;
  uint8_t select0 = 32;

  uint8_t dats[15] = {
    21, 20, 19, 18, 17, 16, 0, 1, 2, 3,4,5,7,8,9
  };

  int indexes[15] = {
    1, 0, 3, 2, 5, 4, 12, 11, 10, 9, 8, 7, 6, 13, 14
  };



  int numGrids;

  int gridX, gridY;

  short apple[3];

  Node* headPtr;
  Node* tailPtr;

  Node**** grid;

public:

  Grid(int numHats) {

    numGrids = numHats;
    gridX = 3;
    gridY = 5;

    for (int i = 0; i < 15; i++) {
      pinMode(dats[i], OUTPUT);
    }

    pinMode(ret, INPUT);
    pinMode(select0, OUTPUT);
    pinMode(select1, OUTPUT);
    pinMode(select2, OUTPUT);
    pinMode(select3, OUTPUT);
    pinMode(select4, OUTPUT);

    grid = new Node***[numGrids];
    for(int i = 0; i < numGrids; i++) {
      grid[i] = new Node**[gridX];
      for(int j = 0; j < gridX; j++) {
        grid[i][j] = new Node*[gridY];
        for(int k = 0; k < gridY; k++) {
          grid[i][j][k] = nullptr;
        }
      }
    }

    apple[0] = gridX - 1;
    apple[1] = gridY - 1;
    apple[2] = numGrids - 1;


  };

  void render() {
    for(int i = 0; i < CPF; i++) {
      for(int j = 0; j < numGrids; j++) {
        switch (j) {
          case 0:
            // 001
            digitalWrite(select0, HIGH);
            digitalWrite(select1, LOW);
            digitalWrite(select2, LOW);
            break;
          case 1:
            // 011
            digitalWrite(select0, HIGH);
            digitalWrite(select1, HIGH);
            digitalWrite(select2, LOW);
            break;
          case 2:
            // 101
            digitalWrite(select0, HIGH);
            digitalWrite(select1, LOW);
            digitalWrite(select2, HIGH);
            break;
        }

        for (int k = 0; k < gridX; k++) {
          for (int l = 0; l < gridY; l++) {
            //bool light = (grid[j][k][l] != nullptr) || (j == apple[2] && k == apple[0] && l == apple[1]);
            bool light = (j == 1 && k == 1 && l == 1);
            setPixel(k, l, light);
          }
        }
      }
    }
  }

  void setPixel(int x, int y, bool isOn) {
    digitalWrite(dats[indexes[(y*3) + x]], isOn ? HIGH : LOW);
  }

  ~Grid();
  


};


Grid* grid;

void setup() {
  grid = new Grid(3);
}

void loop() {
  grid -> render();
}
