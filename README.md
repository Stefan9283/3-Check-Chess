3-Check-Chess
- proiect PA 2021 -

ETAPA 1

Echipa TheROOKies

Toma Stefan-Madalin 323CC
Poasca Stefan 323CC
Moraru Anemona-Maria 323CC
Arvat Ovidiu-Daniel 323CC

Arhiva echipei noastre se foloseste de un CMakeLists.txt. Initial introducem 
comanda 'cmake .' pentru a genera Makefile-ul aferent codului nostru, dupa 
care compilam toate sursele existente folosind comanda 'make'. Dupa acest 
proces putem sa dam play unui joc de sah folosind comanda prezenta si pe site 
'xboard -fcp "make run" -debug'.

Limbajul de programare folosit este C++. Intregul nostru proiect este realizat
in jurul celor doua foldere 'Include' si 'Source'. In primul folder vom regasi
headere ce contin definitii ale claselor dezvoltate ulterior in folder-ul
'Source', definitii ale functiilor, precum si bibliotecile folosite in
intocmirea proiectului. In folder-ul 'Source' se regaseste practic, intregul
proiect.

Din punctul de vedere al structurii ne folosim de clasa 'Engine' care contine 
o instanta a clasei 'Table'. Aceasta din urma se foloseste de o matrice de 
pointeri de tipul 'Square' numita 'squares' pentru a retine informatii in 
legatura patratelele tablei de sah (culoarea, piesa si un set de piese care 
se pot muta pe patratul respectiv). Piesele celor doi jucatori sunt retinute 
in matricea 'pieces' avand pe linia 0 piesele albe iar pe linia 1 cele negre. 
Mai exista si un vector 'history' in care se retin mutarile anterioare sub 
forma de perechi de vectori cu doua componente. Ca metode mentionam functiile 
IO si parsare a mutarilor primite de la xboard.

Etapa 1 se axeaza pe miscarile posibile si corecte ale pionului. De aceea,
functia 'getARandomMove' genereaza miscarea pionului (in O(1)), folosindu-se 
de o alta functie pentru fiecare pion al botului denumita 'getPositions', 
functie ce returneaza toate miscarile posibile ale acestuia intr-o complexitate 
de O(1). In cazul in care nu exista miscari posibile, jocul se va finaliza prin 
remiza, in caz contrar,  se alege o miscare la intamplare. Miscarea aleasa va fi
trimisa catre xboard mai departe pentru a continua algoritmul.

Ca surse de inspiratie am folosit link-urile prezentate pe site:
[1] https://www.gnu.org/software/xboard/engine-intf.html
[2] https://www.gnu.org/software/xboard/engine-intf.html#9

Fiind o echipa, de la bun inceput am discutat si am gandit impreuna algoritmul
ales. Pe de alta parte, fiecare a contribuit la realizarea functiilor folosite
in acest proiect si la partea de debugging a posibilelor erori aparute.
