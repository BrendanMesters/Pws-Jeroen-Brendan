# Pws-Jeroen-Brendan
De `C++` en `Python` code van ons PWS

## Indeling

De volgende folders:

- **Arduino code** Alle code die in c++ staat
- **Python code** Alle code die in Python staat
- **Sandbox** Alle testcode en dergelijke
- **Hardware** (WIP)

# Overige documenten

Er staat nog meer op [onze Google Drive](https://drive.google.com/drive/folders/0Bwz4SLY9bnJjaGFjNHdRSV8wM1E). Ook is er gebruik gemaakt van [StackOverflow](https://stackoverflow.com/users/7473796/brendan-mesters?tab=questions) gebruikt, hier zijn vragen gesteld over code die niet werkte zodat wij snel geholpen konden worden door andere programeurs.

# Arduino code
de arduino code is bedoeld om de auto aan te sturen D.M.V `stepper.ino`. De code heeft een `drive()` functie en een `rotate()` functie die zijn respectievelijk bedoeld om rechtdoor te rijden en te draaien om het draaipunt. De functie `ObstakenOntwijking`, deze voert aaan de hand van van de uitgelezen waardes van onze _HC-SR04_ sensor waardes een van `8 cases`  in een `SwitchCase` functie. Deze functie moet voorkomen dat de auto muren raakt.

# Python code
De python code bestaat uit een hoofdprogramma met een of meerdere modules. De module `kaart` die regelt de matrix die ik gebruik om de kaart in op te slaan. Het hoofdprogramma heet `PWS Python code`.

# Sandbox
In `Sandbox` staan diverse testprogrammas, deze worden vooral bij de python code gebruikt om stukjes van modules te testen.

# Hardware
Wij gebruiken een _arduino uno_ om de stappenmotoren aan te sturen, dit zijn _Rohs 28BYJ-48 stepper motors_, deze worden aangestuurd met behulp van de arduino libary `Accel Stepper` en met behulp van een _ULN2003_ bord, deze helpt bij het aansturen van de stappenmotoren. _HC-SR04_ wordt gebruikt om te zorgen dat onze auto niet botst, hierbij wordt code van [HowToMechatronics](http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/) gebruikt (het eerste stuk voorbeeld code, degene die niet `LiquidCrystal.h` gebruikt). We gebruiken ook een plexiglazen platvorm met een zwenkwiel en onze stappenmotoren. <!--Als we nog een tweede layer 3D-printen vergeet deze niet te benoemen in het verslag.-->