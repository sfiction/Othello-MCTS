CC=g++
CPPFLAGS=-Wall -O2 -std=c++14
INCLUDEFLAGS=
LDFLAGS=
OBJS=chessboard.o player.o round.o main.o
TARGETS=Othello

.PHONY: all
all: $(TARGETS)

Othello: $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CC) $(CPPFLAGS) -o $@ -c $< $(INCLUDEFLAGS)

%.d: %.cc
	@set -e; rm -f $@; $(CC) $(CPPFLAGS) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(OBJS:.o=.d)

.PHONY: clean 
clean:
	rm -f $(TARGETS) *.o *.d *.d.*
