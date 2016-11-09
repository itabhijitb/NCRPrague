#-----------------------------------------------------------------------
# Module Name
#-----------------------------------------------------------------------
MODULE=DeDup
#-----------------------------------------------------------------------
#  Input Files
#-----------------------------------------------------------------------
SRCS=$(wildcard *.cpp)
OBJS = $(patsubst %,$(OBJDIR)/%,$(subst .cpp,.obj,$(SRCS)))

#-----------------------------------------------------------------------
# Determine appropiate platform specific GNUmakefile
#-----------------------------------------------------------------------

ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS=all
endif
ifneq ($(filter-out run clean dist-clean,$(MAKECMDGOALS)),)
ifndef PLATFORM
$(error PLATFORM is not set)
endif
PLATFORM:=$(shell echo $(PLATFORM) | tr A-Z a-z)
include GNUmakefile.$(PLATFORM)
endif

#-----------------------------------------------------------------------
#  Output location
#-----------------------------------------------------------------------
OBJDIR=build$(PLATFORM)$(BITNESS)




.PHONY: all

all: $(OBJDIR) $(OBJDIR)/$(MODULE)


$(OBJS) : $(SRCS)
	$(CXX) $< $(CPPFLAGS)$@

$(OBJDIR)/$(MODULE):$(OBJS)
	$(LINK) $(OBJS) $(LDFLAGS) 

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)/*

dist-clean: clean
	$(RM) *~ .depend
	
run:
	$(OBJDIR)/$(MODULE)
