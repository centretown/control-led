from conan import ConanFile


class GlowRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("yaml-cpp/0.7.0")
        self.requires("nlohmann_json/3.11.2")
        self.requires("cxxopts/3.0.0")
        self.test_requires("catch2/3.3.2")
