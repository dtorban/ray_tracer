CXX := g++

CXXFLAGS := -Wall -g -Wno-sign-compare

OBJ := main.o parser.o sphere.o light.o texture.o mesh.o triangle.o

ray_trace: $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Nicked from http://www.gnu.org/software/make/manual/make.html#Automatic-Prerequisites
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< -o $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o: ,g' < $@.tmp > $@; \
	rm -f $@.tmp

-include $(OBJ:.o=.d)

clean:
	rm -f *.o *.d ray_trace
