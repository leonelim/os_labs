SRCS = $(wildcard *.c)
BINS = $(SRCS:.c=)

all:
	for file in $(SRCS); do \
		cc $$file -o $${file%.c}; \
	done
clean_fifo:
	for i in {2..9}; do \
		rm "1$${i}" "2$${i}"; \
	done
clean:
	rm 1 result.txt
