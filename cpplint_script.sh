#!/bin/sh

echo "Start CPPLINT analysis..."
python.exe cpplint.py --verbose=1 src/*
echo "End of CPPLINT analysis."