CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

CXXFLAGS += -fsanitize=address,undefined -g
LDFLAGS += -fsanitize=address,undefined

ifeq ($(filter gcov_report,$(MAKECMDGOALS)),gcov_report)
    CXXFLAGS += -g0 -O0 --coverage
    LDFLAGS += --coverage
endif

RM = rm -rf

export CXX CXXFLAGS CPPFLAGS LDFLAGS LDLIBS

.PHONY: all clean unit_test gcov_report

a.out: main.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

streetlights: streetlights.cc
	$(CXX) $(CXXFLAGS) -o a.out $^ $(LDFLAGS)

all: test 

test: unit_test

unit_test: 
	$(MAKE) -C unit_tests/ run

tree_test:
	$(MAKE) -C unit_tests/ TREE_ONLY=1 run
	
multiset_test:
	$(MAKE) -C unit_tests/ MULTI_ONLY=1 run

lv_test:
	$(MAKE) -C unit_tests/ LIST_VECTOR_ONLY=1 run

set_test:
	$(MAKE) -C unit_tests/ SET_ONLY=1 run

list_test:
	$(MAKE) -C unit_tests/ LIST_ONLY=1 run

gcov_report: clean test
	@mkdir -p report
	gcovr --root . --exclude 'unit_tests/.*' -o report/gcov_report.html --html-details --html-self-contained
	$(MAKE) clean_without_coverage

clang-format:
	clang-format -i $(wildcard *.cc) $(wildcard *.h) $(wildcard */*.cc) $(wildcard */*.h)

clean: clean_without_coverage
	$(RM) report

clean_without_coverage:
	$(RM) unit_tests/*.gcda unit_tests/*.gcno 
	$(MAKE) -C unit_tests/ clean 
	$(RM) *.out

