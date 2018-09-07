TARGETNAME	:= main
TARGETTYPE	:= APP

CC	:=	$(CROSS_COMPLIER)gcc
CXX	:=	$(CROSS_COMPLIER)g++
LD	:=	$(CXX)
AR	:=	$(CROSS_COMPLIER)ar
OBJCOPY	:=	$(CROSS_COMPLIER)objcopy

CFLAGS	= -Wall -O0 -g
CXXFLAGS	=
LDFLAGS	=
ARFLAGS	=
INCLUDE_DIRS	=	include
LIBRARY_DIRS	=	lib
LIBTYPE	:= 
LIBRARY_NAMES	=	
BINARYDIR	:=	Debug
SRCDIR	:=	src

PRIMARY_OUTPUTS	:= $(BINARYDIR)/$(TARGETNAME)
SOURCEFILES	:= main.c
all_objs	= $(all_make_files:src/%.c=$(BINARYDIR)/%.o)
all_make_files	:= $(addprefix $(SRCDIR)/, $(SOURCEFILES))

CFLAGS	+= $(addprefix -,$(LIBTYPE))
CFLAGS	+= $(addprefix -I,$(INCLUDE_DIRS))
LIBRARY_LDFLAGS	= $(addprefix -l,$(LIBRARY_NAMES))
LDFLAGS	+= $(addprefix -L,$(LIBRARY_DIRS))

all:mkdir do_all $(PRIMARY_OUTPUTS)
mkdir:
	@mkdir $(BINARYDIR) -p
.PHONY:mkdir
do_all:$(all_objs)
$(all_objs):$(BINARYDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(@:.o=.dep)
$(BINARYDIR)/$(TARGETNAME):$(all_objs)
	$(CC) -o $@ $(LDFLAGS) $(all_objs) $(LIBRARY_LDFLAGS)
.PHONY:do_all all

clean:
	$(RM) -r $(BINARYDIR)
.PHONY:clean

