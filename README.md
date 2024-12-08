PAV - P3: estimación de pitch
=============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la estimación de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
 
   * ![image](https://github.com/user-attachments/assets/e7a131ce-4d12-4216-8adf-7c9a0cf4a033)


   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la biblioteca matplotlib de Python.

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.

   * Puede serle útil seguir las instrucciones contenidas en el documento adjunto `código.pdf`.

- Una vez completados los puntos anteriores, dispondrá de una primera versión del estimador de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la estimación de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.

1. rmaxnorm
2. r1norm
3. Potencia
4. Taza de cruces por cero, ZCR
   
![features_15ms](https://github.com/user-attachments/assets/bc53c7ce-faac-4fe1-8dca-8c61f0a53729)

![zcr](https://github.com/user-attachments/assets/814970c7-e773-4c5a-b614-430a080307c9)



      - Use el estimador de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos estimadores.
     
		Aunque puede usar el propio Wavesurfer para obtener la representación, se valorará
	 	el uso de alternativas de mayor calidad (particularmente Python).

Podemos ver que el pitch obtenido por nuestro sistema añade ceros en las tramas sordas. No obstante, hay algunas tramas sonoras que les asigna pitch nulo y no es correcto.
![image](https://github.com/user-attachments/assets/15ea07c7-9420-4b0f-bcf0-0720b993b46c)

  
  * Optimice los parámetros de su sistema de estimación de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

Con llindar_rmax = 0.4 (introducido desde la terminal) nos sale este resultado.

![image](https://github.com/user-attachments/assets/4c23c3b5-b8c3-4382-b838-8e75b8100dea)


Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  estimador a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del estimador. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la estimación de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
![image](https://github.com/user-attachments/assets/6043ca85-5e15-4637-99a3-a7f2b64d7119)
    ![image](https://github.com/user-attachments/assets/82d56005-d030-4038-a1e5-e4e077395939)


- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de estimación
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, diezmado, *center clipping*, etc.
Hemos escogido la técnica de *center clipping* con un threshold de 0.01 (ponemos a 0 aquellos valores inferiores a 0.01). Hemos probado con 0.009, 0.008 y 0.015 pero no habia mejoras en el resultado TOTAL.

![image](https://github.com/user-attachments/assets/bc52a211-b10b-49d6-b17b-b7f071563550)


  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
Hemos implementado el filtro de mediana de orden 3. Hemos probado con orden 2 y 4 pero los resultados no eran tan buenos.
    ![image](https://github.com/user-attachments/assets/2c501f17-1758-453c-b3d3-46729d6afcc0)

  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el estimador, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al estimador. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.

  Con un filtro de mediana de orden 2 (M=2) obtenemos:
  ![image](https://github.com/user-attachments/assets/0ba649ef-a3f3-45ec-b5dd-f20104313405)

  Y con M=4:
  ![image](https://github.com/user-attachments/assets/8bc08b47-2fb6-48ef-a71b-f4c35a9dcd19)

  Con M=5, mejoramos un poco pero sigue siendo peor que M=3:
  ![image](https://github.com/user-attachments/assets/932d0609-4efb-438b-929a-b4051b84f368)

Podemos concluir que los de orden par, al no tener un valor central el filtro no funciona muy bien, pero en los impares sí que funciona mejor, no obstante es mejor coger un valor de orden 3.


   

Evaluación *ciega* del estimador
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
estimador con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
