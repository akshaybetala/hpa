FILE_NAME='$1'
export PATH=/opt/intel/bin/:$PATH
echo 1 | sudo tee /proc/sys/kernel/randomize_va_space
make cc=icc