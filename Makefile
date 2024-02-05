CC = gcc
CFLAGS = -Wall -Wextra

use_example: use_example.c
	$(CC) $(CFLAGS) $< -o /tmp/clogin_use_example && /tmp/clogin_use_example

tests: tests/main.c
	$(CC) $(CFLAGS) $< -o /tmp/clogin_tests && /tmp/clogin_tests < ./tests/in

.PHONY: clean

clean:
	rm -f /tmp/clogin_use_example /tmp/clogin_tests
