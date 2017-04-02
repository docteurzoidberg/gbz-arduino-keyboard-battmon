/home/drzoid/app/arduino-1.6.12/arduino --verbose --preserve-temp-files --board arduino:avr:leonardo --verify ./gbz-keyb-battmon/gbz-keyb-battmon.ino > /tmp/arduino_build.log

DIR=`cat /tmp/arduino_build.log | grep -oP '/tmp/arduino_build_(\d*)' | head -1`
HEX=`cat /tmp/arduino_build.log | grep -oP '/tmp/arduino_build_(\d*)/([^\s]*).hex'`

#TODO: test dir et clean

if [ ! -f $HEX ]; then
  echo "Compilation failed, check /tmp/arduino_build.log"
  exit -1
fi

echo "Copying $HEX to firmware/"

cp $HEX firmware/

echo "Done."
