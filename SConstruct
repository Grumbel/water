env = Environment(CXXFLAGS=["-Wall", "-Wno-narrowing"])
env.ParseConfig("pkg-config --libs --cflags gl glu")
env.Append(LIBS=["-lglut"])
env.Program("water", ["water.cpp"])

# EOF #
