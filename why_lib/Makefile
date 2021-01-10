compiler = gcc
debug_flags = -g -Wall -Wextra
release_flags = -O3 -Wall -Wextra
profile_flags = -g -pg -Wall -Wextra

# flags = $(debug_flags)
# flags = $(release_flags)
flags = $(profile_flags)

header_folder = headers
object_folder = objects
alg_folder = algorithms
basics_folder = basics
structures_folder = structures
utility_folder = utility

alg_source = $(notdir $(wildcard $(alg_folder)/*.c))
alg_objects = $(addprefix $(object_folder)/,$(alg_source:.c=.o))
basics_source = $(notdir $(wildcard $(basics_folder)/*.c))
basics_objects = $(addprefix $(object_folder)/,$(basics_source:.c=.o))
structure_source = $(notdir $(wildcard $(structures_folder)/*.c))
structure_objects = $(addprefix $(object_folder)/,$(structure_source:.c=.o))
utility_source = $(notdir $(wildcard $(utility_folder)/*.c))
utility_objects = $(addprefix $(object_folder)/,$(utility_source:.c=.o))

VPATH=alg_folder:basics_folder:structures_folder #does it even do anything?

all_source = $(alg_source) $(basics_source) $(structure_source) $(utility_source)
all_objects = $(all_source:.c=.o)
lib_header = why_lib.h
header_files = $(wildcard $(header_folder)/*.h)

target = why_lib.a
main_object = $(subst .c,.o,$(object_folder)/$(main_file))

.PHONY: all clean folder re

all: $(target)
# all:
# 	echo $(all_objects)

$(basics_objects) : $(@:.o=.c) $(header_files) $(lib_header)
	$(compiler) $(flags) -I $(header_folder) -I . $(subst $(object_folder),$(basics_folder),$(@:.o=.c)) -c -o $@

$(alg_objects) : $(@:.o=.c) $(header_files) $(lib_header)
	$(compiler) $(flags) -I $(header_folder) -I . $(subst $(object_folder),$(alg_folder),$(@:.o=.c)) -c -o $@

$(structure_objects) : $(@:.o=.c) $(header_files) $(lib_header)
	$(compiler) $(flags) -I $(header_folder) -I . $(subst $(object_folder),$(structures_folder),$(@:.o=.c)) -c -o $@

$(utility_objects) : $(@:.o=.c) $(header_files) $(lib_header)
	$(compiler) $(flags) -I $(header_folder) -I . $(subst $(object_folder),$(utility_folder),$(@:.o=.c)) -c -o $@

$(target): $(basics_objects) $(alg_objects) $(structure_objects) $(utility_objects) $(header_files) $(lib_header) | folder
	ar rcs $(target) $(addprefix $(object_folder)/,$(all_objects))

folder:
	mkdir -p $(object_folder)

clean:
	rm -f $(addprefix $(object_folder)/,$(all_objects))

fclean: clean
	rm -f $(target)

re: fclean all
