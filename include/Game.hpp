#ifndef GAME_HPP
#define GAME_HPP

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
};

#endif // GAME_HPP