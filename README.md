# BMP.Convertor
Visual Studio 2015 Project

  Convert .bmp image to monochrome and negative.

===============================
  The application processes 24-bit BMP images. When working with the program, the user enters a name (for example, name. Bmp) of the processed image, then selects image processing options (negative, monochrome). The processed images are saved in separate files. 
  In case of unsuitable image format or lack of a file (should be located in the program folder), an appropriate error message is displayed and the program is terminated.
  Structures for reading the header and information of the BMP file, and working with pixels are defined in the stdafx header file. H. To convert to a negative, we read the image, writing all the information about it into an array, and create a new image with the same header data, but with the inverse data of colors. To convert to black and white, read the image, writing all the information about it into an array, and create a new image with the same header data, but with R, G, B values equal to Y=R*0.21G*0.72 B*0.07 - this formula is used for correct translation in black and white.

===============================
  Приложение обрабатывает 24-bit BMP изображения. При работе с программой пользователь вводит имя (например, name.bmp) обрабатываемого изображения, затем выбирает варианты обработки изображения (негатив, монохромное). Обработанные изображения сохраняются в отдельные файлы.
  В случае неподходящего формата изображения или отсутствия файла (должен быть расположен в папке с программой) выводится соответствующее сообщение об ошибке и происходит завершение программы.
  Структуры для считывания заголовка и информации BMP-файла, и работы с пикселями определены в заголовочном файле stdafx.h. Для конвертации в негатив читаем изображение, записывая всю информацию о нём в массив, и создаём новое изображение с такими-же данными заголовков, но с инверсированными данными цветов. Для конвертации в черно-белое читаем изображение, записывая всю информацию о нём в массив, и создаём новое изображение с такими-же данными заголовков, но с значениями R, G, B равными Y=R*0.21+G*0.72+B*0.07 – данная формула используется для корректного перевода в черно-белое.
