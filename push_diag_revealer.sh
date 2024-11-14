if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
  echo "Usage: $0 <day> <try_number> <exeutable_name>"
  exit 1
fi

# Assign the arguments to variables
day=$1
try_number=$2
exeutable_name=$3

# Run the commands
adb shell <<EOF
cd /storage/emulated/0/Download/
if [ ! -d $day ]; then
  mkdir $day
fi
cd $day
if [ ! -d $try_number ]; then
  mkdir $try_number
fi

EOF

adb push $exeutable_name /storage/emulated/0/Download/$day/$try_number/

adb shell <<EOF
su
cp /storage/emulated/0/Download/$day/$try_number/$exeutable_name /data/Ty
chmod +x $exeutable_name

EOF
