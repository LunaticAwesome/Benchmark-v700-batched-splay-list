import json
import os
import shutil

def process_json_file(src_path, dest_dir):
    try:
        with open(src_path, 'r') as f:
            data = json.load(f)
    except (json.JSONDecodeError, UnicodeDecodeError):
        print(f"Error: file {src_path} not a valid JSON")
        return

    base_name = os.path.splitext(os.path.basename(src_path))[0]
    dest_subdir = os.path.dirname(src_path).replace("jsons_template", dest_dir, 1)

    # Создаем целевую подпапку
    os.makedirs(dest_subdir, exist_ok=True)

    for num_threads in range(1, 17):
        modified = json.loads(json.dumps(data))
        
        # Модифицируем тестовую секцию
        if "test" in modified:
            modified["test"]["numThreads"] = num_threads
            if "threadLoopBuilders" in modified["test"]:
                for builder in modified["test"]["threadLoopBuilders"]:
                    if "pin" in builder:
                        builder["pin"] = list(range(num_threads))
                        builder["quantity"] = num_threads

        # Формируем имя файла
        dest_name = f"{base_name}_numThreads_{num_threads}.json"
        dest_path = os.path.join(dest_subdir, dest_name)

        # Сохраняем
        with open(dest_path, 'w') as f:
            json.dump(modified, f, indent=4)

def process_templates():
    root_dir = "jsons_template"
    dest_dir = "load_jsons"

    # Очищаем целевую папку
    if os.path.exists(dest_dir):
        shutil.rmtree(dest_dir)
    os.makedirs(dest_dir)

    # Рекурсивный обход
    for foldername, subfolders, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith('.json'):
                src_path = os.path.join(foldername, filename)
                process_json_file(src_path, dest_dir)

if __name__ == "__main__":
    process_templates()
    print("Completed. Results in folder load_jsons")
