#pragma once
#include <sstream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "Filer.h"
#include "Chroma.h"
#include "Frame.h"

bool file_load_frame(std::string frame_name, glow::Frame &frame, std::string &message);
bool file_load_palette(std::string &message);
const std::string file_system_path();
bool file_system_exists(std::string data_path);
bool file_system_create(std::string data_path, std::string &message);
bool file_catalog_copy(std::vector<std::string> frame_names, std::string &message);
void file_catalog_list(std::vector<std::string> &frame_names);
void file_catalog_build(std::string &message);