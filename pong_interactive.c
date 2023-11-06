#include <ncurses.h>
#include <stdio.h>

void fieldView(int ball_x, int ball_y, int player1_y, int player2_y, int score1,
               int score2);
int ballStepX(int ball_x, int ball_y, int step_x, int player1_y, int player2_y);
int ballStepY(int ball_x, int ball_y, int step_y, int player1_y, int player2_y);
int player1Inp(int player1_y, char key);
int player2Inp(int player2_y, char key);
void showWinner(int score1, int score2);

int main() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  int height = 25;
  int width = 80;
  int ball_x = width / 2;
  int ball_y = height / 2;
  int player1_y = height / 2;
  int player2_y = height / 2;
  int step_x = 1;
  int step_y = 1;
  int score1 = 0;
  int score2 = 0;

  while (score1 != 21 && score2 != 21) {
    clear();
    fieldView(ball_x, ball_y, player1_y, player2_y, score1, score2);
    refresh();
    char key;
    key = getch();

    if (key == '\n') {
      continue;
    }
    if (key == 'r') {
      ball_x = width / 2;
      ball_y = height / 2;
      player1_y = height / 2;
      player2_y = height / 2;
      step_x = 1;
      step_y = 1;
      score1 = 0;
      score2 = 0;
      continue;
    }
    player1_y = player1Inp(player1_y, key);
    player2_y = player2Inp(player2_y, key);
    ball_x += step_x;
    ball_y += step_y;
    step_x = ballStepX(ball_x, ball_y, step_x, player1_y, player2_y);
    step_y = ballStepY(ball_x, ball_y, step_y, player1_y, player2_y);
    if (ball_x == width + 1) {
      score1++;
      ball_x = width / 2;
      ball_y = height / 2;
      step_x *= -1;
    } else if (ball_x == 0) {
      score2++;
      ball_x = width / 2;
      ball_y = height / 2;
      step_x *= -1;
    }
    napms(75);
  }
  clear();
  move(0, 0);

  showWinner(score1, score2);
  refresh();
  while (getchar() != 'n')
    ;
  endwin();
  return 0;
}

void fieldView(int ball_x, int ball_y, int player1_y, int player2_y, int score1,
               int score2) {
  printw("Score: Player 1 - %d | Player 2 - %d\n", score1, score2);
  int height = 25;
  int width = 80;
  for (int y = 0; y < height + 2; y++) {
    for (int x = 0; x < width + 2; x++) {
      if (x == 0 || x == width + 1) {
        printw("|");
        continue;
      } else if (y == 0 || y == height + 1) {
        printw("=");
        continue;
      } else if (x == ball_x && y == ball_y) {
        printw("@");
        continue;
      } else if ((y == player1_y || y == player1_y + 1 || y == player1_y + 2) &&
                 x == 2) {
        printw("]");
      } else if ((y == player2_y || y == player2_y + 1 || y == player2_y + 2) &&
                 x == width - 1) {
        printw("[");
      } else if (x == width / 2) {
        printw("|");
      } else {
        printw(" ");
      }
    }
    printw("\n");
  }
}

int ballStepX(int ball_x, int ball_y, int step_x, int player1_y,
              int player2_y) {
  int width = 80;

  if ((ball_y == player1_y || ball_y == player1_y + 1 ||
       ball_y == player1_y + 2) &&
      ball_x == 3) {
    step_x *= -1;
  } else if ((ball_y == player2_y || ball_y == player2_y + 1 ||
              ball_y == player2_y + 2) &&
             ball_x == width - 2) {
    step_x *= -1;
  }
  return step_x;
}

int ballStepY(int ball_x, int ball_y, int step_y, int player1_y,
              int player2_y) {
  int height = 25;

  if (ball_y == 1 || ball_y == height) {
    step_y *= -1;
  }
  return step_y;
}

int player1Inp(int player1_y, char key) {
  int height = 25;
  if (key == 'a' && player1_y > 1) {
    player1_y -= 1;
  } else if (key == 'z' && player1_y < height - 2) {
    player1_y += 1;
  }

  return player1_y;
}

int player2Inp(int player2_y, char key) {
  int height = 25;
  if (key == 'k' && player2_y > 1) {
    player2_y -= 1;
  } else if (key == 'm' && player2_y < height - 2) {
    player2_y += 1;
  }
  return player2_y;
}

void showWinner(int score1, int score2) {
  if (score1 == 21) {
    printw("    ____  __                         ___            _            "
           "__\n");
    printw("   / __ \\/ /___ ___  _____  _____   <  /  _      __(_)___  _____/ "
           "/\n");
    printw("  / /_/ / / __ `/ / / / _ \\/ ___/   / /  | | /| / / / __ \\/ ___/ "
           "/ \n");
    printw(" / ____/ / /_/ / /_/ /  __/ /      / /   | |/ |/ / / / / (__  )_/  "
           "\n");
    printw("/_/   /_/\\__,_/\\__, /\\___/_/      /_/    |__/|__/_/_/ "
           "/_/____(_)   \n");
    printw("              /____/                                               "
           "\n");
  } else if (score2 == 21) {
    printw("    ____  __                         ___               _           "
           " __\n");
    printw("   / __ \\/ /___ ___  _____  _____   |__ \\    _      __(_)___  "
           "_____/ /\n");
    printw("  / /_/ / / __ `/ / / / _ \\/ ___/   __/ /   | | /| / / / __ \\/ "
           "___/ / \n");
    printw(" / ____/ / /_/ / /_/ /  __/ /      / __/    | |/ |/ / / / / (__  "
           ")_/  \n");
    printw("/_/   /_/\\__,_/\\__, /\\___/_/      /____/    |__/|__/_/_/ "
           "/_/____(_)   \n");
    printw("              /____/                                               "
           "   \n");
  }
}
