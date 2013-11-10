water : water2.cxx Makefile
	$(CXX) -o $@ $< -L/usr/X11R6/lib/ -lglut -Wall -Wno-narrowing -lGL -lGLU

# EOF #
