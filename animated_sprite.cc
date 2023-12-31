#include "animated_sprite.hh"
#include "Game.hh"

animated_sprite::animated_sprite(Graphics& graphics, const std::string& file_name, const units::Pixel source_x, const units::Pixel source_y, const units::Pixel width, const units::Pixel height, const units::FPS fps, const units::Frame num_frames) : Sprite(graphics, file_name,source_x,source_y,width,height),
frame_timer_{std::chrono::milliseconds(1000/fps)},
num_frames_(num_frames),current_frame_(0)
{

}

animated_sprite::~animated_sprite()
{
}

void animated_sprite::update()
{
	if (frame_timer_.is_expired()) {
		++current_frame_;
		frame_timer_.reset();
		if (current_frame_ < num_frames_)
			source_rect.x += source_rect.w;
		else
		{
			source_rect.x -= source_rect.w * (num_frames_ - 1);
			current_frame_ = 0;
		}
	}
}
