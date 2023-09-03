#include "sprite.hh"
#include "Graphics.hh"

Sprite::Sprite(Graphics& graphics, const std::string& file_name, const units::Pixel source_x, const units::Pixel source_y, const units::Pixel width, const units::Pixel height) : texture {graphics.loadImage(file_name.c_str(), true)}, source_rect{source_x,source_y, width, height}
{

}

void Sprite::draw(Graphics& graphics, const Vector<units::Game>& pos) const
{
	const units::Pixel dstx = units::gameToPixel(pos.x);
	const units::Pixel dsty = units::gameToPixel(pos.y);

	graphics.renderTexture(texture, dstx, dsty, &source_rect);
}
