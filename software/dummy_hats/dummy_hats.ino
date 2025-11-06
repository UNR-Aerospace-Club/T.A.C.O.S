// cycles per frame
#define CPF 100
#define BPT 100

class Node {
public:

  Node* next;

  int x, y, z;

  Node() {
    next = nullptr;
    x = 0; 
    y = 0;
    z = 0;
  };
  Node(int x, int y, int z) {
    next = nullptr;
    this->x = x;
    this->y = y;
    this->z = z;
  };

};

class Grid {
private:

  int blinkCount = 0;

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

  int apple[3];

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

    grid = new Node***[gridX];
    for(int i = 0; i < gridX; i++) {
      grid[i] = new Node**[gridY];
      for(int j = 0; j < gridY; j++) {
        grid[i][j] = new Node*[numGrids];
        for(int k = 0; k < numGrids; k++) {
          grid[i][j][k] = nullptr;
        }
      }
    }

    apple[0] = gridX - 1;
    apple[1] = gridY - 1;
    apple[2] = numGrids - 1;
    moveApple();

    headPtr = new Node(0, 0, 0);
    tailPtr = new Node(1, 0, 0);
    headPtr->next = tailPtr;
    grid[0][0][0] = headPtr;
    grid[1][0][0] = tailPtr;
  };

  ~Grid() {
    while (headPtr->next != nullptr) {
      Node* tmp = headPtr->next;
      delete headPtr;
      headPtr = tmp;
    }

    headPtr = nullptr;
    tailPtr = nullptr;
  }

  bool gameLoop() {
    // any length on a dummy hat will never be this long
    int shortestDistToApple = 1000;

    int x = tailPtr->x;
    int y = tailPtr->y;
    int z = tailPtr->z;
    for (int i = 0; i < 6; i++) {
      int x2 = tailPtr->x;
      int y2 = tailPtr->y;
      int z2 = tailPtr->z;
      switch(i) {
        case 0:
          // if (x2 == 0) continue;
          // x2 -= 1;
          // tmp = grid[x2][y2][z2];
          x2 -= 1; 
          break;
        case 3:
          // if (y2 == 0) continue;
          // y2 -= 1;
          // tmp = grid[x2][y2][z2];  
          y2 -= 1;  
          break;
        case 5:
          // if (z2 == 0) continue;
          // z2 -= 1;
          // tmp = grid[x2][y2][z2];
          z2 -= 1;
          break;

        case 4: z2+=1; break;
        case 1: x2+=1; break;
        case 2: y2+=1; break;
      }
      if (checkGrid(x2, y2, z2) != nullptr) continue;

      int dist = abs(apple[0] - x2) + abs(apple[1] - y2) + abs(apple[2] - z2);
      
      if (dist < shortestDistToApple) {
        shortestDistToApple = dist;
        x = x2;
        y = y2;
        z = z2;
      }
    }

    if (shortestDistToApple == 1000) return true;


    Node* tmp = new Node(x, y, z);
    tailPtr->next = tmp;
    tailPtr = tmp;
    grid[x][y][z] = tailPtr;
 

    // check if we're at the apple - dont delete tail if we are
    if (x == apple[0] && y == apple[1] && z == apple[2]) {moveApple(); return;}


    int dx, dy, dz;
    dx = headPtr->x;
    dy = headPtr->y;
    dz = headPtr->z;

    tmp = headPtr->next;
    delete headPtr;
    grid[dx][dy][dz] = nullptr;
    headPtr = tmp;

    return false;
  }

  void render() {
    for(int i = 0; i < CPF; i++) {
      blinkCount++;
      if (blinkCount > BPT) blinkCount = 0;
      for(int j = 0; j < numGrids; j++) {

        // first, set all of the data pins to be off
        for (int k = 0; k < gridX; k++) {
          for (int l = 0; l < gridY; l++) {
            setPixel(k, l, false);
          }
        }

        // select the proper hat for drawing
        selectHat(j);

        // write that data
        for (int k = 0; k < gridX; k++) {
          for (int l = 0; l < gridY; l++) {
            bool light = (grid[k][l][j] != nullptr) || ((j == apple[2] && k == apple[0] && l == apple[1]) && blinkCount < BPT / 2);
            setPixel(k, l, light);
          }
        }
      }
    }
  }

  void blink() {
    for(int i = 0; i < CPF * 10; i++) {
      blinkCount++;
      if (blinkCount > BPT) blinkCount = 0;
      for(int j = 0; j < numGrids; j++) {

        // first, set all of the data pins to be off
        for (int k = 0; k < gridX; k++) {
          for (int l = 0; l < gridY; l++) {
            setPixel(k, l, false);
          }
        }

        // select the proper hat for drawing
        selectHat(j);

        // write that data
        for (int k = 0; k < gridX; k++) {
          for (int l = 0; l < gridY; l++) {
            bool light = i < CPF * 5;
            setPixel(k, l, light);
          }
        }
      }
    }
  }

  void setPixel(int x, int y, bool isOn) {
    digitalWrite(dats[indexes[(y*3) + x]], isOn ? HIGH : LOW);
  }

  void selectHat(int index) {
    switch (index) {
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
  }

  void moveApple() {
    int ct = 0;
    do {
      apple[0] = random(0, gridX);
      apple[1] = random(0, gridY);
      apple[2] = random(0, numGrids);
      ct++;
      if (ct >= 500) randomSeed(analogRead(0) * random(0,204394));
    } while (checkGrid(apple[0], apple[1], apple[2]) != nullptr);
  }

  // will return the node at the given point accounting for wrap-around
  Node* checkGrid(int x, int y, int z) {
    // surely this doesn't cause issues :)

    // just return a node so that we dont move there
    if ((x < 0) || (y < 0) || (z < 0) || (x >= gridX)
        || (y >= gridY) || (z >= numGrids)) return headPtr;

    return grid[x][y][z];
  }
  
  // will return the node at the given point accounting for wrap-around
  Node* checkGridChange(int& x, int& y, int& z) {
    // surely this doesn't cause issues :)

    if (x < 0) x = gridX - 1;
    if (y < 0) y = gridY - 1;
    if (z < 0) z = numGrids - 1;

    if (x >= gridX) x = 0;
    if (y >= gridY) y = 0;
    if (z >= numGrids) z = 0;

    return grid[x][y][z];
  }
  

};


Grid* grid;

void setup() {  
  randomSeed(analogRead(0));
  grid = new Grid(3);
  grid->blink();
  grid->blink();
  grid->blink();
}

void loop() {
  grid->render();
  if (grid->gameLoop()) {
    grid->blink();
    grid->blink();
    grid->blink();
    delete grid;
    grid = new Grid(3);
    randomSeed(analogRead(0));
  };
}
