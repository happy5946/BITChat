CCFLAG = -lpthread
guest:guest.o connect.o
	gcc $^ $(CCFLAG) -o $@
connect.o:../lib/connect.c
	gcc -c $< $(CCFLAG) -o $@
.c.o:
	gcc -c $< $(CCFLAG) -o $@
ALL:guest
clean:ALL
	rm -f *.o
install:clean
	mv guest ../bin/
