#pragma once

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <catch2/catch_all.hpp>
#include <yaml-cpp/yaml.h>

template <typename GLOW_STRUCT>
void test_yaml_from_struct(
    const GLOW_STRUCT &glow_struct,
    void (*check_detail)(const GLOW_STRUCT &a, const GLOW_STRUCT &b))
{
  std::cout << '\n'
            << "YAML from struct" << '\n';

  YAML::Node node = YAML::convert<GLOW_STRUCT>::encode(glow_struct);
  YAML::Emitter out;
  out << node;
  std::cout << out.c_str() << '\n';

  GLOW_STRUCT from_node;
  YAML::convert<GLOW_STRUCT>::decode(node, from_node);
  check_detail(glow_struct, from_node);
}

template <typename GLOW_STRUCT>
void test_yaml_from_input(
    const GLOW_STRUCT &glow_struct,
    std::string input,
    void (*check_detail)(const GLOW_STRUCT &a, const GLOW_STRUCT &b))
{
  std::cout << '\n'
            << "YAML from input" << '\n';

  YAML::Node input_node = YAML::Load(input);
  GLOW_STRUCT from_input;
  YAML::convert<GLOW_STRUCT>::decode(input_node, from_input);

  YAML::Emitter out;
  out << input_node;
  std::cout << out.c_str() << '\n';

  YAML::Node from_node = YAML::convert<GLOW_STRUCT>::encode(from_input);
  YAML::Emitter out_a;
  out_a << from_node;
  std::cout << out_a.c_str() << '\n';
  check_detail(glow_struct, from_input);
}

template <typename GLOW_STRUCT>
void test_yaml_from_file(const GLOW_STRUCT &glow_struct, std::string file_name,
                         void (*check_detail)(const GLOW_STRUCT &a, const GLOW_STRUCT &b))
{
  YAML::Node input_node = YAML::LoadFile(file_name);
  GLOW_STRUCT from_input;
  YAML::convert<GLOW_STRUCT>::decode(input_node, from_input);

  YAML::Emitter out;
  out << input_node;
  std::cout << out.c_str() << '\n';

  YAML::Node from_node = YAML::convert<GLOW_STRUCT>::encode(from_input);
  YAML::Emitter out_a;
  out_a << from_node;
  std::cout << out_a.c_str() << '\n';
  check_detail(glow_struct, from_input);
}

template <typename GLOW_STRUCT>
void test_yaml(const GLOW_STRUCT &glow_struct, std::string input,
               void (*check_detail)(const GLOW_STRUCT &a, const GLOW_STRUCT &b))
{
  test_yaml_from_struct(glow_struct, check_detail);
  test_yaml_from_input(glow_struct, input, check_detail);
}
