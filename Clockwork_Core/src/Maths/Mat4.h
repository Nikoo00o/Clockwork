#pragma once
#include <vector>
#include<iostream>
#include <sstream>
#include <cmath>

#include "Vec2.h"//vektoren für weniger schreibarbeit in matrizen includen, damit alles in der klasse definiert werden kann, aber methoden der vektoren, die mit matrizen arbeiten müssen im vektor in klasse deklariert und hier im headerende der matrix definiert werden | wird aber wahrscheinlich nicht gebraucht, da matrix mit vektor eh nur * und nicht *= macht und konstruktor eigentlich auch nicht gebraucht wird und matrix immer als erstes stehen muss
//auch noch für Mat2xx und für Mat3xx nach dem gleichen schema, müssen auch als friend deklariert werden 

/*wichtig bei matrix operatoren/methoden an denen von vektoren orientieren und genauso machen, nur für alle anderen matrixen überladen, ausser bei denen wo es keinen sinn macht, z.b. multiply MATHE REGEL SPALTEN ZEILEN 
MATRITZEN AUCH NICHT MIT RVALUE REFERENZEN MACHEN, da const referenz vollkommen ausreicht, da matritzen immer primitive datentypen als member haben und somit const referenz reicht und sich an rvalue und lvalue objekte bindet
AUCH GANZ WICHTIG bei matritzen sind die methoden für multiply und divide elementwise, also nicht das normale matrix matrix multiplikation ding aus der schule, aber die operatoren haben dann das normale matrix matrix multiplikationsverhalten aus der schule 
und müssen auch nicht für alle anderen überladen werden | zeilen spalten regel | zu operatoren dann like scalar product hinschreiben 
infos noch ein bisschen https://learnopengl.com/#!Getting-started/Transformations 

in matrix vector includen und dann die methoden mit vectoren direkt in der klasse definieren | falls vektoren methoden mit matritzen haben, diese in klasse prototypen und in matritzen header definieren ausserhalb der klasse




WICHTIG NEU: in allen matritzen den standardkonstruktor explizit machen, damit er nicht versehentlich aufgerufen wird, wegen den =0 default werten 
und in allen matritzen auch union mit einem struct von all den type values und einem type array von data machen und dann auch operatoren, etc kopieren | AUCH nochmal kommentar von matrix kopieren mit opengl column major layout



*/