chmod 755 pld-wrapper.sh

TYPE=$1
FOLDER="tests/Init/${TYPE}"

python3 pld-test.py $FOLDER
