prefix = /usr/local


all:src/laplace

src/laplace: src/laplace.c
	@echo "CFLAGS= $(CFLAGS)" | \
		fold -s -w 70 | \
		sed -e 's/^/# /'

	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDCFLAGS) -o $@ $^ -lm

install: src/laplace
	install -D src/laplace \
		$(DESTDIR)$(prefix)/bin/laplace

clean: 
	-rm -f src/laplace

distclean: clean

unistall: 
	-rm -f $(DISTDIR)$(prefix)/bin/laplace

	    
 

