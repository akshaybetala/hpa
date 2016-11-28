export PATH=/opt/intel/bin/:$PATH
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
python processVector.py
cd loops
make clean


