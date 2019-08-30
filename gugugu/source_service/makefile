CCFLAG = -lpthread
service:service.o connect.o
	gcc $^ $(CCFLAG) -o $@
connect.o:../lib/connect.c
	gcc -c $< $(CCFLAG) -o $@
.c.o:
	gcc -c $< $(CCFLAG) -o $@
ALL:service
clean:ALL
	rm -f *.o
install:clean
	mv service ../bin/
