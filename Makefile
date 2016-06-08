.PHONY: app driver

all : app driver
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
	$(MAKE) -C $@ #> log_$@.txt


clean:
	$(MAKE) clean -C app #> log_app.txt
	$(MAKE) clean -C driver #> log_driver.txt
	

