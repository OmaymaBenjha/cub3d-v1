import json
import os

def process_torch():
    json_path = 'assets/textures/menu/torch.json'
    with open(json_path, 'r') as f:
        data = json.load(f)
    
    meta_width = data['meta']['dimensions']['width']
    meta_height = data['meta']['dimensions']['height']
    palette_len = len(data['meta']['palette'])
    header_len = 1
    expected_total_rows = header_len + palette_len + meta_height
    
    # Check and Fix Frames
    for i, frame in enumerate(data['frames']):
        rows = frame['data']
        actual_total_rows = len(rows)
        print(f"Frame {i}: Expected {expected_total_rows} rows, got {actual_total_rows}")
        
        if actual_total_rows < expected_total_rows:
            diff = expected_total_rows - actual_total_rows
            print(f"  Adding {diff} padding rows to Frame {i}")
            padding = [" " * meta_width] * diff
            frame['data'].extend(padding)
        elif actual_total_rows > expected_total_rows:
            print(f"  Truncating {actual_total_rows - expected_total_rows} excess rows from Frame {i}")
            frame['data'] = rows[:expected_total_rows]

    # Regenerate XPMs
    for i, frame in enumerate(data['frames']):
        xpm_path = f"assets/textures/menu/torch_{i}.xpm"
        with open(xpm_path, 'w') as f:
            f.write("/* XPM */\n")
            f.write(f"static char *torch_{i}[] = {{\n")
            for line in frame['data']:
                f.write(f'"{line}",\n')
            f.write("};\n")
        print(f"Generated {xpm_path}")
    
    # Cleanup extra files from 10-frame version
    for j in range(6, 11):
        old_path = f"assets/textures/menu/torch_{j}.xpm"
        if os.path.exists(old_path):
            os.remove(old_path)
            print(f"Removed lingering asset {old_path}")

if __name__ == "__main__":
    process_torch()
