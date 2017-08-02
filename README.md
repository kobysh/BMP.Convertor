# BMP.Convertor
Convert .bmp image to monochrome and negative

Приложение обрабатывает 24-bit BMP изображения. При работе с программой пользователь вводит имя (например, name.bmp) обрабатываемого изображения, затем выбирает варианты обработки изображения (негатив, монохромное). Обработанные изображения сохраняются в отдельные файлы.
В случае неподходящего формата изображения или отсутствия файла (должен быть расположен в папке с программой) выводится соответствующее сообщение об ошибке и происходит завершение программы.
Структуры для считывания заголовка и информации BMP-файла, и работы с пикселями определены в заголовочном файле stdafx.h.
Для конвертации в негатив читаем изображение, записывая всю информацию о нём в массив, и создаём новое изображение с такими-же данными заголовков, но с инверсированными данными цветов.
Для конвертации в черно-белое читаем изображение, записывая всю информацию о нём в массив, и создаём новое изображение с такими-же данными заголовков, но с значениями R, G, B равными Y=R*0.21+G*0.72+B*0.07 – данная формула используется для корректного перевода в черно-белое.
