#!/bin/bash
printf "Lab 1.5. Karol Gutierrez, A01024536\n\nOne of the many locations of the kernel source code is:\n" >> linux_source_structure.txt;
LOCATION="usr/src/linux-headers-3.16.0-6-686-pae/include/config";
echo $LOCATION >> linux_source_structure.txt;

echo "First Level: ">> linux_source_structure.txt;
echo ".h files ">> linux_source_structure.txt;
echo $(cd ~; cd ..; cd ..; cd $LOCATION; ls *.h)>> linux_source_structure.txt;
echo ".c files ">> linux_source_structure.txt;
echo $(cd ~; cd ..; cd ..; cd $LOCATION; ls *.c)>> linux_source_structure.txt;


echo "Second Level: ">> linux_source_structure.txt;
cd ~;
cd ..;
cd ..;
#echo $(pwd);
cd $LOCATION;
#echo $(pwd);
echo ".h files";
for dir in $(find . -type d);
do
	echo $(ls $dir/ *.h);
done

echo ".h files";
for dir in $(find . -type d);
do
	echo $(ls $dir/ *.h);
done
