#include "Game.hh"
#include "rectangle.hh"
#include "Graphics.hh"
#include <stdexcept>

Graphics::Graphics() :
    window{ SDL_CreateWindow(
                "Cave Reconstructed",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                units::tileToPixel(Game::kScreenWidth),
                units::tileToPixel(Game::kScreenHeight),
                SDL_WINDOW_RESIZABLE
                ) },
    renderer{ SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE) },
    sprite_sheets_()
{
    if (window == nullptr) {
        throw std::runtime_error("SDL_CreateWindow");
    }
    if (renderer == nullptr) {
        throw std::runtime_error("SDL_CreateRenderer");
    }

    SDL_RenderSetLogicalSize(renderer, units::tileToPixel(Game::kScreenWidth),
        units::tileToPixel(Game::kScreenHeight));
}

Graphics::~Graphics()
{
    for (auto& kv : sprite_sheets_) {
        SDL_DestroyTexture(kv.second);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/**
 * Loads SDL_Texture from file_name into sprite cache (sprite_sheets_ map) and
 * returns it. If texture already presents in cache just returns it.
 */
SDL_Texture* Graphics::loadImage(const std::string& file_name,
    const bool black_is_transparent)
{
    // get file path.
    const std::string file_path{
        (config::getGraphicsQuality() == config::GraphicsQuality::HIGH)
            ? "content/original_graphics/" + file_name + ".pbm"
            : "content/" + file_name + ".bmp"
    };

    // if spritesheet not loaded
    if (sprite_sheets_.count(file_path) == 0) {
        SDL_Texture* t = { 0 };
            
        if (black_is_transparent) {
            SDL_Surface* surface = SDL_LoadBMP(file_path.c_str());
            if (surface == nullptr) {
                const auto warn_str = "Cannot load texture '" + file_path + "'!";
                throw std::runtime_error(warn_str);
            }

            const Uint32 black_color = SDL_MapRGB(surface->format, 0, 0, 0);
            SDL_SetColorKey(surface, SDL_TRUE, black_color);
            t = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
        /*else {
            t = IMG_Load(renderer, file_path.c_str());
           
        } 
        if (t == nullptr) {
            throw std::runtime_error("Cannot load texture!");
        }
        */
        sprite_sheets_[file_path] = t;
    }
    return sprite_sheets_[file_path];
}

void Graphics::renderTexture( SDL_Texture* tex, const SDL_Rect dst, const SDL_Rect* clip) const
{
    // Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer, tex, clip, &dst);
}

/**
 * Draw an SDL_Texture at some destination rect taking a clip of the
 * texture if desired
 */
void Graphics::renderTexture( SDL_Texture* tex, const int x, const int y, const SDL_Rect* clip) const
{
    SDL_Rect dst{ 0 };
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else {
        // Query the attributes of a texture.
        SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
    }
    renderTexture(tex, dst, clip);
}

void Graphics::flip() const
{
    SDL_RenderPresent(renderer);
}

void Graphics::clear() const
{
    SDL_RenderClear(renderer);
}