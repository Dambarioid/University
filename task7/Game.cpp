#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <unistd.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define MOVE_SPEED 10
int shipLive = 3;
int counter = 1;

char numBonus[5];
int bonusNum;

SDL_Rect destRectBonus = {bonusNum, 0, 50, 50};
Uint32 TimerCallback(Uint32 interval, void *param);
Uint32 TimerCallback2(Uint32 interval, void *param);
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *renderer);
bool checkCollision(SDL_Rect obj1, SDL_Rect obj2);
bool init(SDL_Window *&window, SDL_Renderer *&renderer);

int main(int argc, char *argv[]) {

  // Проверка на вхождение никнейма игрока
  if (argc < 2){
    std::cout << "Enter the name of player" << std::endl;
    return EXIT_FAILURE;
  }

  // Создаем файл в который будем загружать результаты игроков
  std::ofstream file(argv[1], std::ios::app); 

  // Создаем окно и рендер
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  // Проверка на инициализацию окна рендера и шрифта
  if (!init(window, renderer)) {
    return -1;
  }
  if (TTF_Init() == -1) {
    printf("TTF_Init Error: %s\n", TTF_GetError());
    return 1;
  }

  TTF_Font *font =
      TTF_OpenFont("./Assets/GeistMono-Black.ttf", 48); 
  if (!font) {
    printf("TTF_OpenFont Error: %s\n", TTF_GetError());
  }
  SDL_Color fontColor = {255, 255, 255};

  // Загрузка текстур
  SDL_Texture *first_live = loadTexture("./Assets/Lives.bmp", renderer);
  SDL_Texture *second_live = loadTexture("./Assets/Lives.bmp", renderer);
  SDL_Texture *third_live = loadTexture("./Assets/Lives.bmp", renderer);
  SDL_Texture *bonus;
  SDL_Texture *bg = loadTexture("./Assets/ktQBX2.bmp", renderer);
  SDL_Texture *ast = loadTexture("./Assets/asteroid.bmp", renderer);
  SDL_Texture *ast2 = loadTexture("./Assets/asteroid.bmp", renderer);
  SDL_Texture *ship = loadTexture("./Assets/gieo784eT.bmp", renderer);

  // Проверка загрузки текстур
  if (!first_live || !second_live || !third_live || !bg || !ast || !ast2 || !ship) {
    return -1;
  }

  // Загрузка координат
  SDL_Rect lives_pos = {100, 0, 50, 50};
  SDL_Rect lives_pos2 = {160, 0, 50, 50};
  SDL_Rect lives_pos3 = {220, 0, 50, 50};
  SDL_Rect destRectTimer = {300, 0, 200, 100};
  SDL_Rect destRectBg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect destRectShip = {300, 700, 100, 100};
  SDL_Rect destRectFirAstr = {0, 0, 100, 100};
  SDL_Rect destRectSecAstr = {700, 0, 100, 100};

  //Ассинхронные таймеры для подсчёта alive time, рандомной траэктории бонуса
  SDL_AddTimer(1000, TimerCallback, NULL);
  SDL_AddTimer(5000, TimerCallback2, NULL);

  // Обновление текста на окне
  char timerText[50];

  // Переменные для рандомной траектории астероидов
  int randomnum = rand() % 11;
  int randomnum2 = rand() % 11;

  bool quit = false;
  SDL_Event e;
  bool flag = false;


  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // При каких условиях выпдает бонус
    if (counter % 5 == 0 && flag == false) {
      if (counter % 2 == 0) {
        bonus = loadTexture("./Assets/bomb-icon-28191.bmp", renderer);
        strncpy(numBonus,"bomb",4);
      } else {
        bonus = loadTexture("./Assets/wrench-128.bmp", renderer);
        strncpy(numBonus,"heal",4);
      }
      flag = true;
    }

    //Обновляем текст с каждым новым значением counter
    snprintf(timerText, sizeof(timerText), "Time: %d", counter);

    // Записываем текст в timeText в белый текст(Сначала создавая поверхность, а потом уже текстуру)
    SDL_Surface *TimerSurface = TTF_RenderText_Solid(font, timerText, fontColor);
    if (!TimerSurface) {
      printf("RenderText Error: %s\n", TTF_GetError());
      break;
    }
    SDL_Texture *Timer = SDL_CreateTextureFromSurface(renderer, TimerSurface);
    if (!Timer) {
      printf("CreateTextureFromSurface Error: %s\n", SDL_GetError());
      break;
    }

    // Создаем константу для определения клавиш
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_W] && destRectShip.y > 450) {
      destRectShip.y -= MOVE_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_S] && destRectShip.y < 700) {
      destRectShip.y += MOVE_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_A] && destRectShip.x > 0) {
      destRectShip.x -= MOVE_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_D] && destRectShip.x < 700) {
      destRectShip.x += MOVE_SPEED;
    }
    
    //Падение астероидов
    destRectFirAstr.y += MOVE_SPEED + 5;
    destRectFirAstr.x += randomnum;

    destRectSecAstr.y += MOVE_SPEED + 5;
    destRectSecAstr.x -= randomnum2;

    //Ограничение падения метеоритов
    if (destRectFirAstr.y > 800 || destRectFirAstr.x > 800) {
      destRectFirAstr.y = 0;
      destRectFirAstr.x = 0;
      randomnum = rand() % 10;
    }

    if (destRectSecAstr.y > 800 || destRectSecAstr.x > 800) {
      destRectSecAstr.y = 0;
      destRectSecAstr.x = 700;
      randomnum2 = rand() % 10;
    }


    if (flag == true) {
      destRectBonus.y += MOVE_SPEED;
      if (destRectBonus.y > 800) {
        flag = false;
        destRectBonus.y = -100;
      }
    }

    // Проверка на взятие бонуса
    bool checkBonus = checkCollision(destRectShip, destRectBonus);
    if (checkBonus) {
      if (strncmp(numBonus,"bomb",4) == 0) {
        shipLive -= 1;
        destRectBonus.y = -100;
      } else if (strncmp(numBonus,"heal",4) == 0 && shipLive < 3) {
        shipLive += 1;
        destRectBonus.y = -100;
      }
    }

    // Проверка на столкновение с астероидами и на кол-во жизней
    bool checkAstDTP = checkCollision(destRectShip, destRectFirAstr);
    bool checkAst2DTP = checkCollision(destRectShip, destRectSecAstr);
    if (shipLive == -1) {
      break;
    }
    if (checkAstDTP) {
      shipLive -= 1;
      destRectFirAstr.x = 0;
      destRectFirAstr.y = 0;
    }
    if (checkAst2DTP) {
      shipLive -= 1;
      destRectSecAstr.x = 800;
      destRectSecAstr.y = 800;
    }

    // Обновление экрана
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, bg, nullptr, &destRectBg);

    // Номер в переменной равен кол-во сердец на экранке
    switch (shipLive) {
    case 3:
      SDL_RenderCopy(renderer, first_live, nullptr, &lives_pos);
    case 2:
      SDL_RenderCopy(renderer, first_live, nullptr, &lives_pos2);
    case 1:
      SDL_RenderCopy(renderer, third_live, nullptr, &lives_pos3);
    }

    SDL_RenderCopy(renderer, bonus, nullptr, &destRectBonus);
    SDL_RenderCopy(renderer, Timer, nullptr, &destRectTimer);
    SDL_RenderCopy(renderer, ast, nullptr, &destRectFirAstr);
    SDL_RenderCopy(renderer, ast2, nullptr, &destRectSecAstr);
    SDL_RenderCopy(renderer, ship, nullptr, &destRectShip);

    SDL_RenderPresent(renderer);

    SDL_Delay(20);
  }
  
  //Завершение цикла: Записываем результат игрока, закрываем все текстуры и окна
  file << argv[1] << "Alive time: "<< counter << '\n';
  file.close();
  SDL_DestroyTexture(bonus);
  SDL_DestroyTexture(ast2);
  SDL_DestroyTexture(ast);
  SDL_DestroyTexture(bg);
  SDL_DestroyTexture(ship);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

// Инициализации базовых переменных(окна и рендера)
bool init(SDL_Window *&window, SDL_Renderer *&renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  return true;
}

// Функция для загрузки текстур и проверки их инициализации
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *renderer) {
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (!loadedSurface) {
    std::cerr << "Unable to load image! SDL_Error: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }

  SDL_Texture *newTexture =
      SDL_CreateTextureFromSurface(renderer, loadedSurface);

  SDL_FreeSurface(loadedSurface);

  if (!newTexture) {
    std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }

  return newTexture;
}

// Таймеры
Uint32 TimerCallback(Uint32 interval, void *param) {
  counter++;
  return interval;
}
Uint32 TimerCallback2(Uint32 interval, void *param) {
  destRectBonus = {rand() % 700,-100,50,50};
  return interval;
}

//Функция для проверки столкновения объектов
bool checkCollision(SDL_Rect obj1, SDL_Rect obj2) {
  return (obj1.x + 20 < obj2.x + obj2.w && obj1.x + obj1.w > obj2.x + 20 &&
          obj1.y + 60 < obj2.y + obj2.h && obj1.y + obj1.h > obj2.y + 60);
}
