# Create 'frames' directory if it doesn't exist
mkdir -p frames

# Remove contents of 'frames' directory
rm frames/*
# rm out*
python3 main_test.py assets/star.jpg

# For ImageMagick v6
# convert -clear cache
# ./gif.sh

