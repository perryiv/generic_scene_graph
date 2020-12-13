from conans import CMake, CMakeToolchain, ConanFile, tools
import os


class GenericSceneGraph(ConanFile):
    name = "generic_scene_graph"
    license = "MIT"
    author = "Perry L Miller IV (perry@modelspace.com)"
    url = "https://github.com/perryiv/generic_scene_graph"
    description = "A scene graph decoupled from the rendering engine"
    topics = "OpenGL", "Vulkan", "C++", "Scene Graph"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "run_tests": [True, False],
    }
    default_options = {"shared": False, "run_tests": True}

    scm = {"type": "git", "url": "auto", "revision": "auto"}
    revision_mode = "scm"
    requires = (
        "boost/1.71.0",
        "usul/3.5.4@perryiv/stable"
    )

    no_copy_source = True
    generators = "cmake_find_package",

    def set_version(self):
        with open ( os.path.join ( self.recipe_folder, "version.txt" ) ) as file:
            self.version = file.read()

    def requirements(self):
        if self.options.run_tests:
            self.requires("catch2/2.13.1", private=True)

    def toolchain(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["GSG_BUILD_TESTS"] = self.options.run_tests
        toolchain.variables["GSG_ENABLE_CODE_COVERAGE"] = False
        toolchain.variables["CMAKE_DEBUG_POSTFIX"] = ""
        toolchain.variables["CMAKE_VERBOSE_MAKEFILE"] = True
        toolchain.write_toolchain_files()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.options.run_tests:
            with tools.run_environment(self):
                cmake.test(output_on_failure=True)

    def package(self):
        cmake = CMake(self)
        cmake.install()
        self.copy(pattern="License.md", dst="licenses")

    def package_info(self):
        self.cpp_info.libs = ["generic_scene_graph"]
        if not self.options.shared:
            self.cpp_info.defines = ["GSG_STATIC_DEFINE"]
        if not self.in_local_cache:
            self.cpp_info.includedirs = [
                "source",
                os.path.join("build", self.settings.build_type.value, "config")
            ]

    def package_id(self):
        del self.info.options.run_tests
