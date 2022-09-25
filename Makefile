# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
build:
	g++ curatare.cpp -o curatare
	g++ fortificatii.cpp -o fortificatii
	g++ curse.cpp -o curse
	g++ beamdrone.cpp -o beamdrone

run-p1:
	./curatare

run-p2:
	./fortificatii

run-p3:
	./beamdrone

run-p4:
	./curse

clean:
	rm -rf curatare fortificatii beamdrone curse
