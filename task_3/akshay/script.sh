echo "FileName	EventName	Metric" > stat.csv
for i in *.novec;do
    for event in branch-instructions branch-misses bus-cycles cache-misses cache-references cpu-cycles instructions ref-cycles alignment-faults context-switches cpu-clock cpu-migrations dummy emulation-faults major-faults minor-faults page-faults task-clock L1-dcache-load-misses L1-dcache-loads L1-dcache-prefetches L1-dcache-store-misses L1-dcache-stores L1-icache-load-misses L1-icache-loads LLC-load-misses LLC-loads LLC-store-misses LLC-stores branch-load-misses branch-loads dTLB-load-misses dTLB-loads dTLB-store-misses dTLB-stores iTLB-load-misses iTLB-loads branch-instructions branch-misses bus-cycles cache-misses cache-references; do
	a=`perf stat -e $event  ./$i ./input 5 2>&1 | grep $event | sed -e 's/^[ \t]*//' | sed 's/ .*//'` 
    	echo $a
	echo $i '	' $event '	' $a >> stat.csv
	done
done
