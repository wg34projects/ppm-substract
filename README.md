# ppm-substract
PPM Substract Task WS2016 FHTW

I created this tool as a task in the winter-semester 2016 at www.technikum-wien.at electronical engineering

Details for usage you can find in the help section - start the executable with -h

Below my Readme in German



1) Dateien / Inhalt / Zusammenfassung

main.h		  Headerdatei samt Funktionsprototypen und Präprozessormakros

main.c		  Hauptprogramm mit getopt Auswertung und Funktionsaufrufen

screen.c	  Funktionsdeklarationen für Bildschirmausgabe und getopt Abarbeitung

readppm.c	  Funktionsdeklarationen PPM lesen (P3 ASCII und P6 BINARY Type)
	
writeppm.c	Funktionsdeklarationen PPM schreiben (P3 ASCII und P6 BINARY Type)

calcppm.c	  Funktionsdeklarationen der Berechnungen für IMAGE SUBSTRACTION, das Herzstück des Tools

		Es kann zwischen 6 Ausgabeoptionen gewählt werden:

		# Einbeziehung jedes R/G/B Wertes bei der Berechnung: ein Pixel gilt as verändert wenn sich dessen R & G & B
		  Wert mehr als der gegebene threshhold geändert hat
		  abs [ (color value pixel input 2) - (color value pixel input 1) ] > threshold

		  - Type 1 - unveränderte Pixel Hintergrundfarbe (schwarz R/G/B 0/0/0 voreingestellt, über Präprozessormakro BLACKPRESETTING 
		             auch auf z. B. weiss 255/255/255 umstellbar), veränderte Pixel angegebene R/G/B Farbe bzw. wenn nicht definiert
			     wird jeder undefinierte Farbwert auf 255 gesetzt - ACHTUNG, dies habe ich gegenüber der Vorgabe CIS geändert 
			     ("If one of these options is ommited, the corresponding color value shall be set to zero") da sonst sowohl
			     Hintergrund als auch Bewegung schwarz wäre, dies ist über das Präprozessormakro NOCOLORPRESETTING umstellbar

		  - Type 2 - unveränderte Pixel original wie in INPUT1, veränderte Pixel angegebene R/G/B Farbe (bzw. wenn nicht angegeben siehe Type 1)

		  - Type 3 - unveränderte Pixel original wie in INPUT1, veränderte Pixel angegebene R/G/B Farbe (bzw. wenn nicht angegeben siehe Type 1) 
	                     mit Transparenz, die Transparenz kann über TRANSPARENCY angepasst werden [dies ist eher ein "gelungenes" Experiment mit den
			     unterschiedlichen Ausgabeoptionen und wurde wegen des interessanten optischen Effekts beibehalten].

		  - Type 4 - unveränderte Pixel Hintergrundfarbe (siehe auch Bemerkung Type 1), veränderte Pixel original
			     wie in INPUT 2 - die "Bewegung" wird quasi ausgeschnitten

		# Einbeziehung des GREY Wertes bei der Berechnung: ein Pixel gilt as verändert wenn sich dessen errechneter Grauwert
		  mehr als der gegebene threshhold geändert hat. Grundlage Berechnung https://de.wikipedia.org/wiki/Grauwert
		  abs [ (grey value pixel input 2) - (grey value pixel input 1) ] > threshold

		  - Type 5 - unveränderte Pixel Hintergrundfarbe (siehe auch Bemerkung Type 1), veränderte Pixel angegebene R/G/B Farbe 
			     (bzw. wenn nicht angegeben siehe Type 1) - berechnet mit dem gewichteten Grauwert

		  - Type 6 - detto Type 5 jedoch mit den nicht gewichteten Grauwert

2) Kompilierung

Bei Kompilierung mit GCC bitte die Option -std=c99 verwenden.

gcc main.h main.c screen.c readppm.c calcppm.c writeppm.c
clang main.h main.c screen.c readppm.c calcppm.c writeppm.c

3) Testumgebung

x64 Windows 10 - Build 15014 - GCC
ARM Raspian - Kernel 4.4 Raspbian - GCC und CLANG

4) Bemerkungen

Eventuelle Kommentarzeilen werden bei 100 Zeichen pro Zeile abgeschnitten [Änderung zu Medium Tasks, wurde und wird über MAXCHARSPERLINE definiert], 
die Ausgabedatei enthält NICHT die Kommentare der Eingabedatei, diese werden nicht übernommen und durch folgenden Kommentar ersetzt: # created by el16b005 BEL1 helmut resch

5) Anwendung

weitere Infos auf bei Programmaufruf mit -h

subtract.exe -f inp1.ppm -s inp2.ppm -o out1.ppm -v out2.ppm -w out3.ppm -x out4.ppm -y out5.ppm -z out6.ppm -t 40 -p p6 -r 255 -g 255 -b 255

Argumente: OPT optional, REQ required

-h Hilfe

-f inp1.ppm	REQ	1st input image
INPUT Datei 1, das ist das neutrale Referenzbild
Das erste Bild definiert Breite, Höhe und Helligkeit - die Bilddaten von INPUT Datei 2 werden verglichen, wenn es Abweichungen gibt wird
abgebrochen samt Meldung dass die Bilder nicht kompatibel sind
Es werden nur 8-bit PPM unterstützt

-s inp2.ppm	REQ	2nd input image
INPUT Datei 2, das ist das Bild mit der "Bewegung"

-o out1.ppm	OPT	output type 1
-v out2.ppm	OPT	output type 2
-w out3.ppm	OPT	output type 3
-x out4.ppm	OPT	output type 4
-y out5.ppm	OPT	output type 5
-z out6.ppm	OPT	output type 6
Verschiedene Ausgabeoptionen wie in 1) beschrieben, Kombination beliebig, eine Ausgabedatei ist natürlich notwendig

-t 40	OPT	threshhold value
Werte von 0 - 255 möglich, wenn der Wert >= der tatsächlich gelesenen BRIGHTNESS wird, wird später im Programmablauf abgebrochen
Es können nur Zahlenwerte eingegeben werden, auch wenn 133a steht wird eine Fehlermeldung ausgegeben und nicht bis zum Fehler umgewandelt
Wenn kein Wert angegeben wird, wird später die halbe Helligkeit als Vorgabewert übernommen, ein Hinweis erfolgt

-p p6	REQ	output format for picture
P3 ASCII - P6 BINARY

-r 255	OPT	R Wert Markierungsfarbe
-g 255	OPT	G Wert Markierungsfarbe
-b 255	OPT 	B Wert Markierungsfarbe
Werte von 0 - 255 möglich, wenn der Wert/die Werte >= der tatsächlich gelesenen BRIGHTNESS wird, wird später im Programmablauf abgebrochen
Es können nur Zahlenwerte eingegeben werden, auch wenn 133a steht wird eine Fehlermeldung ausgegeben und nicht bis zum Fehler umgewandelt
Nicht angegebene Werte werden mit 255 definiert - siehe auch unter 1) Type 1
