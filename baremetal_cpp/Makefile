.PHONY: esp raspi

esp:
	$(MAKE) -C esp/
	
raspi:
	$(MAKE) -C raspi/
	
clean_esp:
	$(MAKE) -C esp/ -f Makefile clean
	
clean_raspi:
	$(MAKE) -C raspi/ -f Makefile clean
	
qemu_raspi:
	$(MAKE) -C raspi/ -f Makefile run