env = Environment(CXXFLAGS=["-Wall", "-Wno-narrowing", "-std=c++11"])
env.ParseConfig("pkg-config --libs --cflags gl glu")
env.Append(LIBS=["-lglut"])
env.Program("water", ["water.cpp"])

# EOF #
