#pragma once

#include "sprite.hh"
#include "units.hh"
#include "timer.hh"

struct animated_sprite :public Sprite {
	animated_sprite(
        Graphics& graphics,
        const std::string& file_name,
        const units::Pixel source_x, const units::Pixel source_y,
        const units::Pixel width, const units::Pixel height,
        const units::FPS fps, const units::Frame num_frames);


    ~animated_sprite();

    void update() override;

private:
    Timer frame_timer_;
    const units::Frame num_frames_;
    units::Frame current_frame_;

};



