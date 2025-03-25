#!/bin/bash

# Directory containing the binaries
BIN_DIR="./bin"

# Directory containing the JSON files
JSON_DIR="load_jsons"

# Number of runs for each combination
NUM_RUNS=5

# Loop through all files in the bin directory recursively
find "$BIN_DIR" -type f | while read -r BIN_FILE; do
    # Extract the binary filename without the path
    BIN_FILENAME=$(basename "$BIN_FILE")
    
    # Loop through all JSON files in the load_jsons directory
    find "$JSON_DIR" -type f -name "*.json" | while read -r JSON_FILE; do
        # Extract the JSON filename without the path and extension
        JSON_FILENAME=$(basename "$JSON_FILE" .json)
        
        # Loop for the number of runs
        for (( RUN=1; RUN<=NUM_RUNS; RUN++ )); do
            # Define the result file path with a run number
            RESULT_FILE="jsons/${BIN_FILENAME}_${JSON_FILENAME}_run${RUN}.result.json"
            
            # Execute the binary with the specified options
            LD_PRELOAD=../lib/libmimalloc.so "$BIN_FILE" -create-default-prefill -json-file "$JSON_FILE" -result-file "$RESULT_FILE"
            
            # Check if the command was successful
            if [ $? -eq 0 ]; then
                echo "Successfully executed $BIN_FILE with $JSON_FILE (Run $RUN), results saved to $RESULT_FILE"
            else
                echo "Failed to execute $BIN_FILE with $JSON_FILE (Run $RUN)"
            fi
        done
    done
done