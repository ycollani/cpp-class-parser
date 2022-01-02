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
	mkdir -p $(DESTDIR)/include/rcl-genmsg
	$(CP) -au src/rcl-genmsg/*.h $(DESTDIR)/include/rcl-genmsg
	#cd $(DESTDIR); tar -czf ../rcl-genmsg-compiled.tgz lib/librcl-genmsg.so include/rcl-genmsg

