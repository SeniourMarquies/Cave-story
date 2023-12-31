#pragma once
#include <cmath>
#include "config.hh"

namespace units {
    typedef int HP;

    typedef double Game; // intrinsic units of position
    typedef int Pixel;
    typedef unsigned int Tile;
    typedef double Degrees;

    typedef unsigned int Frame;

    typedef unsigned int FPS;
    typedef double Velocity;
    typedef double Acceleration;
    typedef double AngularVelocity; // Degrees / milliseconds

    namespace {
        const Game kTileSize{ 32.0 };
        const double kPi{ atan(1) * 4 };
    }

    inline double degreesToRadians(Degrees degrees) {
        return degrees * kPi / 180.0;
    }

    inline Game sin(Degrees degrees) {
        return static_cast<Game>(std::sin(degreesToRadians(degrees)));
    }

    inline Game cos(Degrees degrees) {
        return static_cast<Game>(std::cos(degreesToRadians(degrees)));
    }

    inline Pixel gameToPixel(Game game) {
        if (config::getGraphicsQuality() == config::GraphicsQuality::HIGH) {
            return Pixel(round(game));
        }
        else {
            return Pixel(round(game) / 2);
        }
    }
    inline Tile gameToTile(Game game) {
        return Tile(game / kTileSize);
    }
    inline Game tileToGame(Tile tile) {
        return tile * kTileSize;
    }
    inline Pixel tileToPixel(Tile tile) {
        return gameToPixel(tileToGame(tile));
    }

    const Game kHalfTile{ tileToGame(1) / 2.0 };
} // units