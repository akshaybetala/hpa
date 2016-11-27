echo "FileName,EventName,Metric" > stat.csv
for i in *.novec;do
    for event in task-clock; do
	a=`perf stat -e $event  ./$i ./input 5 2>&1 | grep $event | sed -e 's/^[ \t]*//' | sed 's/ .*//'` 
    	echo $a
	echo $i,$event,$a >> stat.csv
	done
done
