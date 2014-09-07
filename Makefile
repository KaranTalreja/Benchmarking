SUBDIRS = GraphClustering Utils

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	$(MAKE) -C $@
	
GraphClustering : Utils
     
