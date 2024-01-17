# Remove the '#' in line 3 if you want to check for memory leaks
CPPFLAGS = -std=c++11 
# CPPFLAGS = -std=c++11 -g -fsanitize=address,leak,undefined
SRCS = main.cpp array.cpp dictionary.cpp item.cpp match.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

ifeq (Windows_NT, $(OS))
RM_CMD := del /F
else
RM_CMD := rm -vf
endif

ZIP_CMD := zip

all: pa2.exe

pa2.exe: $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

# Use make zinc to create the zip file for submission
zinc: dictionary.cpp item.cpp array.cpp match.cpp
	$(ZIP_CMD) pa2.zip $^ 

clean:
	$(RM_CMD) *.o pa2.exe *.d pa2.zip
