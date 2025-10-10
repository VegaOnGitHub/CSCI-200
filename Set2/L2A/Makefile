# COMMENTS BEGIN WITH A HASH

# THE NAME OF YOUR PROJECT
PROJECT = L2A
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp
# YOUR USERNAME
USERNAME = Daniel_Vega

# NO EDITS BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g
CXXFLAGS_WARN = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ARCHIVE_EXTENSION = zip

ifeq ($(shell echo "Windows"), "Windows")
	TARGET = $(PROJECT).exe
	DEL = del
	ZIPPER = tar -a -c -f
	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
else
	TARGET = $(PROJECT)
	DEL = rm -f
	ZIPPER = tar -acf

	ifeq ($(shell tar --version | grep -o "GNU tar"), GNU tar)
		ARCHIVE_EXTENSION = tar.gz
	endif

	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

submission:
	@echo "Creating submission file $(ZIP_NAME) ..."
	@echo "...Zipping source files:   $(SRC_FILES)..."
	@echo "...Zipping Makefile..."
	$(ZIPPER) $(ZIP_NAME) $(SRC_FILES) Makefile
	@echo "...$(ZIP_NAME) done!"

.PHONY: all clean submission
