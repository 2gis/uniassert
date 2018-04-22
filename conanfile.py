from conans import ConanFile, CMake


class UniassertConan(ConanFile):
    name = "uniassert"
    version = "1.0.0"
    license = "Zlib"
    url = "https://github.com/lagner/uniassert.git"
    description = "The uniassert library is a small collection of useful macros. Most of them are designed for assumption checks"
    settings = "os", "compiler", "build_type", "arch"
    build_requires = ('gtest/1.8.0@bincrafters/stable', )
    generators = "cmake"

    cmake = None

    def source(self):
        self.run("git clone --depth=1 -b conan --single-branch {} .".format(self.url))

    def build(self):
        self.cmake = CMake(self)
        args = ['-DUNIASSERT_TESTS=ON', ] if self.develop else None
        self.cmake.configure(args=args, source_dir=self.source_folder)
        self.cmake.build()
        self.cmake.build(target='test')

    def package(self):
        self.copy("*.h", dst="include", src="include")

    def package_info(self):
        pass
