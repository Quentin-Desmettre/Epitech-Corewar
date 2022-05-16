##
## EPITECH PROJECT, 2021
## B-CPE-201-LIL-2-1-corewar-noa.trachez
## File description:
## Makefile
##

.PHONY: doc

all	:
	make -C asm
	make -C corewar

re	:
	make re -C asm
	make re -C corewar

clean	:
	make clean -C asm
	make clean -C corewar
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.o" -delete
	find . -name "vgcore.*" -delete

fclean	:
	make fclean -C asm
	make fclean -C corewar

tests_run: fclean
	echo "Testing ASM..."
	make tests -C asm
	gcovr --html --html-details -o corewar.html
	find . -name "*.o" -delete
	mkdir -p test_report
	mv *.html *.css test_report/

functional:
	echo "Testing ASM..."
	make -s functional_tests -C asm > asm.log ; tail -n 3 asm.log | head -n 1
	echo "See full detail in asm.log."

doc:
	doxygen corewar.doxy
