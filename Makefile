SHELL = /bin/bash
.PHONY: app driver

all : driver app
	@echo
	@echo "done..."	
app:
	@echo
	@echo "***************************************************"
	@echo "**  Making $@     				 **"
	@echo "***************************************************"
	$(MAKE) -C $@ #> log_$@.txt
	
driver: 
	@echo
	@echo
	@echo "***************************************************"
	@echo "**  Making $@     				 **"
	@echo "***************************************************"
	pushd $@ &&	$(MAKE) &&	popd


clean:
	$(MAKE) clean -C app #> log_app.txt
	$(MAKE) clean -C driver #> log_driver.txt
	

