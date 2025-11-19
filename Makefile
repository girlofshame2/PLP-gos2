CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# Source files
SOURCES = matrix.c unity.c
TEST_SOURCES = basic-test-suite.c
OBJECTS = $(SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Executables
TEST_EXEC = test_matrix
ADVANCED_TEST_EXEC = test_matrix_advanced
ROBUSTNESS_TEST_EXEC = test_matrix_robustness

# Targets
.PHONY: all clean test test-advanced test-robustness test-all

all: $(TEST_EXEC)

$(TEST_EXEC): basic-test-suite.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(ADVANCED_TEST_EXEC): advanced-test-suite.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(ROBUSTNESS_TEST_EXEC): robustness-test-suite.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

test-advanced: $(ADVANCED_TEST_EXEC)
	./$(ADVANCED_TEST_EXEC)

test-robustness: $(ROBUSTNESS_TEST_EXEC)
	./$(ROBUSTNESS_TEST_EXEC)

test-all: test test-advanced test-robustness
	@echo "======================================"
	@echo "All test suites passed!"
	@echo "======================================"

clean:
	rm -f *.o $(TEST_EXEC) $(ADVANCED_TEST_EXEC) $(ROBUSTNESS_TEST_EXEC)

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all      - Build the test executable (default)"
	@echo "  test     - Build and run the test suite"
	@echo "  clean    - Remove object files and executables"
	@echo "  help     - Show this help message"
