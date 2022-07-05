.PHONY: build
build: clean
	gcc -o local_ip local_ip.c

.PHONY: clean
clean:
	rm -f a.out local_ip
