# -------------------------------------------------
# Name: Mitchell Adam, Ryan Shukla
# ID: 1528592, 1537980
# CMPUT 275, Winter 2018
#
# Final Project
# -------------------------------------------------

TARGET := ./pitcher

CC := g++
CFLAGS := -std=c++11 -g
# linker flags
LDFLAGS := -lsndfile

# Directory of cpp source code
SRCDIR := src
# Directory to put .o files
OBJDIR := obj

# Find all .cpp files to compile
SOURCES := $(shell find $(SRCDIR) -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f $(TARGET)
	-rm -f $(OBJDIR)/*.o
