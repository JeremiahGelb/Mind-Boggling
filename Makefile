# I didn't write most of this. I adapted
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET ?= run.o
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -pedantic -Wall -Wextra -Weffc++

$(TARGET): $(OBJS)
	g++ $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

lint:
	docker build -t cpplint ./linting

	docker run -it -v $(PWD):/src cpplint sh -c "cd src && cpplint --recursive */*"
