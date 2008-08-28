# Make file for 
#  guduz :  Yet another RED simulator (YaREDs)
#  Last Revised: October 2006  (M)
#     Mehmet Suzen  <mehmet.suzen@physics.org>  (M) 
#     Ziya Suzen  <zsuzen@acm.org>              (Z)
#
GCC=gcc
# ANSI=-ansi
ANSI=
red:
	#$(GCC) -g $(ANSI) -Wall red.c -lm -lefence -o ../bin/red
	$(GCC) -g $(ANSI) -Wall red.c -lm -o ../bin/red
clean:
	rm -f ../bin/red
	rm -f ../bin/red_me
red_me:
	# $(GCC) -g $(ANSI) -Wall red_me.c -lm -lefence -o ../bin/red_me
	$(GCC) -g $(ANSI) -Wall red_me.c -lm -o ../bin/red_me
all:
	# $(GCC) -g $(ANSI) -Wall red_me.c -lm -lefence -o ../bin/red_me
	$(GCC) -g $(ANSI) -Wall red_me.c -lm -o ../bin/red_me
	# $(GCC) -g $(ANSI) -Wall red.c -lm -lefence -o ../bin/red
	$(GCC) -g $(ANSI) -Wall red.c -lm  -o ../bin/red
