#pragma once

#include <thread>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include "glow_file.h"
#include "Frame.h"
#include "ansi_stream.h"
#include "HostLight.h"

bool show_lights(uint16_t length, uint16_t rows, uint32_t interval,
                 std::string frame_name, std::string &message);
void show_palette(uint16_t columns = 5, uint16_t column_width = 26, bool by_hue = true);
void show_frame(glow::Frame &frame);
void show_normal();
