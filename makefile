CXXFLAGS += -std=c++11 -Ofast
# CXXFLAGS += -std=c++11

app : main.o clock.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^
main.o : main.cpp
clock.o : clock.cpp

.PHONY : clean
clean :
	rm *.o app
