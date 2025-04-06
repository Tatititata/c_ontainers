override LDLIBS += -lgtest -lgtest_main -lpthread

TESTSRCS = $(wildcard *.cc)
TREE_TESTS = $(wildcard test_rb_tree*.cc)
MULTI_TESTS = $(wildcard multiset*.cc)
LIST_VECTOR_TESTS = $(wildcard test_list_vector*.cc)
SET_TESTS = $(wildcard set_*.cc)
LIST_TESTS = $(wildcard list_*.cc)

ifdef TREE_ONLY
    TESTSRCS = $(TREE_TESTS)
endif

ifdef MULTI_ONLY
    TESTSRCS = $(MULTI_TESTS)
endif

ifdef LIST_VECTOR_ONLY
    TESTSRCS = $(LIST_VECTOR_TESTS)
endif

ifdef SET_ONLY
    TESTSRCS = $(SET_TESTS)
endif

ifdef LIST_ONLY
    TESTSRCS = $(LIST_TESTS)
endif


TESTOBJS = $(TESTSRCS:.cc=.o) 

DEPS := $(TESTOBJS:.o=.d)

.PHONY: all clean run
NODEPS := clean

all: test run

run: test
	./test

test: $(TESTOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TESTOBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(DEPS): %.d: %.cc
	$(CXX) -E $(CPPFLAGS) $< -MM -MT $(@:.d=.o) > $@

clean:
	$(RM) test $(TESTOBJS) $(DEPS)

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS)
endif
