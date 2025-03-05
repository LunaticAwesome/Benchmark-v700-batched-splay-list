import json
import os
from collections import defaultdict

# Directory containing the JSON files
JSON_DIR = "jsons"

# Output directory for the averaged JSON files
OUTPUT_DIR = "averaged_results"

def normalize_average_operations(json_dir, output_dir):
    # Create the output directory if it doesn't exist
    os.makedirs(output_dir, exist_ok=True)

    # Dictionary to store aggregated data for each prefix
    prefix_data = defaultdict(lambda: {"total_operations": 0, "file_count": 0, "aggregated_data": defaultdict(float)})

    # Loop through all JSON files in the directory
    for filename in os.listdir(json_dir):
        if filename.endswith(".json"):
            # Extract the prefix (everything before "_run" or ".result.json")
            if "_run" in filename:
              prefix = filename.split("_run")[0]

            filepath = os.path.join(json_dir, filename)
            with open(filepath, "r") as file:
                data = json.load(file)
                
                # Add the average_num_operations_total to the total for this prefix
                if "average_num_operations_total" in data:
                    prefix_data[prefix]["total_operations"] += data["average_num_operations_total"]
                    prefix_data[prefix]["file_count"] += 1

                # Aggregate other metrics for this prefix (optional)
                for key, value in data.items():
                    if isinstance(value, (int, float)):
                        prefix_data[prefix]["aggregated_data"][key] += value

    # Calculate the average for each prefix and save the results
    for prefix, data in prefix_data.items():
        if data["file_count"] > 0:
            average_operations = data["total_operations"] / data["file_count"]
        else:
            average_operations = 0

        # Create the output JSON structure for this prefix
        output_data = {
            "average_num_operations_total": average_operations,
            **{key: value / data["file_count"] for key, value in data["aggregated_data"].items()}
        }

        # Save the output JSON to a file
        output_file = os.path.join(output_dir, f"{prefix}_average.json")
        with open(output_file, "w") as outfile:
            json.dump(output_data, outfile, indent=4)

        print(f"Averaged JSON for prefix '{prefix}' saved to {output_file}")

# Run the function
normalize_average_operations(JSON_DIR, OUTPUT_DIR)