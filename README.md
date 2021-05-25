3-Check-Chess
- proiect PA 2021 -

Echipa TheRookies

Arvat Ovidiu-Daniel 323CC
Moraru Anemona-Maria 323CC
Poasca Stefan 323CC
Toma Stefan-Madalin 323CC


ETAPA 1

Arhiva echipei noastre se foloseste de un Makefile pentru a compila codul
algoritmului nostru. Dupa acest proces putem sa dam play unui joc de sah
folosind comanda prezenta si pe site 'xboard -fcp "make run" -debug'.

Limbajul de programare folosit este C++. Intregul nostru proiect este realizat
in jurul celor doua foldere 'Include' si 'Source'. In primul folder vom regasi
headere ce contin definitii ale claselor dezvoltate ulterior in folder-ul
'Source', definitii ale functiilor, precum si bibliotecile folosite in
intocmirea proiectului. In folder-ul 'Source' se regaseste practic, intregul
proiect. Tot ce este mentionat in primul folder, acum este dezvoltat si realizat
in asa fel incat jocul de sah sa prinda viata.

Etapa 1 se axeaza pe miscarile posibile si corecte ale pionului. De aceea,
functia 'getARandomMove' genereaza miscarea pionului, folosindu-se de o alta
functie pentru fiecare pion al botului denumita 'getPositions', functie ce
returneaza toate miscarile posibile ale acestuia intr-o complexitate de O(1).
In cazul in care nu exista miscari posibile, jocul se va finaliza prin remiza,
in caz contrar,  se alege o miscare la intamplare. Miscarea aleasa va fi
trimisa catre xboard mai departe pentru a continua algoritmul.


ETAPA 2

In aceasta etapa am realizat mutarile tutror pieselor de pe tabla de sah. Acestea
se misca intr-un mod aleator, alegerea pieselor si a mutarilor nu este realizata
dupa un algoritm inteligent momentan, acesta fiind unul care randomizeaza mutarile.
Regele oponent continua jocul de sah cu mutari valide in cazul in care acesta se
afla in sah.

Pionii pot fi promovati in piesele precizate din enunt: in regina daca mutam
direct pionul inainte si in turn/cal/nebun daca dam putin pionul inapoi si apoi
avansam cu acesta.

De asemenea, mutarile speciale En passant, Rocada mica si mare sunt valide si
realizate conform constrangerilor din cerinta.


ETAPA 3

In acesta etapa am realizat un algoritm avansat al jocului de sah bazat pe
cunoscutul algoritm de jocuri Alpha-Beta-Pruning. In fisierul Tree.cpp avem
functia 'minimax()' ce calculeaza starile viitoare ale jocului.

Totodata, in aceasta etapa am conditionat jocul de sah pentru specificul de
'3-Check-Chess', jocul oprindu-se cand oponent-ul bot-ului primeste 3 sah-uri.


Ca surse de inspiratie am folosit link-urile prezentate pe site:
[1] https://www.gnu.org/software/xboard/engine-intf.html
[2] https://www.gnu.org/software/xboard/engine-intf.html#9
[3] https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977/
[4] https://www.youtube.com/watch?v=l-hh51ncgDI

Fiind o echipa, de la bun inceput am discutat si am gandit impreuna algoritmul
ales. Pe de alta parte, fiecare a contribuit la realizarea functiilor folosite
in acest proiect si la partea de debugging a posibilelor erori aparute.