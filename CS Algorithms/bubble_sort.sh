echo "========================================================================"
echo ""
echo "                 Enter values to sort                                  "
echo ""
echo "========================================================================"
read vals
 
set -- $vals
n=$#
 
k=0
for val in $* 
do
    a[$k]=$val
    ((k++))
done
 
flag=1
 
for (( i=0; i<$n-1 && $flag==1; i++ ))
do
    flag=0
    for (( j=0; j<$n-i-1; j++ ))
    do
        if [ ${a[$j]} -gt ${a[$j+1]} ]
        then
            temp=${a[$j]}
            a[$j]=${a[$j+1]}
            a[$j+1]=$temp
            flag=1
        fi
    done
done
 
echo "========================================================================"
echo ""
echo "                 Sorted!!                                               "
echo ""
echo "========================================================================"

for (( l=0; l<$n; l++))
do
    echo -ne "${a[$l]} "
done
 
echo