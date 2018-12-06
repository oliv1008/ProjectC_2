.PHONY: clean All

All:
	@echo "----------Building project:[ SacADos - Debug ]----------"
	@"$(MAKE)" -f  "SacADos.mk"
clean:
	@echo "----------Cleaning project:[ SacADos - Debug ]----------"
	@"$(MAKE)" -f  "SacADos.mk" clean
