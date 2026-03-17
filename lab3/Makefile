all:
	for file in *.c; do \
		cc $$file -o $${file%.c}; \
	done
clean:
	for file in *.c; do \
		rm $${file%.c}; \
	done
.PHONY: all clean
