#!/bin/bash
#labtask.sh
#Code_Skeleton

clean_up()
{
	clear
	#break 
	echo "Program is terminating"
	#clear	
	exit
}

create_dir()
{
	dialog --title "Directory Creation" --clear \
		--inputbox "Enter name of Directory:" \
		16 51 2>tempf
	nam=$(cat tempf)
	retval=$?
	
	rm tempf

	case $retval in
		0)
			temp=$(mkdir $nam-d)
			$temp
			dialog --title "DIR" --msgbox "Created" 6 20
			;;
		1)
			dialog --title "DIR" --msgbox "Not Created" 6 20
			;;
	esac
}		

create_file()
{
	dialog --title "File Creation" --clear \
		--inputbox "Enter name of the file:" \
		16 51 2>tempf
	
	nam=$(cat tempf)
	retval=$?
	
	rm tempf

	case $retval in
		0)	
			temp=$(touch $nam)
			#$temp
			dialog --title "DIR" --msgbox "Created" 6 20
			;;
		1)
			dialog --title "DIR" --msgbox "Not Created" 6 20
			;;
	esac

}

show_path()
{
	var1=$(pwd)
	dialog --title "Present Working Directory" \
	--msgbox "$var1" 10 28
}

move_up()
{
	#'cd ..'
	cd ..
		dialog --title "Alert" \
	--msgbox "Moved one dir up" 6 20
	
	show_path
#$var
}

list_contents()
{
	var3=$(ls)
	dialog --title "CONTENTS" --msgbox "$var3" 10 30
}

change_dir()
{
dialog --title "Navigation" --clear \
		--inputbox "Enter name of the Directory:" \
		16 51 2>tempf
	nam=$(cat tempf)
	retval=$?
	
	rm tempf
	
	case $retval in
		0)	
			if [[ -e $nam ]]; then
				cd  $nam
				dialog --title "Alert" --msgbox "Moved" 6 20
				show_path
			else
				dialog --title "Alert" --msgbox "Doesn't exist" 6 20
				show_path
			fi			
			;;
		1)
			dialog --title "Alert" --msgbox "Not Moved" 6 20
			;;
	esac


}


delete_file(){
dialog --title "File Deletion" --clear \
		--inputbox "Enter name of the file:" \
		16 51 2>tempf
	
	nam=$(cat tempf)
	retval=$?
	
	rm tempf

	case $retval in
		0)	
				
			if [[ -e $nam ]]; then
				temp=$(rm -r $nam)
				dialog --title "Alert" --msgbox "Deleted" 6 20
				
			else
				dialog --title "Alert" --msgbox "Doesn't exist" 6 20
				show_path
			fi			
			;;
		1)
			dialog --title "DIR" --msgbox "Not deleted" 6 20
			;;
	esac

}

delete_dir(){
dialog --title "Directory Deletion" --clear \
		--inputbox "Enter name of the Directory:" \
		16 51 2>tempf
	
	nam=$(cat tempf)
	retval=$?
	
	rm tempf

	case $retval in
		0)	
			if [[ -e $nam ]]; then
				temp=$(rm -r $nam)
				dialog --title "Alert" --msgbox "Deleted" 6 20
				
			else
				dialog --title "Alert" --msgbox "Doesn't exist" 6 20
				show_path
			fi			
			;;
		1)
			dialog --title "DIR" --msgbox "Not deleted" 6 20
			;;
	esac

}


while true
do
dialog \
--title "Create Dir Structure" \
--menu "Choose your option: " 20 60 10 \
1 "Create Directory" \
2 "Create File" \
3 "Move One Level Up" \
4 "List Contents of Directory" \
5 "Change Directory" \
6 "Show Path" \
7 "Delete File" \
8 "Delete Directory" \
9 "Exit" 2>tempf

opt=$(cat tempf)
rm tempf



case $opt in
	1)
		create_dir;;
	2)
		create_file;;
	3)
		move_up;;	
	4)
		list_contents;;
	5)
		change_dir;;
	6)
		show_path;;
	7)
		delete_file;;
	8)
		delete_dir;;
	9)
		clean_up;;	 
esac
done
