CC = cc
CFLAGS = -Wall -pedantic-errors -Werror -ggdb
LD = gcc

BUILDDIR = build
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, main.o)
HEADERS = 

vpath %.c src
vpath %.h src
	
all: $(BUILDDIR)/imageRotator

$(BUILDDIR)/imageRotator: $(OBJS) | $(BUILDDIR)
	$(LD) $^ -o $@
	
$(OBJS) : $(OBJDIR)/%.o : %.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
 
$(OBJDIR):
	mkdir $(OBJDIR)
	
$(BUILDDIR):
	mkdir $(BUILDDIR)
	
.PHONY:
	clean
	
clean:
	rm -f build/* \
	rm -f obj/* 