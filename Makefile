NAME = libmemprof.so
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -O2 -I includes
LDFLAGS = -shared -ldl
SRCS = src/hooks.c src/malloc_hook.c src/free_hook.c src/calloc_hook.c \
       src/realloc_hook.c src/tracking.c src/tracking_ops.c src/hashtable.c \
       src/hashtable_ops.c src/hashtable_utils.c src/backtrace.c \
       src/leak_detector.c src/leak_detector_ops.c src/leak_detector_print.c \
       src/report.c src/report_text.c src/report_text_stats.c \
       src/report_json.c src/report_csv.c src/signals.c src/filter.c \
       src/compare.c src/compare_ops.c src/memory_utils.c src/string_utils.c \
       src/list.c src/init.c
OBJS = $(SRCS:.c=.o)
HEADERS = includes/memory_profiler.h includes/tracking.h includes/hooks.h \
          includes/report.h includes/hashtable.h includes/backtrace.h \
          includes/leak_detector.h includes/signals.h includes/filter.h \
          includes/compare.h includes/utils.h

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)
	@echo "Memory Profiler library created."

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<"

clean:
	@rm -f $(OBJS)
	@echo "Objects removed."

fclean: clean
	@rm -f $(NAME)
	@echo "Library removed."

re: fclean all

.PHONY: all clean fclean re
