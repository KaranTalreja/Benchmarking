SUBDIRS = IO
OUT = lib/libUtils.a

.PHONY: subdirs $(SUBDIRS)
$(OUT) : subdirs
	@echo "Building Library libUtils.a"
	@mkdir -p lib
	@ar rcs lib/libUtils.a IO/obj/IO.o

subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	$(MAKE) -C $@