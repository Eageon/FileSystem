# Author Jun Yu

EXECUTABLE := faccess
LIBS :=
CC := gcc
LD := ld

DEBUG_MODE := n

ifeq ($(DEBUG_MODE), y)
        DEBUG := -g
        MACRO := -D__DEBUG__
else
        DEBUG :=
        MACRO :=
endif

LIB += -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/i386-linux-gnu/ -lpthread
CFLAGS := $(DEBUG) $(MACRO) -Wall
CXXFLAGS := $(CFLAGS)
LDFLAGS := $(DEBUG) $(LIB)

RM-F := rm -f

SOURCE := $(wildcard *.c) $(wildcard *.cc)
OBJS := $(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(SOURCE)))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.c,$(MISSING_DEPS)) $(patsubst %.d,%.cc,$(MISSING_DEPS)))
CPPFLAGS += -MD

.PHONY : everything deps objs clean veryclean rebuild

everything : $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean everything

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %.d,%.o,$@)
endif

-include $(DEPS)

$(EXECUTABLE) : $(OBJS)
	gcc -o $(EXECUTABLE) $(OBJS) $(addprefix -l,$(LIBS))
