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

    def source(self):
        self.run("git clone --depth=1 -b conan --single-branch {} .".format(self.url))

    def build(self):
        cmake = CMake(self)
        configure_args = {
            'args': ['-DUNIASSERT_TESTS=ON', ] if self.develop else None,
        }
        cmake.configure(**configure_args)
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="include")

    def package_id(self):
        self.info.header_only()
