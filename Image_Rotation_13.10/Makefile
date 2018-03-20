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

$(BUILDDIR)/imageRotator: $(OBJS)
	$(LD) $^ -o $@
	
$(OBJS) : $(OBJDIR)/%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY:
	clean
	
clean:
	rm -f build/* \
	rm -f obj/* 