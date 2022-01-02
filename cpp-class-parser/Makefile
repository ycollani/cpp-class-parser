
all: lib share
	$(MAKE) -C src all

bin share lib:
	mkdir -p $@

.PHONY: clean verylcean distclean cleandepend  
clean veryclean distclean cleandepend:
	$(MAKE) -C src $@
	rm -f lib/* bin/*

install: all
	$(CP) -au lib $(DESTDIR)
	mkdir -p $(DESTDIR)/include/cpp-class-parser
	$(CP) -au src/cpp-class-parser/*.h $(DESTDIR)/include/cpp-class-parser
	#cd $(DESTDIR); tar -czf ../rcl-genmsg-compiled.tgz lib/librcl-genmsg.so include/rcl-genmsg

