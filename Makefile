xdump:
	gcc -Iinclude -Wall src/xdump.c src/main.c -o xdump

clean:
	rm -rf xdump