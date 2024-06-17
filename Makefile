# Makefile in the root directory

CXX = g++
CXXFLAGS = -Wall -std=c++14
SRCDIR = example
BUILDDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
EXECUTABLES = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%,$(SOURCES))

all: $(EXECUTABLES)

$(BUILDDIR)/%: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)
