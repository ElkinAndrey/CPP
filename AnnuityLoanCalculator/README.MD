# Калькулятор аннуитетных кредитов

Калькулятор, принимающий сумму кредита, процентную ставку и срок, на который берется кредит. По этим данным калькулятор рассчитывает общую сумму выплат, переплату и сумму каждого платежа.

Программа написана на языке программирования C++. Графическая часть приложения реализована при помощи Windows Forms. Проект написан в среде разработки Visual Studio 2022. 

Для работы с Windows Forms нужно установить дополнительный компонент "Поддержка C++/CLI для Build Tools v143" (Заходим в Visual Studio 
-> Панель в самом верху 
-> Средаства 
-> Получить средства и компоненты 
-> В открывшемся окне перейти в Отдельные компоненты). 
Затем нужно создать пустой проект CLR(.NET Framework) и создать файл с формой. Изначально форма не будет отображаться, для того, чтобы исправить это перезагрузите Visual Studio (при выключении Visual Studio может не перезагрузится, если это произошло, то перезагрузите компьтер). 

Для добавления файлов Windows Forms нужно нажать ПКМ по папке "Файлы ресурсов" в visual Studio -> Добавить -> Создать элемент -> Форма Windows Forms (Если такой нет, то установите компонент "Поддержка C++/CLI для Build Tools v143").
