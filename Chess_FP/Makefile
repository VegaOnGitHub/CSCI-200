# COMMENTS BEGIN WITH A HASH

# THE NAME OF YOUR PROJECT
PROJECT = Chess_FP

# SOURCES
CLI_SRC_FILES  = main.cpp board.cpp game.cpp piece.cpp
SFML_SRC_FILES = sfml_main.cpp board.cpp piece.cpp

# HEADERS
H_FILES = board.h game.h piece.h position.h

# ANY OTHER RESOURCES FILES THAT ARE PART OF THE PROJECT
REZ_FILES =

# YOUR USERNAME
USERNAME = Daniel_Vega

# SFML configuration (override on the command line if installed elsewhere)
SFML_LIB_DIR ?= /usr/local/lib
SFML_INC_DIR ?= /usr/local/include

# NO EDITS BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g
CXXFLAGS_WARN = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17
SFML_LIBS = -L$(SFML_LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system
SFML_RPATH = -Wl,-rpath,$(SFML_LIB_DIR)

CLI_OBJECTS  = $(CLI_SRC_FILES:.cpp=.o)
SFML_OBJECTS = $(SFML_SRC_FILES:.cpp=.o)

ARCHIVE_EXTENSION = zip

ifeq ($(shell echo "Windows"), "Windows")
	TARGET_CLI  = $(PROJECT)_cli.exe
	TARGET_SFML = $(PROJECT).exe
	DEL = del
	ZIPPER = tar -a -c -f
	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
	Q =
else
	TARGET_CLI  = $(PROJECT)_cli
	TARGET_SFML = $(PROJECT)
	DEL = rm -f
	ZIPPER = tar -acf
	Q= "

	ifeq ($(shell tar --version | grep -o "GNU tar"), GNU tar)
		ARCHIVE_EXTENSION = tar.gz
	endif

	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
endif

all: $(TARGET_CLI) $(TARGET_SFML)

$(TARGET_CLI): $(CLI_OBJECTS)
	$(CXX) -o $@ $^

$(TARGET_SFML): $(SFML_OBJECTS)
	$(CXX) -o $@ $^ $(SFML_LIBS) $(SFML_RPATH)

.cpp.o:
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -I$(SFML_INC_DIR) -o $@ -c $<

clean:
	$(DEL) $(TARGET_CLI) $(TARGET_SFML) $(CLI_OBJECTS) $(SFML_OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) $(CPPVERSION) -MM $(CLI_SRC_FILES) $(SFML_SRC_FILES) >> Makefile

submission:
	@echo "Creating submission file $(ZIP_NAME) ..."
	@echo "...Zipping source files:   $(CLI_SRC_FILES) $(SFML_SRC_FILES)..."
	@echo "...Zipping header files:   $(H_FILES) ..."
	@echo "...Zipping resource files: $(REZ_FILES)..."
	@echo "...Zipping Makefile..."
	$(ZIPPER) $(ZIP_NAME) $(CLI_SRC_FILES) $(SFML_SRC_FILES) $(H_FILES) $(REZ_FILES) Makefile
	@echo "...$(ZIP_NAME) done!"

.PHONY: all clean depend submission

# DEPENDENCIES
