#pragma once

#include <chrono>
#include "Graphics.hh"


struct Game {
    Game();
    ~Game();

    static units::Tile kScreenWidth;
    static units::Tile kScreenHeight;

private:
    void runEventLoop();
    void update(const std::chrono::milliseconds elapsed_time, Graphics& graphics);
    void draw(Graphics& graphics) const;


    Graphics graphics_;
  
};

