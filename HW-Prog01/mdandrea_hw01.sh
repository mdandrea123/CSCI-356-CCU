#! /bin/bash




#########################################
#Author: Michael Dandrea
#Class: CSCI 356
#Email: mdandrea@coastal.edu
#Description: CSCI365 HW01
#Date: 9/15/23
#########################################

# Step 4
echo Making temp directory... Done.
mkdir /home/$USER/temp

# Step 5
man df | tee temp/5.out

# Step 6
grep -i -E '^[m]' passwd.txt t| tee temp/6.out

# Step 7
grep -i -E '^[d]' passwd.txt | wc -l | tee temp/7.out

# Step 8
env | sort | tee temp/8.out

# Step 9
echo "Enter the number of miles"
read miles

if ! [ "$miles" > 0]
then
	echo "Error: Please enter a positive non-zero number"
	exit 0
else
	conv=1.60934
	kilo=$(echo "$mile * $conv" || bc )

	echo "${miles} miles = ${kilo} kilometers"
	echo "${miles} miles = ${kilo} kilometers" > temp/9.out
fi	
	
# Step 10
cat temp/*.out > mdandrea_hw01.txt