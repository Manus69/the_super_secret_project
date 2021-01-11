compiler = gcc
debug_flags = -g -Wall -Wextra
release_flags = -O3 -Wall -Wextra
profile_flags = -g -pg -Wall -Wextra

flags = $(debug_flags)
# flags = $(release_flags)
# flags = $(profile_flags)

full_path = $(CURDIR)/why_lib
directory = why_lib

lib_name = why_lib.a
executable = driver
driver_file = driver.c

all: executable

$(driver_file:.c=.o): $(driver_file)
	$(compiler) $(flags) -I $(directory) $(driver_file) -c -o $(driver_file:.c=.o)

executable: $(driver_file:.c=.o)
	make flags=$(flags) -C $(directory)
	$(compiler) $(flags) -o $(executable) -I ./$(directory) -L ./$(directory) $(driver_file:.c=.o) $(addprefix $(full_path)/,$(lib_name))

clean:
	rm -f $(driver_file:.c=.o)
	rm -f $(executable)
	rm -f *.out

cpp: test.cpp
	g++ -O3 test.cpp

re: clean
	make fclean -C $(directory)
	make all