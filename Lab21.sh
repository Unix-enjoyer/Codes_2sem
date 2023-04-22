#!/bin/bash

let len=0; # число введенных аргументов, оно же и триггер, нужно ли просить повторный ввод
until ((len == 2)); do # глупый пользователь будет вводить до тех пор, пока не введет нормально
	echo "Через пробел введите число дней и суффикс"
	read day subs

	input="$day $subs" # склеить в строку и далее разбить ее по пробелу

	IFS=' ' read -ra checker <<< `echo $input` # так определится количество введенных символов а также проверится
	len=${#checker[@]} # есть ли между ними пробел(условие задачи 7)

	if ((len == 2)); then

		for char in {a..z}; do # проверка на недопустиме символы в числе
			if [[ ${checker[0]} == *"$char"* ]]; then
				let len=0
				echo "Первый аргумент должен быть числом, например: 2"
				checker=()
			fi
		done
	fi
	
	
	if ((len != 2)); then #проверка на число аргументов

		echo "Введите 2 аргумента с разделителем 'пробел', например: 2 file"
		checker=()
	fi
done



let dead_num=${checker[0]} # просто переименование переменных
substr=${checker[1]}


today_day=`date +%j` # номер сегодняшнего дня

for file in `pwd`/*; do

	IFS='/' read -ra array <<< `echo $file` # выцепить название файла
	name=`echo ${array[5]}`
	 
	file_day=`date -r $name +%j` # номер дня редактирования файла
    	let value=10#$today_day-10#$file_day # дней с момента редактирования


    	if ((value >= dead_num)); then
    	
		if [[ $name == "$substr"* ]]; then # если суффикс в слове - удаляем		
			rm $name
			let counter=1;

		fi
    	fi
    	
done

if ((counter != 1)); then
	echo "Файлов с этим именем, созданных $dead_num дней назад, нет в папке, введите другое имя или число дней"
fi

