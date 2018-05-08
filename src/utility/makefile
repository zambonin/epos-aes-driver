# EPOS Utilities Makefile

include ../../makedefs

SUBDIRS := aes

all:		$(SUBDIRS) $(LIBUTIL)

$(SUBDIRS):	FORCE
		(cd $@ && $(MAKE))

FORCE:

OBJS := $(subst .cc,.o,$(shell find *.cc | grep -v test))

$(LIBUTIL):	$(LIBUTIL)($(OBJS))

clean:
		make MAKE:="$(MAKECLEAN)" $(SUBDIRS)
		$(CLEAN) *.o *_test
