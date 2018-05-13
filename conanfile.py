import os
from conans import ConanFile, CMake, tools


class UniassertConan(ConanFile):
    name = "uniassert"
    version = "1.0.0"
    license = "Zlib"
    url = "https://github.com/2gis/uniassert.git"
    description = "The uniassert library is a small collection of useful macros. Most of them are designed for assumption checks"
    settings = "os", "compiler", "build_type", "arch"
    build_requires = ('gtest/1.8.0@bincrafters/stable', )
    generators = "cmake"

    branch = 'master'

    def source(self):
        url = 'https://github.com/2gis/uniassert/archive/{}.zip'.format(self.branch)
        tools.download(url, self.branch)
        tools.unzip(self.branch)
        os.remove(self.branch)

    def build(self):
        cmake = CMake(self)
        configure_args = {
            'args': ['-DUNIASSERT_TESTS=ON', ] if self.develop else None,
            'source_dir': self.source_subdir(),
        }
        cmake.configure(**configure_args)
        cmake.build()
        cmake.test()

    def package(self):
        src = os.path.join(self.source_subdir(), 'include')
        self.copy("*.h", dst="include", src=src)

    def package_id(self):
        self.info.header_only()

    def source_subdir(self):
        subdir = '{}-{}'.format(self.name, self.branch)
        return os.path.join(self.source_folder, subdir)
